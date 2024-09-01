// Create a function that tweaks letters by one forward (+1) or backwards (-1) according to an array.
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


string tweakLetters(string s, vector<int> arr) {
    for(size_t i = 0; i < arr.size(); ++i) {
        if(s[i] == 'z' && arr[i] == 1)
            s[i] = 'a';
        else if(s[i] == 'a' && arr[i] == -1)
            s[i] = 'z';
        else
            s[i] += arr[i];
    }
    return s;
}

int main() {
    srand(time(NULL));

    cout << "Introdu un cuvant: ";
    string word; 
    cin >> word;
    vector<int> arr(word.size());
    for(size_t i = 0; i < arr.size(); i++)
        arr[i] = rand() % 3 - 1;
    
    cout << endl << tweakLetters(word, arr);
    return 0;
}