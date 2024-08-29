#include <iostream>
#include <string>
using namespace std;

int numberSyllables(string word) {
    return count(word.begin(), word.end(), '-') + 1;
}

int main() {
    cout << numberSyllables("buf-fet") << endl;
    cout << numberSyllables("beau-ti-ful") << endl;
    cout << numberSyllables("mon-u-men-tal") << endl;
    cout << numberSyllables("on-o-mat-o-poe-ia") << endl;
}