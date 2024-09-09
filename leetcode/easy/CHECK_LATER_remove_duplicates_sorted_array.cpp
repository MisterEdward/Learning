#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int> nums) {
        if (nums.empty()) return 0;

        int k = 1; // Start with the first element
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[k++] = nums[i];
            }
        }

        return k;
}

int main() {

    return 0;
}