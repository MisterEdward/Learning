#include <iostream>
using namespace std;

int add_2_numbers(int a, int b) {
    return a + b;
}

int main() {
    int a, b;
    cout << "Introdu doua numere: ";
    cin >> a >> b;

    cout << add_2_numbers(a, b);
    return 0;
}