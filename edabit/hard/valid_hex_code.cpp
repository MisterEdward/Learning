#include <iostream>
#include <string>
using namespace std;

bool isValidHexCode(string str) {
	if(str.size() != 6 && str[0] != '#')
        return false;
    
    for (int i = 1; i < str.size(); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'f') || 
            (str[i] >= 'A' && str[i] <= 'A') || 
            (str[i] >= '0' && str[i] <= '9'))) 
                return false;
    }
    return true;
}

int main() {
    
    return 0;
}