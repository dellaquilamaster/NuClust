#include "SRIMEnergyLossModule.h"


//______________________________________________
SRIMEnergyLossModule::SRIMEnergyLossModule(const char * data_path) :
fDataPath(data_path),
fEnergyLossPrecision(0.001)
{
  if(fDataPath.empty()) {
    fDataPath.assign(".");
  }
  if(fDataPath.find_last_of('/')==fDataPath.length()-1) {
    fDataPath.assign(fDataPath.substr(0,fDataPath.find_last_of('/')));
  }
}

//______________________________________________
SRIMEnergyLossModule::~SRIMEnergyLossModule()
{}

//______________________________________________
void SRIMEnergyLossModule::Clear()
{
  for(auto && energy : ParticleEnergy) {
    energy.second.clear(); 
  }
  for(auto && eloss : SrimELoss) {
    eloss.second.clear(); 
  }
  for(auto && range : SrimRange) {
    range.second.clear(); 
  }
  for(auto && Inter : SplineInterpolator) {
    delete Inter.second; 
  }
  for(auto && Inter : RangeSplineInterpolator) {
    delete Inter.second; 
  }
  for(auto && Inter : EnergyFromRangeSplineInterpolator) {
    delete Inter.second; 
  }
}

//______________________________________________
int SRIMEnergyLossModule::LoadEnergyLossFile(const char * file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }

  std::string TheElement (file_name);
  TheElement.assign(TheElement.substr(TheElement.find_last_of('/')+1,TheElement.find_last_of(".dat")-4-TheElement.find_last_of('/')));

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);

//     LineRead.assign(LineRead.substr(0,LineRead.find('*')));
    if(LineRead.empty()) continue;
    if(LineRead.find_first_not_of(' ') == std::string::npos) continue;
    
    if(LineRead.find("  --------------  ---------- ---------- ----------  ----------  ----------")!=std::string::npos) {
      //Found begin string
      while (!FileIn.eof())
      {
        std::string LineData;
        std::getline(FileIn, LineData);
        
        if(LineData.find("-----------------------------------------------------------")!=std::string::npos) {
          break; 
        }
        
        std::istringstream LineStream(LineData);
        
        std::string EnergyString;
        std::string EnergyUnit;
        std::string StoppingPowerElectronString;
        std::string StoppingPowerNuclearString;
        std::string RangeString;
        std::string RangeUnit;
        
        LineStream>>EnergyString>>EnergyUnit>>StoppingPowerElectronString>>StoppingPowerNuclearString>>RangeString>>RangeUnit;
        
        std::replace (EnergyString.begin(), EnergyString.end(), ',', '.');
        std::replace (StoppingPowerElectronString.begin(), StoppingPowerElectronString.end(), ',', '.');
        std::replace (StoppingPowerNuclearString.begin(), StoppingPowerNuclearString.end(), ',', '.');
        std::replace (RangeString.begin(), RangeString.end(), ',', '.');
        
        double StoppingPowerScalingFactor=1E-3;//Data is in keV/um
        double EnergyScalingFactor=1;
        if(EnergyUnit.compare("eV")==0) EnergyScalingFactor=1E-6;
        if(EnergyUnit.compare("keV")==0) EnergyScalingFactor=1E-3;
        double RangeScalingFactor=1;
        if(RangeUnit.compare("A")==0) RangeScalingFactor=1E-4;
        if(RangeUnit.compare("mm")==0) RangeScalingFactor=1E3;
        if(RangeUnit.compare("m")==0) RangeScalingFactor=1E6;
                
        const double Energy=std::stof(EnergyString)*EnergyScalingFactor;
        const double StoppingPowerElectron=std::stof(StoppingPowerElectronString)*StoppingPowerScalingFactor;
        const double StoppingPowerNuclear=std::stof(StoppingPowerNuclearString)*StoppingPowerScalingFactor;
        const double Range=std::stof(RangeString)*RangeScalingFactor;
        
        (ParticleEnergy)[TheElement].push_back(Energy);
        (SrimELoss)[TheElement].push_back(StoppingPowerElectron+StoppingPowerNuclear);
        (SrimRange)[TheElement].push_back(Range);
        
        NRead++;        
      }    
      
    }
  }
  
  Emin[TheElement]=(ParticleEnergy[TheElement])[0];
  Emax[TheElement]=(ParticleEnergy[TheElement])[ParticleEnergy[TheElement].size()-1];
  
  (SplineInterpolator)[TheElement] = new ROOT::Math::Interpolator();
  (SplineInterpolator)[TheElement]->SetData(ParticleEnergy[TheElement],SrimELoss[TheElement]);
  (RangeSplineInterpolator)[TheElement] = new ROOT::Math::Interpolator();
  (RangeSplineInterpolator)[TheElement]->SetData(ParticleEnergy[TheElement],SrimRange[TheElement]);
  (EnergyFromRangeSplineInterpolator)[TheElement] = new ROOT::Math::Interpolator();
  (EnergyFromRangeSplineInterpolator)[TheElement]->SetData(SrimRange[TheElement],ParticleEnergy[TheElement]);
    
  return NRead;
}

