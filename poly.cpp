#include "poly.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>

poly::poly()
{
  deg = 0;
}

poly::poly(int inDeg)
{
  deg = inDeg;
}

poly::~poly()
{
}

void poly::setCoef() //Set degree through iostream
{
  if (deg == 0) //In case degree was not set.
  {
    std::cout << "Enter degree of polynomial: ";
    std::cin >> deg;
  }

  double coefIn = 0; //Temp input variable

  for (int n = 0; n <= deg; n++)
  {
    std::cout << "Coefficient for degree " << n << ": ";
    std::cin >> coefIn;

    coef.push_back(coefIn); //Push input to coefficient vector
  }
}

void poly::dispPoly() //Display to terminal
{
  std::cout << "Degree = " << deg << std::endl;

  for (int n = deg; n >= 0; n--)
  {
    std::cout << real(coef[n]) << "x^" << n << std::endl;
  }

  std::cout << std::endl;
}

std::complex<double> poly::evalPoly(std::complex<double> x)
{
  std::complex<double> eval = {0, 0}; //Variable to hold the evaluation
  for (int n = deg; n >= 0; n--) //Horner's method to evaluate a polynomial
  {
    eval = eval * x + coef[n];
  }

  return eval;
}

void poly::fileSetCoef(int inDeg, std::vector<std::complex<double>> inCoef) //Set coef from a vector
{
  deg = inDeg; //Set degree

  for (int i = 0; i <= deg; i++) //Set coefs
  {
    coef.push_back(inCoef[i]);
  }
}

poly poly::diff() //Differentiate
{
  poly eqnPrime; //poly object to save the derivative
  std::vector<std::complex<double>> coefPrime; //temp vector to save the new coefs

  coefPrime.resize(deg + 1); //Set size of vector

  for (int n = deg - 1; n > 0; n--)
  {
    coefPrime[n] = coef[n + 1] * (double)(n + 1);
  }
  coefPrime[0] = coef[1];

  eqnPrime.fileSetCoef(deg - 1, coefPrime);

  return eqnPrime;
}

bool poly::zero() //Check if degree is 0
{
  return (deg == 0);
}

std::complex<double> poly::synDiv(const std::complex<double> divisor) //Synthetic division
{
  std::complex<double> newCoef[deg + 1];
  newCoef[deg - 1] = coef[deg]; //Leading coefficient is the same
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

bool poly::evalAtGiven(std::vector<std::complex<double>> &roots) //Evaluate and output to terminal
{
  std::cout << "Evaluating polynomial at identified roots:\n";
  std::cout.precision(6);

  for (int n = 0; n < deg; n++)
  {
    std::cout << "f" << std::fixed << roots[n] << " = " << std::scientific << real(evalPoly(roots[n])) << std::endl;
  }

  return true;
}

void poly::coef2File(std::ofstream &out)
{
  out << deg << ":\n";
  
  for (auto i : coef)
  {
    out << i << " ";
  }
  out << std::endl;
}