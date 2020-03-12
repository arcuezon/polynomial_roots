#include "poly.h"
#include <iostream>
#include <complex>

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

  coef = new double[deg + 1];

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

  for (int n = deg; n > 0; n--)
  {
    std::cout << coef[n] << "x^" << n << " + ";
  }

  std::cout << coef[0] << std::endl;
}

long double poly::evalPoly(long double x)
{
  double sum = 0;
  for (int n = deg; n >= 0; n--)
  {
    sum = sum * x + coef[n];
  }

  return sum;
}

void poly::fileSetCoef(int inDeg, double inCoef[])
{
  deg = inDeg;

  coef = new double[deg + 1];
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
  double *coefPrime = new double[deg];

  for (int n = deg - 1; n > 0; n--)
  {
    coefPrime[n] = coef[n + 1] * (n + 1);
  }
  coefPrime[0] = coef[1];

  //std::cout << "Differentiated:\n";

  eqnPrime.fileSetCoef(deg - 1, coefPrime);
  delete[] coefPrime;

  return eqnPrime;
}

bool poly::quadDeg()
{
  return (deg == 0);
}

double poly::synDiv(const double divisor)
{
  double newCoef[deg + 1] = {0};
  newCoef[deg - 1] = coef[deg];
  double remainder = 0;

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
  coef[deg] = 0; //Supposed leading = 0
  deg--;         //Decrement degree
  for (int n = deg; n >= 0; n--)
  {
    coef[n] = newCoef[n];
  }

  return remainder;
}