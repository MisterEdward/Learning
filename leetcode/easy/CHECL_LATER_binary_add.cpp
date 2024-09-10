#include <iostream>
using namespace std;

string addBinary(string a, string b) {
       std::string result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    
    // Add from the end to the beginning
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        
        if (i >= 0) {
            sum += a[i] - '0'; // Convert char to int
            i--;
        }
        
        if (j >= 0) {
            sum += b[j] - '0'; // Convert char to int
            j--;
        }
        
        carry = sum / 2; // Compute carry for next iteration
        result.push_back((sum % 2) + '0'); // Append current bit
    }
    
    // The result is in reverse order, so reverse it back
    std::reverse(result.begin(), result.end());
    return result;
    }
    
int main() {

    return 0;
}