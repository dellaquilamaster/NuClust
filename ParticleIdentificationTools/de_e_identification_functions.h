#ifndef DE_E_IDENTIFICATION_FUNCTIONS_H
#define DE_E_IDENTIFICATION_FUNCTIONS_H

#include <math.h>
#include <TROOT.h>
#include <TF1.h>
#include <TMath.h>

/*
 * ////////////////////////////////////////////////////////////////////
 * TassanGot class
 * This class handles the Tassan-Got formula
 * for all the isotopes.
 * See L. Tassan-Got, Nucl. Instr. Meth. Phys. Res. B 194 (2002) 503.
 * ////////////////////////////////////////////////////////////////////
 * 
 * 
 */
//
class TassanGot
{
public :
  TF1 * GetFunction(int Z, int A);
  
  void SetParameters(double g, double mu, double lambda);
  void SetParameters(double *);
  
  double * GetParameters();
  
private :
  double fPar[3];
};
//

//
// A fit function for the Tassan-Got formula
// x[0] = Eres
// x[1] = Z*100+A
// par[0]=g; 
// par[1]=mu; 
// par[2]=lambda; 
double TassanGotFitFunction(double * x, double * par);
//A function for fast tassan got evaluation
double TassanGotFunction(double x, double Z, double A, double * par);
//

//
class TassanGotExtended
{
public :
  TF1 * GetFunction(int Z, int A);
  
  void SetParameters(double g, double mu, double nu, double alpha, double beta, double lambda, double xi);
  void SetParameters(double *);
  
  double * GetParameters();
  
private :
  double fPar[7];
};
//

// A fit function for the Tassan-Got formula
// x[0] = Eres
// x[1] = Z*100+A
// par[0]=g; 
// par[1]=mu; 
// par[2]=nu; 
// par[3]=alpha; 
// par[4]=beta; 
// par[5]=lambda; 
// par[6]=xi; 
double TassanGotExtendedFitFunction(double * x, double * par);
//A function for fast tassan got evaluation
double TassanGotExtendedFunction(double x, double Z, double A, double * par);
//

////////////////////////////////////////////////////////////////////

//
// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// This formula needs 9 parameters
// Extracted from DEEFIT by Enrico De Filippo
// x[0] = Eres
// x[1] = Z*100+A
// par[7] = offset DE
// par[8] = offset E
Double_t LeNeindreFitFunction(Double_t *x, Double_t *par);
////////////////////////////////////////////////////////////////////
Double_t LeNeindreFunction(double x, double Z, double A, double * par);
////////////////////////////////////////////////////////////////////


// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
// Extracted from DEEFIT by Enrico De Filippo
// x[0] = Eres
// x[1] = Z*100+A
// par[12] = offset DE
// par[13] = offset E
Double_t LeNeindreEnhancedFitFunction(Double_t *x, Double_t *par);
////////////////////////////////////////////////////////////////////
Double_t LeNeindreEnhancedFunction(double x, double Z, double A, double * par);
////////////////////////////////////////////////////////////////////

#endif
