#include <iostream>
#include <string>
using namespace std;

bool isValidHexCode(string str) {
	if(str.size() != 7 || str[0] != '#')
        return false;
    
    for (int i = 1; i < str.size(); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'f') || 
            (str[i] >= 'A' && str[i] <= 'F') || 
            (str[i] >= '0' && str[i] <= '9'))) 
                return false;
    }
    return true;
}

int main() {
    // make a small test for the function
    string hexCode = "#FF0000";
    if (isValidHexCode(hexCode)) {
        cout << "Valid hex code" << endl;
    } else {
        cout << "Invalid hex code" << endl;
    }
    return 0;
}