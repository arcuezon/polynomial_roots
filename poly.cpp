#include "poly.h"
#include <iostream>

poly::poly()
{
}

poly::poly(int inDeg)
{
  deg = inDeg;
}

poly::~poly()
{
}

void poly::setCoef()
{
  if (deg == 0)
  {
    std::cout << "Enter degree of polynomial: ";
    std::cin >> deg;
  }

  double coefIn = 0;

  for (int n = 0; n <= deg; n++)
  {
    std::cout << "Coefficient for degree " << n << ": ";
    std::cin >> coefIn;

    coef.push_back(coefIn);
  }
}

void poly::dispPoly()
{
  std::cout << "Degree = " << deg << std::endl;

  for (int n = deg; n >= 0; n--)
  {
    std::cout << real(coef[n]) << "x^" << n << std::endl;
  }

  std::cout << std::endl;
  //std::cout << real(coef[0]) << std::endl;
}

std::complex<double> poly::evalPoly(std::complex<double> x)
{
  std::complex<double> sum = {0, 0};
  for (int n = deg; n >= 0; n--)
  {
    sum = sum * x + coef[n];
  }

  return sum;
}

void poly::fileSetCoef(int inDeg, std::vector<std::complex<double>> inCoef)
{
  deg = inDeg;

  for (int i = 0; i <= deg; i++)
  {
    coef.push_back(inCoef[i]);
  }
}

poly poly::diff()
{
  poly eqnPrime;
  std::vector<std::complex<double>> coefPrime;

  coefPrime.resize(deg + 1);

  for (int n = deg - 1; n > 0; n--)
  {
    coefPrime[n] = coef[n + 1] * (double)(n + 1);
  }
  coefPrime[0] = coef[1];

  eqnPrime.fileSetCoef(deg - 1, coefPrime);

  return eqnPrime;
}

bool poly::zero()
{
  return (deg == 0);
}

std::complex<double> poly::synDiv(const std::complex<double> divisor)
{
  std::complex<double> newCoef[deg + 1] = {0};
  newCoef[deg - 1] = coef[deg];
  std::complex<double> remainder = 0;

  for (int n = deg - 2; n >= -1; n--) //-2 since new eqn is 1 degree lower and the first coef is already set
  {
    if (n == -1) // Compute Remainder
    {
      remainder = coef[n + 1] + (divisor * newCoef[n + 1]);
    }
    else
    {
      newCoef[n] = coef[n + 1] + (divisor * newCoef[n + 1]);
    }
  }

  //Transfer new coefficients to existing array
  this->coef[deg] = 0; //Supposed leading = 0
  this->deg--;         //Decrement degree
  for (int n = deg; n >= 0; n--)
  {
    this->coef[n] = newCoef[n];
  }

  return remainder;
}

bool poly::evalAtGiven(std::vector<std::complex<double>> &roots)
{
  std::cout << "Evaluating polynomial at identified roots:\n";
  std::cout.precision(6);

  for (int n = 0; n < deg; n++)
  {
    std::cout << "f" << std::fixed << roots[n] << " = " << std::scientific << real(evalPoly(roots[n])) << std::endl;
  }

  return true;
}