#include "poly.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void readFile(string filename, poly &eqnRead);                                           //Function to read from file
complex<double> newtons(poly eqn, poly prime, complex<double> estimate, int iterations); //Newton's Method function
bool findRoots(poly eqn, vector<complex<double>> &roots);                                //Finding all roots using Newton's and Synthetic Division
void saveFile(string filename, poly eqn, vector<complex<double>> roots);

int main(int argc, char **argv)
{
  cout.precision(6);
  string filename;               //Filename
  vector<complex<double>> roots; //Vector for roots

  //Arguments checking
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

  //Poly object for the equation to be solved
  poly eqn;

  readFile(filename, eqn); //Read polynomial from file
  eqn.dispPoly();          //Display the polynomial read

  findRoots(eqn, roots); //Solve for the roots
  eqn.evalAtGiven(roots); //Evaluate the polynomial at roots identified

  //User option to save roots to txt file
  cout << "Would you like to save roots to file? (Y/N) ";
  char save;
  cin >> save;
  if (save == 'Y' || save == 'y')
  {
    cout << "Saving to \"./roots.txt\"";
    saveFile(filename, eqn, roots);
  }
  else
    cout << "Exiting.";

  return 0;
}

bool findRoots(poly eqnIn, vector<complex<double>> &roots) //Starter function to solve roots
{
  while (!eqnIn.zero()) //While polynomial is not of degree 0
  {
    roots.push_back(newtons(eqnIn, eqnIn.diff(), {1, -1}, 0)); //Find one root and push to root vector
    cout << "[DEBUG] Root found.\n";
    eqnIn.synDiv(roots.back()); //Divide by root solved
  }

  for (int i = 0; i < roots.size(); i++)
  {
    cout << "Root " << i + 1 << " = " << fixed << roots[i] << endl;
  }
  cout << endl;

  return true;
}

complex<double> newtons(poly eqn, poly prime, complex<double> estimate, int iterations) //Recursive Newton's Method
{
  complex<double> zero = {0, 0};
  if (eqn.evalPoly(estimate) == zero) //If eqn is evaluated to 0 @root currently being solved
  {
    return estimate; 
  }

  complex<double> x = estimate - (eqn.evalPoly(estimate) / prime.evalPoly(estimate)); //Continue and solve for next estimate (Formula)

  if ((abs((x - estimate) / estimate)) < 10E-16) //Relative error checking
  {
    return estimate;
  }
  else if (iterations >= 500) //In case max iterations is reached and root is not solved
  {
    cerr << "[ERROR] Max Iterations reached.\nStopped at" << estimate << endl;
    //exit(1);
    return estimate;
  }

  iterations++;
  return newtons(eqn, prime, x, iterations); //Call recursive
}

void readFile(string filename, poly &eqnRead) //Reading from txt file
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
}

void saveFile(string filename, poly eqn, vector<complex<double>> roots)
{
  ofstream outFile("roots.txt");

  outFile << "Polynomial from \"" << filename << "\" x0 to x";

  eqn.coef2File(outFile);

  outFile << endl;
  outFile << roots.size() << " computed roots:\n";

  for (auto i : roots)
  {
    outFile << setprecision(10) << i << " ";
  }

  outFile.close();
}