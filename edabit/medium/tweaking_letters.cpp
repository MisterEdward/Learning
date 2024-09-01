// Create a function that tweaks letters by one forward (+1) or backwards (-1) according to an array.
#include <iostream>
#include <vector>
using namespace std;

string tweakLetters(string s, vector<int> arr) {
    for(int i : arr) {
        if(arr[i] == 1)
            s[i] += 1;
        else if(arr[i] == -1)
            s[i] -= 1;
    }

    return s;
}

int main() {
    cout << "Introdu un cuvant: ";
    string word; 
    cin >> word;
    vector<int> arr = {1, 1, 0, -1, -1};

    cout << endl << tweakLetters(word, arr);
    return 0;
}