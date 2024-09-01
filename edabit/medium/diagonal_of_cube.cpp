#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

double cubeDiagonal(double volume) {
    return pow(volume, (double)1/3) * sqrt(3);
}

int main() {
    double volume;
    cout << "Introdu volumul cubului: ";
    cin >> volume;

    cout << endl << cubeDiagonal(volume);
    return 0;
}