#include "poly.h"
#include "poly.cpp"
#include <fstream>

using namespace std;

int readFile(string filename, poly &eqnRead);
complex<double> startNewtons(poly eqnIn, poly prime, complex<double> estimate);
complex<double> newtons(poly eqnIn, poly prime, complex<double> estimate, int iterations);
bool findRoots(poly eqnIn, complex<double> *roots);

int main(int argc, char **argv)
{
  cout.precision(6);
  string filename; //Filename
  complex<double> *roots;

  complex<double> coefA[3] = {{4, 0}, {4, 0}, {1, 0}};

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
  poly test;

  int inDeg = readFile(filename, eqn); //Read polynomial from file
  test = eqn;
  eqn.dispPoly();

  //Allocate array for roots
  roots = new complex<double>[inDeg];
  for (int n = 0; n < inDeg; n++)
  {
    roots[n] = {0, 0};
  }

  findRoots(eqn, roots);
  eqn.dispPoly();
  eqn.evalAtRoots(roots);

  return 0;  test.fileSetCoef(2, coefA);
}

bool findRoots(poly eqnIn, complex<double> *roots)
{
  int n = 0;

  while (!eqnIn.zero())
  {
    roots[n] = startNewtons(eqnIn, eqnIn.diff(), {1, -1});
    eqnIn.synDiv(roots[n]);
    n++;
  }

  eqnIn.dispPoly();

  for (int i = 0; i < n; i++)
  {
    cout << "Root " << i + 1 << " = " << fixed << roots[i] << endl;
  }

  return true;
}

complex<double> startNewtons(poly eqnIn, poly prime, complex<double> estimate)
{
  complex<double> root = 0;
  int iterations = 0;

  root = newtons(eqnIn, prime, estimate, iterations);

  return root;
}

complex<double> newtons(poly eqnIn, poly prime, complex<double> estimate, int iterations)
{
  if (eqnIn.evalPoly(estimate) == (complex<double>){0, 0})
  {
    //cout << "[DEBUG] Evaluation zero reached.\n";
    return estimate;
  }

  complex<double> x = estimate - (eqnIn.evalPoly(estimate) / prime.evalPoly(estimate));

  if ((abs((x - estimate) / estimate)) < 10E-16)
  {
    return estimate;
  }
  else if (iterations >= 200)
    exit(1);

  iterations++;
  return newtons(eqnIn, prime, x, iterations);
}

int readFile(string filename, poly &eqnRead)
{
  int inDeg;
  complex<double> *inCoef;
  ifstream inFile;

  inFile.open(filename);

  if (!inFile) //If no such file exists, exit.
  {
    cerr << "File does not exist. Terminating program.";
    exit(1);
  }

  inFile >> inDeg; //Read degree in file.

  inCoef = new complex<double>[inDeg + 1]; //Allocate array of length inDeg.
  double temp;

  for (int n = 0; n <= inDeg; n++) //Read coefficients from file.
  {
    inFile >> temp;
    inCoef[n] = temp;
  }

  eqnRead.fileSetCoef(inDeg, inCoef); //Set coefficients

  delete[] inCoef;
  return inDeg;
}