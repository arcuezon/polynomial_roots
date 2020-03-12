#ifndef POLY_H
#define POLY_H

class poly
{
private:
  unsigned short int deg = 0;
  double *coef;

public:
  poly();
  ~poly();
  poly(int inDeg);
  void setCoef();
  void dispPoly();
  long double evalPoly(long double x);
  void fileSetCoef(int inDeg, double inCoef[]);
  poly diff();
  bool quadDeg();
  double synDiv(const double divisor);
};

#endif