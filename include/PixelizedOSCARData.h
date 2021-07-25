#ifndef PIXELIZEDOSCARDATA_H
#define PIXELIZEDOSCARDATA_H

#include <TROOT.h>

class PixelizedOSCARData
{
public:
  Int_t    fmulti;
  Int_t    *fnumtel;          //[fmulti]
  Int_t    *fnumstrip;        //[fmulti]
  Int_t    *fnumpad;          //[fmulti]
  Short_t  *fEnergyStrip;     //[fmulti]
  Short_t  *fEnergyPad;       //[fmulti]
  Short_t  *fTimeStrip;       //[fmulti]
  Short_t  *fTimePad;         //[fmulti]
  Double_t *fEnergyStripCal;  //[fmulti]
  Double_t *fEnergyPadCal;    //[fmulti]
  Double_t *fKinEnergy;       //[fmulti]
  Double_t *fTheta;           //[fmulti]
  Double_t *fPhi;             //[fmulti]
  Int_t *fZId;                //[fmulti]
  Int_t *fAId;                //[fmulti]

  PixelizedOSCARData(int);
  PixelizedOSCARData();
  virtual ~PixelizedOSCARData();

  ClassDef(PixelizedOSCARData,1);
};

#endif