//______________________________________________
void SRIMEnergyLossModule::SetEnergyLossPrecision(double new_precision)
{
  fEnergyLossPrecision=new_precision;
} 

//______________________________________________
double SRIMEnergyLossModule::GetEnergyLoss(int Z, int A, double Einc, const char * material, double thickness_um)
{
  double Precision=fEnergyLossPrecision; //Lower is this number higher is the precision (slower calculation)
  double dThicknessMax=thickness_um; //This is the maximum thickness used as the integration step
  double IntegrateThickness=0;
  double dThickness=dThicknessMax;
  double Eresidual=Einc;
  double ELoss=0;

  std::string TheCombination (Form("SRIM_Z%02d_A%02d_%s",Z, A, material));

  //Check if information is present
  if(SplineInterpolator.find(TheCombination)==SplineInterpolator.end()) {
    if(LoadEnergyLossFile(Form("%s/SRIM_Z%02d_A%02d_%s.dat", fDataPath.c_str(), Z, A, material))<=0) {
      printf("Error: information not present for Z=%d A=%d material=%s\n", Z, A, material);
      return -100;
    }
 }

 //Retrieve the LISE information
 ROOT::Math::Interpolator * TheSplineInterpolator = (SplineInterpolator)[TheCombination];
 double TheEmin = Emin[TheCombination];

  for(;IntegrateThickness<thickness_um; IntegrateThickness+=dThickness)
  {
    if(Eresidual<=TheEmin) { //the particle stopped in the material
      ELoss=Einc;
      return ELoss;
    }

    if(TheSplineInterpolator->Deriv(Eresidual)!=0) {
      dThickness=fmin((thickness_um-IntegrateThickness),fmin(dThicknessMax,std::fabs(Precision/TheSplineInterpolator->Deriv(Eresidual)))); //variable integration step with fixed precision
    }

    double ELossStep=dThickness*TheSplineInterpolator->Eval(Eresidual);

    ELoss+=ELossStep;
    Eresidual-=ELossStep;
  }

  return ELoss;
}

//______________________________________________
double SRIMEnergyLossModule::GetEnergyLossGas(int Z, int A, double Einc, const char * material, double pressure, double temperature, double thickness_um)
{
  double Precision=fEnergyLossPrecision; //Lower is this number higher is the precision (slower calculation)
  double dThicknessMax=thickness_um; //This is the maximum thickness used as the integration step
  double IntegrateThickness=0;
  double dThickness=dThicknessMax;
  double Eresidual=Einc;
  double ELoss=0;

  std::string TheCombination (Form("SRIM_Z%02d_A%02d_gas_%s%.0fmbar%.2fK",Z, A, material, pressure, temperature));

  //Check if information is present
  if(SplineInterpolator.find(TheCombination)==SplineInterpolator.end()) {
    if(LoadEnergyLossFile(Form("%s/%s.dat", fDataPath.c_str(), TheCombination.c_str()))<=0) {
      printf("Error: information not present for Z=%d A=%d material=%s pressure=%.0fmbar T=%.2fK\n", Z, A, material, pressure, temperature);
      return -100;
    }
 }

 //Retrieve the LISE information
 ROOT::Math::Interpolator * TheSplineInterpolator = (SplineInterpolator)[TheCombination]; 
 double TheEmin = Emin[TheCombination];

  for(;IntegrateThickness<thickness_um; IntegrateThickness+=dThickness)
  {
    if(Eresidual<=TheEmin) { //the particle stopped in the material
      ELoss=Einc;
      return ELoss;
    }
    if(TheSplineInterpolator->Deriv(Eresidual)!=0) {
      dThickness=fmin((thickness_um-IntegrateThickness),fmin(dThicknessMax,std::fabs(Precision/TheSplineInterpolator->Deriv(Eresidual)))); //variable integration step with fixed precision
    }
    
    double ELossStep=dThickness*TheSplineInterpolator->Eval(Eresidual);

    ELoss+=ELossStep;
    Eresidual-=ELossStep;
  }

  return ELoss;
}
