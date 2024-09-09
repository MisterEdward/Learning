#include <iostream>
#include <unordered_map>
using namespace std;

int romanToInt(string s) {
        unordered_map<char, int> m;
        
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
        
        int answer = 0;
        for(int i = 0; i < s.size(); ++i) {
                if(m[s[i]] < m[s[i + 1]])
                    answer -= m[s[i]];
                else
                    answer += m[s[i]];
        }

        return answer;
    }

int main() {
    string test1 = "III";
    string test2 = "IV";
    string test3 = "IX";
    string test4 = "LVIII";
    string test5 = "MCMXCIV";

    cout << "Roman numeral: " << test1 << " -> Integer: " << romanToInt(test1) << endl; // Expected: 3
    cout << "Roman numeral: " << test2 << " -> Integer: " << romanToInt(test2) << endl; // Expected: 4
    cout << "Roman numeral: " << test3 << " -> Integer: " << romanToInt(test3) << endl; // Expected: 9
    cout << "Roman numeral: " << test4 << " -> Integer: " << romanToInt(test4) << endl; // Expected: 58
    cout << "Roman numeral: " << test5 << " -> Integer: " << romanToInt(test5) << endl; // Expected: 1994
    return 0;
}