#include <iostream>
using namespace std;

bool isSafeBridge(string s) {
	for (int i = 0; i < sizeof(s); ++i) {
        if(s[i] == ' '){
            cout << "Not Safe" << endl;
            return false;
        }
    }
    cout << "Safe" << endl;
    return true;
}

int main() {
    isSafeBridge("#####");
    isSafeBridge("#### #");
    isSafeBridge("## ###");
    
    return 0;
}