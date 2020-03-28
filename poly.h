#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>

class poly
{
private:
  unsigned short int deg;
  std::vector<std::complex<double>> coef;

public:
  poly();
  ~poly();
  poly(int inDeg);
  void setCoef();
  void dispPoly();
  std::complex<double> evalPoly(std::complex<double> x);
  void fileSetCoef(int inDeg, std::vector<std::complex<double>> inCoef);
  poly diff();
  bool zero();
  std::complex<double> synDiv(const std::complex<double> divisor);
  bool evalAtGiven(std::vector<std::complex<double>> &roots);
};

#endif