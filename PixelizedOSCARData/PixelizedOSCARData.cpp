#include <PixelizedOSCARData.h>

const int MAX_MULTIPLICITY=50;

//________________________________________________
PixelizedOSCARData::PixelizedOSCARData(int num_particles) :
fmulti(0)
{
  fnumtel=new Int_t[num_particles];    
  fnumstrip=new Int_t[num_particles];    
  fnumpad=new Int_t[num_particles];      
  fEnergyStrip=new Short_t[num_particles]; 
  fEnergyPad=new Short_t[num_particles];    
  fTimeStrip=new Short_t[num_particles]; 
  fTimePad=new Short_t[num_particles];    
  fEnergyStripCal=new Double_t[num_particles];    
  fEnergyPadCal=new Double_t[num_particles];      
  fKinEnergy=new Double_t[num_particles]; 
  fTheta=new Double_t[num_particles]; 
  fPhi=new Double_t[num_particles]; 
  fZId=new Int_t[num_particles]; 
  fAId=new Int_t[num_particles]; 
}

//________________________________________________
PixelizedOSCARData::PixelizedOSCARData() :
fmulti(0)
{
  fnumtel=new Int_t[MAX_MULTIPLICITY];    
  fnumstrip=new Int_t[MAX_MULTIPLICITY];    
  fnumpad=new Int_t[MAX_MULTIPLICITY];      
  fEnergyStrip=new Short_t[MAX_MULTIPLICITY]; 
  fEnergyPad=new Short_t[MAX_MULTIPLICITY];    
  fTimeStrip=new Short_t[MAX_MULTIPLICITY]; 
  fTimePad=new Short_t[MAX_MULTIPLICITY];    
  fEnergyStripCal=new Double_t[MAX_MULTIPLICITY];    
  fEnergyPadCal=new Double_t[MAX_MULTIPLICITY];      
  fKinEnergy=new Double_t[MAX_MULTIPLICITY]; 
  fTheta=new Double_t[MAX_MULTIPLICITY]; 
  fPhi=new Double_t[MAX_MULTIPLICITY]; 
  fZId=new Int_t[MAX_MULTIPLICITY]; 
  fAId=new Int_t[MAX_MULTIPLICITY]; 
}

//________________________________________________
PixelizedOSCARData::~PixelizedOSCARData()
{
  delete [] fnumtel;
  delete [] fnumstrip;
  delete [] fnumpad;
  delete [] fEnergyStrip;
  delete [] fEnergyPad;
  delete [] fTimeStrip;
  delete [] fTimePad;
  delete [] fEnergyStripCal;
  delete [] fEnergyPadCal;
  delete [] fKinEnergy;
  delete [] fTheta;
  delete [] fPhi;
  delete [] fZId;
  delete [] fAId;
}
