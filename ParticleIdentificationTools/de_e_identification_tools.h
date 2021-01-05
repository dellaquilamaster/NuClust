#ifndef DE_E_IDENTIFICATION_TOOLS_H
#define DE_E_IDENTIFICATION_TOOLS_H

#include <iostream>
#include <math.h>

class de_e_identification_tools
{
public :
  de_e_identification_tools();
  ~de_e_identification_tools();
  
  void SetFunction(double (*function)(double, double, double, double *));
  void SetNumParameters(int);
  void SetParameter(int, double);
  
  //
  //get the charge for a given de and e
  int get_charge(double de, double e, double * zeta);
  //get the mass for a given de and e and a charge
  double get_mass(int charge, double de, double e);
  //
  
private :
  int fNumPar;
  double * fPar;
  double (*fFunc) (double, double, double, double*);
  //get the most probable mass for a given Z according to Charity formula
  double get_mass_charity(double Z);
  //
  
  //
  int fZmin;
  int fZmax;
  //
};

#endif
