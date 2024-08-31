#include <iostream>
using namespace std;

void doubleChar(std::string str) {
	for(int i = 0; i < str.size(); ++i) {
        cout << str[i] << str[i];
    }
    cout << endl;
}

int main() {
    doubleChar("String"); // ➞ "SSttrriinngg"

    doubleChar("Hello World!"); // ➞"HHeelllloo  WWoorrlldd!!"

    doubleChar("1234!_ "); // ➞ "11223344!!__  "
        return 0;
}