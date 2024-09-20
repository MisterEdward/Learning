// Aceeasi chestie a wizardry_find_the_odd_integer, doar ca dat seama cum lucreaza
// Solutia asta merge daca avem EXCLUSIV un vector cu elemente care se repeta de doua ori
// EXCEPTIE facant doar UNUL care nu se repeta.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int singleNumber(vector<int>& nums) {
    int app = 0;
    for(int i : nums)
        app = app ^ i;

    return app;
}

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << "The single number is: " << singleNumber(nums) << endl;
    return 0;
}