#include "poly.h"
#include "poly.cpp"
#include <fstream>

using namespace std;

int readFile(string filename, poly &eqn);
long double startNewtons(poly eqn, poly prime, long double estimate);
long double newtons(poly eqn, poly prime, long double estimate, int iterations);
bool findRoots(poly eqn, long double **roots);
void quadFormula(poly eqn, long double roots);

int main(int argc, char **argv)
{
  string filename; //Filename
  long double **roots;

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

  //Allocate 2D array for roots
  roots = new long double *[inDeg];
  for (int n = 0; n < inDeg; n++)
  {
    roots[n] = new long double[2];
  }
  for (int n = 0; n < inDeg; n++)
  {
    roots[n][0] = 0;
    roots[n][1] = 0;
  }

  /*cout << "Remainder = " << eqn.synDiv(-4) << endl;
  eqn.dispPoly();*/

  findRoots(eqn, roots);

  return 0;
}

bool findRoots(poly eqn, long double **roots)
{
  int n = 0;
  while (!eqn.quadDeg())
  {
    roots[n][0] = startNewtons(eqn, eqn.diff(), 1);
    eqn.synDiv(roots[n][0]);
    n++;
  }

  for (int i = 0; i < n; i++)
  {
    cout << "Root " << i + 1 << " = " << roots[i][0] << endl;
  }

  return true;
}

long double startNewtons(poly eqn, poly prime, long double estimate)
{
  double root = 0;
  int iterations = 0;

  root = newtons(eqn, prime, estimate, iterations);

  return root;
}

long double newtons(poly eqn, poly prime, long double estimate, int iterations)
{
  if (eqn.evalPoly(estimate) == 0)
  {
    //cout << "[DEBUG] Evaluation zero reached.\n";
    return estimate;
  }

  long double x = estimate - (eqn.evalPoly(estimate) / prime.evalPoly(estimate));

  if ((abs((x - estimate) / estimate)) < 10E-16)
  {
    //cout << "[DEBUG] Relative Error reached: " << abs((x - estimate) / estimate);
    //cout << "\n[DEBUG]New: " << x << "\n[DEBUG]Old: " << estimate << endl;
    return estimate;
  }
  else if (iterations >= 200)
    exit(1);

  iterations++;
  return newtons(eqn, prime, x, iterations);
}

int readFile(string filename, poly &eqn)
{
  int inDeg;
  double *inCoef;
  ifstream inFile;

  inFile.open(filename);

  if (!inFile) //If no such file exists, exit.
  {
    cerr << "File does not exist. Terminating program.";
    exit(1);
  }

  inFile >> inDeg; //Read degree in file.

  inCoef = new double[inDeg + 1]; //Allocate array of length inDeg.
  double temp;

  for (int n = 0; n <= inDeg; n++) //Read coefficients from file.
  {
    inFile >> temp;
    inCoef[n] = temp;
  }

  eqn.fileSetCoef(inDeg, inCoef); //Set coefficients

  delete[] inCoef;
  return inDeg;
}