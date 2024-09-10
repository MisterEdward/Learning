#include <iostream>
#include <string>
using namespace std;

int lengthOfLastWord(string s) { // needs completing, doesnt work for "  abc abc  " and such
        int count = 0;
        for(int i = 1; i < s.size(); ++i) {
            if(s[i] == ' ')
                count = 0;
                
            else
                count++;
        }
        return count;
}

int main() {
string testStr = "   fly me   to   the moon  ";
cout << "Length of last word: " << lengthOfLastWord(testStr) << endl;
    return 0;
}