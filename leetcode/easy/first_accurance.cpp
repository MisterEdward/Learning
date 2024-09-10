#include <iostream>
#include <string>
using namespace std;

int strStr(string haystack, string needle) {
        return (haystack.find(needle) == std::string::npos) ? -1 : haystack.find(needle);
}

int main() {
    string haystack = "hello";
    string needle = "ll";
    int index = strStr(haystack, needle);
    cout << "The first occurrence of \"" << needle << "\" in \"" << haystack << "\" is at index: " << index << endl;

    haystack = "aaaaa";
    needle = "bba";
    index = strStr(haystack, needle);
    cout << "The first occurrence of \"" << needle << "\" in \"" << haystack << "\" is at index: " << index << endl;

    haystack = "";
    needle = "";
    index = strStr(haystack, needle);
    cout << "The first occurrence of \"" << needle << "\" in \"" << haystack << "\" is at index: " << index << endl;
return 0;
}