// SLOW AS FUCKING BALLS - Better approach incoming Soon™
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int countConsistentStrings(string allowed, vector<string>& words) {
    int consistent = 0, check = 0;
    for(int i = 0; i < words.size(); i++) {
        for(int j = 0; j < words[i].size(); j++) {
            check = 0;
            for(int k = 0; k < allowed.size(); k++) 
                if(allowed[k] == words[i][j])
                    check++;
                if(check == 0)
                    break;
        }
            if(check >= 1)
               consistent++;
    }
    return consistent;    
}
    
int main() {

    return 0;
}