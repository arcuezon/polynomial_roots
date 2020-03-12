#include "poly.h"
#include "poly.cpp"
#include <fstream>

using namespace std;

void hi(poly h)
{
    h.synDiv(4);
}

int main()
{
    complex<double> coefA[3] = {{4, 0}, {4, 0}, {1, 0}};
    complex<double> coefB[4] = {{4, 0}, {4, 0}, {1, 0}, {2, 0}};
    complex<double> roots[2] = {0};

    cout << "test" << endl;

    poly test;
    poly test2;

    test.fileSetCoef(2, coefA);
    test2.fileSetCoef(3, coefB);

    test.dispPoly();
    test2.dispPoly();

    //test.synDiv(2);
    //test.synDiv(2);
    hi(test);
    hi(test2);

    test.dispPoly();
    test2.dispPoly();

    return 0;
}