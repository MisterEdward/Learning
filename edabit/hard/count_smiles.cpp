#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int countSmileys(vector<string> arr) {
    int faces = 0;
    vector<string> face {":)", ";)", ":D", ";D", ":-)", ";-)", ":-D", ";-D", ":~)", ";~)", ":~D", ";~D"};
	for(string i : arr) {
        for(string j : face) {
            if(i == j)
                faces++;
        }
    }
    return faces;
}

int main() {
    // Test case 1: Empty vector
    cout << countSmileys({}) << endl; // Expected output: 0

    // Test case 2: No smiley faces
    cout << countSmileys({"Hello", "World", "123"}) << endl; // Expected output: 0

    // Test case 3: Single smiley face
    cout << countSmileys({":D"}) << endl; // Expected output: 1

    // Test case 4: Multiple smiley faces
    cout << countSmileys({":)", ";)", ":D", ";D", ":-)", ";-)", ":-D", ";-D", ":~)", ";~)", ":~D", ";~D"}) << endl; // Expected output: 12

    // Test case 5: Smileys with other characters
    cout << countSmileys({":)", "Hello", ";)", "World", ":D", "123", ";D", ":-)", ";-)", ":-D", ";-D", ":~)", ";~)", ":~D", ";~D"}) << endl; // Expected output: 12

    return 0;
}