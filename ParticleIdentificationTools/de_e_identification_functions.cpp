#include "de_e_identification_functions.h"

//____________________________________________________
TF1 * TassanGot::GetFunction(int Z, int A) 
{
  TF1 * TheFunc = (TF1*) new TF1 (Form("func_Z%02d_A%02d",Z,A),Form("(([0]*x)^([1]+1)+(([2]*%d^(2/([1]+1)))*%d^([1]/([1]+1)))^([1]+1))^(1/([1]+1))-[0]*x", Z, A),0,1000);
  TheFunc->SetParameters(fPar);
  return TheFunc;
}

//____________________________________________________
void TassanGot::SetParameters(double g, double mu, double lambda)
{
  fPar[0]=g; 
  fPar[1]=mu; 
  fPar[2]=lambda;  
}

//____________________________________________________
void TassanGot::SetParameters(double * parameters) 
{
  fPar[0]=parameters[0]; 
  fPar[1]=parameters[1]; 
  fPar[2]=parameters[2];
}

//____________________________________________________
double * TassanGot::GetParameters() {
  return fPar; 
}

double TassanGotFitFunction(double * x, double * par)
{
  double Z = int(x[1])/100;
  double A = int(x[1])%100;
  return pow((pow((par[0]*x[0]),(par[1]+1))+pow(((par[2]*pow(Z,(2/(par[1]+1))))*pow(A,(par[1]/(par[1]+1)))),(par[1]+1))),(1/(par[1]+1)))-par[0]*x[0];
}

double TassanGotFunction(double x, double Z, double A, double * par)
{
  return pow((pow((par[0]*x),(par[1]+1))+pow(((par[2]*pow(Z,(2/(par[1]+1))))*pow(A,(par[1]/(par[1]+1)))),(par[1]+1))),(1/(par[1]+1)))-par[0]*x;
}

//____________________________________________________
TF1 * TassanGotExtended::GetFunction(int Z, int A) 
{
  TF1 * TheFunc = (TF1*) new TF1 (Form("func_Z%02d_A%02d",Z,A),Form("(([0]*x)^([1]+[2]+1)+([5]*%d^[3]*%d^[4])^([1]+[2]+1)+[6]*%d^2*%d^[1]*([0]*x)^[2])^(1/([1]+[2]+1))-[0]*x", Z, A, Z, A),0,1000);
  TheFunc->SetParameters(fPar);
  return TheFunc;
}

//____________________________________________________
void TassanGotExtended::SetParameters(double g, double mu, double nu, double alpha, double beta, double lambda, double xi) 
{
  fPar[0]=g; 
  fPar[1]=mu; 
  fPar[2]=nu; 
  fPar[3]=alpha; 
  fPar[4]=beta; 
  fPar[5]=lambda; 
  fPar[6]=xi; 
}

//____________________________________________________
void TassanGotExtended::SetParameters(double * parameters) 
{
  fPar[0]=parameters[0]; 
  fPar[1]=parameters[1]; 
  fPar[2]=parameters[2];
  fPar[3]=parameters[3]; 
  fPar[4]=parameters[4]; 
  fPar[5]=parameters[5];  
  fPar[6]=parameters[6]; 
}

//____________________________________________________
double * TassanGotExtended::GetParameters() {
  return fPar; 
}

double TassanGotExtendedFitFunction(double * x, double * par)
{
  double Z = int(x[1])/100;
  double A = int(x[1])%100;    
  return pow(pow(par[0]*x[0],par[1]+par[2]+1)+pow(par[5]*pow(Z,par[3])*pow(A,par[4]),par[1]+par[2]+1)+par[6]*pow(Z,2)*pow(A,par[1])*pow(par[0]*x[0],par[2]),1./(par[1]+par[2]+1))-par[0]*x[0];
}

double TassanGotExtendedFunction(double x, double Z, double A, double * par)
{
  typedef struct parameters_ {
    double g, mu, nu, alpha, beta, lambda, xi;
  } parameters;
  parameters * p_x;
  p_x = (parameters*)par;
  
  double mu_nu_uno=p_x->mu+p_x->nu+1;
  double E_g=p_x->g*x;
  return pow(pow(E_g,mu_nu_uno)+pow(p_x->lambda*pow(Z,p_x->alpha)*pow(A,p_x->beta),mu_nu_uno)+p_x->xi*Z*Z*pow(A,p_x->mu)*pow(E_g,p_x->nu),1.0/(mu_nu_uno))-E_g;
}

Double_t LeNeindreFunction(double x, double Z, double A, double * par)
{
 double x_pedestal_subtracted = x-par[8];
 
 double exp1 = par[2] + par[3] + 1;
 double exp2 = 1./exp1;
 double res = pow((par[5] * x_pedestal_subtracted), exp1) +
       pow((par[6]*pow(Z,par[0]) * pow(A,par[1])),exp1) +
       par[4]*pow(Z,2) * pow(A,par[2]) * pow(x_pedestal_subtracted*par[5],par[3]);
 res = pow(res,exp2) - par[5]*x_pedestal_subtracted + par[7];
 return res;
}

Double_t LeNeindreFitFunction(Double_t * x, Double_t * par)
{
  double Z = int(x[1])/100;
  double A = int(x[1])%100;
  return LeNeindreFunction(x[0], Z, A, par);
}

// Function for DE-E identification based
// on formulas from N. Le Neindre et al. NIM A490 (2002) 251
// modified following the formula of W. Gawlikowicz
// for Light-Energy relation in CsI(Tl)
// NIM A491 (2002) 181. Adapted by Amalia Pop following
// ref.: J. Blicharska et al. LNS report 2005
// This formula needs 14 fit parameters
// Extracted from DEEFIT by Enrico De Filippo
Double_t LeNeindreEnhancedFunction(double x, double Z, double A, double * par)
{ 
  double x_pedestal_subtracted = x-par[13];
 
  double exp1 = par[2] + par[3] + 1;
  double exp2 = 1./exp1;
  double reslog = log(1.+ par[9]* Z)*(1.- exp(-par[10]*pow(Z,par[11])))/Z;
  double ene = par[6] * reslog * x_pedestal_subtracted ;
  ene = ene + par[7] * Z * sqrt(A) * log(1. + par[8] * reslog  * x_pedestal_subtracted);
  double res = pow(ene,exp1) +
        pow((par[4]* pow(Z,par[0]) * pow(A,par[1])),exp1) +
        par[5]*pow(Z,2) * pow(A,par[2]) * pow(ene,par[3]);
  res = pow(res,exp2) - ene + par[12];
  return res;
}


Double_t LeNeindreEnhancedFitFunction(Double_t * x, Double_t * par)
{
  double Z = int(x[1])/100;
  double A = int(x[1])%100;
  return LeNeindreEnhancedFunction(x[0], Z, A, par);
}
