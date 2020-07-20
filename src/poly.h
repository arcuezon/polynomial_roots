#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>

/*
  Poly class that represents a polynomial of nth degree with options for
  input and setting the coefficients. Coefficients can be complex and all 
  functions that deal with values are capable of handling complex numbers including returns. 
  All variables are private.
*/
class poly
{
private:
  unsigned short int deg; //Degree is stored here
  std::vector<std::complex<double>> coef; //Vector to contain coefficients 

public:
  poly();
  //Constructor that sets the degree to 0

  ~poly();
  //Dstor

  poly(int inDeg);
  //Constructor that will set the degree to a specified value

  void setCoef();
  //A function to set the coefficient after the instantation of the object by iostream.

  void dispPoly();
  //Function to display the polynomial in the terminal

  std::complex<double> evalPoly(std::complex<double> x);
  //Function that evaluates at a specific point given and returns the answer.

  void fileSetCoef(int inDeg, std::vector<std::complex<double>> inCoef);
  //Function to set the coefficients from values from a input vector and is used
  //primarily to input coefficients from a file given thus the name. However,
  //the input has to be a vector containing these coefficients and not a file or file name.

  poly diff();
  //Function that returns the 1st derivative of tht object.

  bool zero();
  //Returns true if the equation has a degree of 0

  std::complex<double> synDiv(const std::complex<double> divisor);
  //Function that performs synthetic division on the current equation and overwrites
  //the current object values. The function returns the remainder of the division.

  bool evalAtGiven(std::vector<std::complex<double>> &roots);
  //Function that evaluates the polynomial at a number of given points (primarily used 
  //for roots therefore the naming of the vector) and displays the evaluated values to
  //to the terminal. Since the function is used here only to solve the computed roots and
  //pressumed to evaluate to 0, the function only displays the real part of the evaluation.

  void coef2File(std::ofstream &out);
  //Outputs the coefficient to a ofstream object.
};

#endif