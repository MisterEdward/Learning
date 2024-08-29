#include <iostream>
#include <string>
using namespace std;

int numberSyllables(string word) {
    int syllables = 0;
    for(int i = 0 ; i < word.size(); i++) {
        if(word[i] == '-')
            syllables++;
    }
    return syllables;
}

int main() {
    cout << numberSyllables("buf-fet") << endl;
    cout << numberSyllables("beau-ti-ful") << endl;
    cout << numberSyllables("mon-u-men-tal") << endl;
    cout << numberSyllables("on-o-mat-o-poe-ia") << endl;
}