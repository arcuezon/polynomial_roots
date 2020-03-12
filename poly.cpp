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

  coef = new std::complex<double>[deg + 1];

  for (int n = 0; n <= deg; n++)
  {
    coef[n] = 0;
  }

  double coefIn = 0;

  for (int n = 0; n <= deg; n++)
  {
    std::cout << "Coefficient for degree " << n << ": ";
    std::cin >> coefIn;

    coef[n] = coefIn;
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

void poly::fileSetCoef(int inDeg, std::complex<double> inCoef[])
{
  deg = inDeg;

  coef = new std::complex<double>[deg + 1];
  for (int i = 0; i <= deg; i++)
  {
    coef[i] = 0;
  }

  for (int i = 0; i <= deg; i++)
  {
    coef[i] = inCoef[i];
  }

  //std::cout << "[DEBUG] Polynomial read from file.\n";
  //dispPoly();
}

poly poly::diff()
{
  poly eqnPrime;
  std::complex<double> *coefPrime = new std::complex<double>[deg];

  for (int n = deg - 1; n > 0; n--)
  {
    coefPrime[n] = coef[n + 1] * (double)(n + 1);
  }
  coefPrime[0] = coef[1];

  //std::cout << "Differentiated:\n";

  eqnPrime.fileSetCoef(deg - 1, coefPrime);
  delete[] coefPrime;

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
  deg--;         //Decrement degree
  for (int n = deg; n >= 0; n--)
  {
    this->coef[n] = newCoef[n];
  }

  delete[] newCoef;
  return remainder;
}

bool poly::evalAtRoots(std::complex<double> *roots)
{
  std::cout << "Evaluating polynomial at identified roots:\n";
  std::cout.precision(6);

  for (int n = 0; n < deg; n++)
  {
    std::cout << "f" << std::fixed << roots[n] << " = " << std::scientific << evalPoly(roots[n]) << std::endl;
  }

  return true;
}