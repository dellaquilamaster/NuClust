#include "de_e_identification_tools.h"

//____________________________________________________
de_e_identification_tools::de_e_identification_tools() :
fZmin(1),
fZmax(10)
{}

//____________________________________________________
void de_e_identification_tools::SetFunction(double (*function)(double, double, double, double *))
{
  fFunc=function;
}

//____________________________________________________
void de_e_identification_tools::SetNumParameters(int num_parameters)
{
  fNumPar=num_parameters;
  fPar=new double[num_parameters];
}

//____________________________________________________
void de_e_identification_tools::SetParameter(int ipar, double value)
{
  fPar[ipar]=value;
}

//____________________________________________________
int de_e_identification_tools::get_charge(double de, double fast, double *zeta)
{
  const unsigned int maxiter=50;
  int izeta=0;
  double yy, dist;
  double the_unsigned_distance;
  double the_best_distance=1E6;
  int ztest, atest;
  int zmintest=fZmin, zmaxtest=fZmax;
  double amass=0,amassp=0,amassm=0;
  bool found = false;
  
  unsigned int iter = 0;
  *zeta = 0;
  while(iter < maxiter) {
    (iter)++;
    ztest = (zmintest + zmaxtest) / 2;
    atest = get_mass_charity(ztest);
    
    if(atest==1)atest=2;
    
    yy = (*fFunc)(fast,ztest,atest,fPar);
    the_unsigned_distance = std::fabs(de - yy);
    
    if(the_unsigned_distance<the_best_distance) {
      the_best_distance=the_unsigned_distance;
      izeta=ztest;
    }
    
    if(zmintest==zmaxtest) {
      found = true;
      break;
    }
    if(zmintest==zmaxtest-1) {
      if(ztest==zmintest) zmintest=zmaxtest;
      else zmaxtest=zmintest;
      continue;
    }  
    if((de - yy)>=0) {
      zmintest = ztest;
      continue;
    }
    else {
      zmaxtest = ztest;
      continue;
    }
  }
  if(!found) {
    std::cout<<"Get_Charge>> Convergence not reached"<<std::endl;
    return 0;
  }
  
  // dispersion around mean charge value
  amass = get_mass_charity(izeta);
  amassp = get_mass_charity(izeta+1);
  amassm = get_mass_charity(izeta>1 ? izeta-1 : izeta);
  
  yy = (*fFunc)(fast,izeta,amass,fPar);
  dist = de - yy;
  
  if(dist >= 0.0) {
    *zeta = izeta + dist/((*fFunc)(fast,izeta+1,amassp,fPar)-yy);
  }
  else {
    *zeta = izeta + dist/(yy- (izeta>1 ? (*fFunc)(fast,izeta-1,amassm,fPar) : 0.));
  }
  if(*zeta>0 && *zeta<0.5) {
    return 0.;
  }
  return izeta;
}

//____________________________________________________
double de_e_identification_tools::get_mass(int charge, double de, double fast)
{
  const int maxiter=100;
  bool found = false;
  int amin,amax;
  int atest;
  int imass=0;
  double the_unsigned_distance;
  double the_best_distance=1E6; 
  int Amin[] = {0, 2, 4, 6, 7, 9, 11, 13, 14, 17, 19, 21, 22, 23};
  int Amax[] = {6, 10, 11, 12, 13, 15, 18, 26, 29, 32, 35, 36, 38, 41};
  double fmass, yy, dist;
  
  unsigned int iter = 0;
  amin = Amin[charge-1];
  amax = Amax[charge-1];
  
  while(iter < maxiter) {
    (iter)++;
    atest = (amax + amin) / 2;
    //
    yy = (*fFunc)(fast,charge,atest,fPar);
    the_unsigned_distance = std::fabs(de - yy);
    // 
    
    if(the_unsigned_distance<the_best_distance) {
      the_best_distance=the_unsigned_distance;
      imass=atest;
    }
    
    if(amin==amax) {
      found = true;
      break;
    }
    if(amin==amax-1) {
      if(atest==amin) amin=amax;
      else amax=amin;
      continue;
    }
    if((de - yy)>=0) {
      amin = atest;
      continue;
    }
    else {
      amax = atest;
      continue;
    }
  }  //end convergence loop
  
  if(!found) {
    if(charge>1) {
      std::cout<<"Get_Mass>> Warning: charge convergenze failed:  Z="<<charge<<std::endl;
    }
  }
  
  yy = (*fFunc)(fast,charge,imass,fPar);
  if(imass==0) {
    return 0;
  }
  
  // calculate dispersion around mean mass value
  dist = de - yy;
  if(dist >= 0.0) {
    fmass = imass + dist/((*fFunc)(fast,charge,imass + 1.,fPar)-yy);
  }
  else {
    fmass = imass + dist/(yy-(*fFunc)(fast,charge,imass - 1.,fPar));
  }
  //
  return fmass;
}

//Return the mass by the Charity formula
//PRC 58(1998)1073
//____________________________________________________
double de_e_identification_tools::get_mass_charity(double Z)
{
  double A;
  
  if(Z<=6) {
    int CharityLight[] = {1,4,7,9,10,12};
    A = CharityLight[(int)Z-1];
    return A;
  }
  else
    return (unsigned int)(2.072*Z + 2.32E-03 * Z*Z) + 1;
}


