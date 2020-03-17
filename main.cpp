#include "poly.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

int readFile(string filename, poly &eqnRead);
complex<double> newtons(poly eqn, poly prime, complex<double> estimate, int iterations);
bool findRoots(poly eqn, vector<complex<double>> &roots);

int main(int argc, char **argv)
{
  cout << "Hello\n";
  cout.precision(6);
  string filename; //Filename
  vector<complex<double>> roots;

  if (argc == 1) //No arguments
  {
    cout << "filename: ";
    cin >> filename;
  }
  else if (argc == 2) //Filename given
  {
    filename = argv[1];
    cout << "Loading from " << filename << endl
         << endl;
  }
  else //Too many arguments
  {
    cerr << "Too many arguments entered. Terminating program.";
    exit(1);
  }

  poly eqn;

  int inDeg = readFile(filename, eqn); //Read polynomial from file
  eqn.dispPoly();

  findRoots(eqn, roots);
  eqn.evalAtGiven(roots);

  return 0;
}

bool findRoots(poly eqnIn, vector<complex<double>> &roots)
{
  while (!eqnIn.zero())
  {
    roots.push_back(newtons(eqnIn, eqnIn.diff(), {1, -1}, 0));
    cout << "[DEBUG] Root found.\n";
    eqnIn.synDiv(roots.back());
  }

  for (int i = 0; i < roots.size(); i++)
  {
    cout << "Root " << i + 1 << " = " << fixed << roots[i] << endl;
  }
  cout << endl;

  return true;
}

complex<double> newtons(poly eqn, poly prime, complex<double> estimate, int iterations)
{
  if (eqn.evalPoly(estimate) == (complex<double>){0, 0})
  {
    return estimate;
  }

  complex<double> x = estimate - (eqn.evalPoly(estimate) / prime.evalPoly(estimate));

  if ((abs((x - estimate) / estimate)) < 10E-16)
  {
    return estimate;
  }
  else if (iterations >= 500)
  {
    cerr << "[ERROR] Max Iterations reached.\nStopped at" << estimate << endl;
    //exit(1);
    return estimate;
  }

  iterations++;
  return newtons(eqn, prime, x, iterations);
}

int readFile(string filename, poly &eqnRead)
{
  int inDeg;
  vector<complex<double>> inCoef;
  ifstream inFile;

  inFile.open(filename);

  if (!inFile) //If no such file exists, exit.
  {
    cerr << "File does not exist. Terminating program.";
    exit(1);
  }

  inFile >> inDeg; //Read degree in file.
  double temp;

  for (int n = 0; n <= inDeg; n++) //Read coefficients from file.
  {
    inFile >> temp;
    inCoef.push_back(temp);
  }

  eqnRead.fileSetCoef(inDeg, inCoef); //Set coefficients

  return inDeg;
}