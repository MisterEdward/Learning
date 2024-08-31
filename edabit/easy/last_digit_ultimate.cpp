#include <iostream>
using namespace std;

int lastDig(int a, int b, int c) {
    if(a % 10 * b % 10 == c % 10)
        return true;
    
    return false;
}

int main() {
    if (lastDig(25, 21, 125))
        cout << "True" << endl;

    if( lastDig(55, 226, 5190))
        cout << "True" << endl;

    if (lastDig(12, 215, 2142))
        cout << "False" << endl;
    return 0;
}