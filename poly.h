#ifndef POLY_H
#define POLY_H

#include <complex>
#include <cmath>

class poly
{
private:
  unsigned short int deg = 0;
  std::complex<double> *coef;

public:
  poly();
  ~poly();
  poly(int inDeg);
  void setCoef();
  void dispPoly();
  std::complex<double> evalPoly(std::complex<double> x);
  void fileSetCoef(int inDeg, std::complex<double> inCoef[]);
  poly diff();
  bool zero();
  std::complex<double> synDiv(const std::complex<double> divisor);
  bool evalAtRoots(std::complex<double> *roots);
};

#endif