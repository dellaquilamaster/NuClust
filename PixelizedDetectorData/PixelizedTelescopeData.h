#ifndef PIXELIZEDTELESCOPEDATA_H
#define PIXELIZEDTELESCOPEDATA_H

#include <TROOT.h>

class PixelizedTelescopeData
{
public:
  Int_t    fmulti;
  Int_t    *fnumtel;         //[fmulti]
  Int_t    *fnumstripf;      //[fmulti]
  Int_t    *fnumstripb;      //[fmulti]
  Int_t    *fnumstripssssd;  //[fmulti]
  Short_t  *fEnergyFront;    //[fmulti]
  Short_t  *fEnergyBack;     //[fmulti]
  Short_t  *fEnergySSSSD;    //[fmulti]
  Double_t *fEnergyFrontCal; //[fmulti]
  Double_t *fEnergyBackCal;  //[fmulti]
  Double_t *fEnergySSSSDCal; //[fmulti]
  Double_t *fKinEnergy;      //[fmulti]
  Double_t *fTheta;          //[fmulti]
  Double_t *fPhi;            //[fmulti]
  Double_t *fZ;              //[fmulti]
  Double_t *fA;              //[fmulti]
  Int_t *fZId;               //[fmulti]
  Int_t *fAId;               //[fmulti]
  Int_t *fptype;             //[fmulti]

  PixelizedTelescopeData(int);
  PixelizedTelescopeData();
  virtual ~PixelizedTelescopeData();

  ClassDef(PixelizedTelescopeData,1);
};

#endif
