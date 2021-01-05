#include <PixelizedTelescopeData.h>

const int MAX_MULTIPLICITY=50;

//________________________________________________
PixelizedTelescopeData::PixelizedTelescopeData(int num_particles) :
fmulti(0)
{
  fnumtel=new Int_t[num_particles];    
  fnumstripf=new Int_t[num_particles];    
  fnumstripb=new Int_t[num_particles];      
  fnumstripssssd=new Int_t[num_particles];      
  fEnergyFront=new Short_t[num_particles]; 
  fEnergyBack=new Short_t[num_particles];    
  fEnergySSSSD=new Short_t[num_particles];    
  fEnergyFrontCal=new Double_t[num_particles];    
  fEnergyBackCal=new Double_t[num_particles];      
  fEnergySSSSDCal=new Double_t[num_particles];      
  fKinEnergy=new Double_t[num_particles]; 
  fTheta=new Double_t[num_particles]; 
  fPhi=new Double_t[num_particles]; 
  fZ=new Double_t[num_particles]; 
  fA=new Double_t[num_particles]; 
  fZId=new Int_t[num_particles]; 
  fAId=new Int_t[num_particles]; 
  fptype=new Int_t[num_particles]; 
}

//________________________________________________
PixelizedTelescopeData::PixelizedTelescopeData() :
fmulti(0)
{
  fnumtel=new Int_t[MAX_MULTIPLICITY];    
  fnumstripf=new Int_t[MAX_MULTIPLICITY];    
  fnumstripb=new Int_t[MAX_MULTIPLICITY];      
  fnumstripssssd=new Int_t[MAX_MULTIPLICITY];      
  fEnergyFront=new Short_t[MAX_MULTIPLICITY]; 
  fEnergyBack=new Short_t[MAX_MULTIPLICITY];    
  fEnergySSSSD=new Short_t[MAX_MULTIPLICITY];    
  fEnergyFrontCal=new Double_t[MAX_MULTIPLICITY];    
  fEnergyBackCal=new Double_t[MAX_MULTIPLICITY];      
  fEnergySSSSDCal=new Double_t[MAX_MULTIPLICITY];      
  fKinEnergy=new Double_t[MAX_MULTIPLICITY]; 
  fTheta=new Double_t[MAX_MULTIPLICITY]; 
  fPhi=new Double_t[MAX_MULTIPLICITY]; 
  fZ=new Double_t[MAX_MULTIPLICITY]; 
  fA=new Double_t[MAX_MULTIPLICITY]; 
  fZId=new Int_t[MAX_MULTIPLICITY]; 
  fAId=new Int_t[MAX_MULTIPLICITY]; 
  fptype=new Int_t[MAX_MULTIPLICITY];
}

//________________________________________________
PixelizedTelescopeData::~PixelizedTelescopeData()
{
  delete [] fnumtel;
  delete [] fnumstripf;
  delete [] fnumstripb;
  delete [] fnumstripssssd;
  delete [] fEnergyFront;
  delete [] fEnergyBack;
  delete [] fEnergySSSSD;
  delete [] fEnergyFrontCal;
  delete [] fEnergyBackCal;
  delete [] fEnergySSSSDCal;
  delete [] fKinEnergy;
  delete [] fTheta;
  delete [] fPhi;
  delete [] fZ;
  delete [] fA;
  delete [] fZId;
  delete [] fAId;
  delete [] fptype;
}
