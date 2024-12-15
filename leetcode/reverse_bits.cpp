#include <iostream>
#include <vector>
#include <string>
using namespace std;

uint32_t reverseBits(uint32_t n) {  // Converteste BITII, nu numarul; E acelasi concept
    uint32_t rev = 0;               // ca la palindrome doar ce pentru biti, nu pentru numar in sine;
    for(int i = 0; i < 32; i++) {   // adica 00110011 devine 11001100
        rev <<= 1;
        rev |= (n & 1);
        n >>= 1;
    }
    return rev;
}
    
int main() {

    return 0;
}