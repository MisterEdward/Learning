#include <iostream>
using namespace std;

bool isPalindrome(int x) {
    if(x < 0)
        return false;
        
    long int rev = 0, x_copy = x;
    for(int i = 0; x_copy != 0; ++i) {
        rev = rev * 10 + x_copy % 10;
        x_copy = x_copy / 10;
    }

    return (rev == x);
}

int main() {
    int x;
    cin >> x;
    if(isPalindrome(x))
        cout << "true";
    return 0;
}