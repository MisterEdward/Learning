#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int letterDistance(string str1, string str2) {
    int length = min(str1.size(), str2.size()), sum = 0;
	for (int i = 0; i < length; ++i) 
        sum += abs(str1[i] - str2[i]);
    
    return sum + abs((int)str1.size() - (int)str2.size());
}


int main() {
    cout << letterDistance("sharp", "sharq") << endl; // ➞ 1
    cout << letterDistance("abcde", "Abcde") << endl; // ➞ 32
    cout << letterDistance("abcde", "bcdef") << endl; // ➞ 5
    return 0;
}