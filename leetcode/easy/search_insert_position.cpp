#include <iostream>
#include <vector>
using namespace std;

int searchInsert(vector<int>& nums, int target) {
        int distance = INT_MAX, distance_i;
        for(size_t i = 0; i < nums.size(); ++i) {
            if(nums[i] == target)
                return i;
            
            else if(distance >= (nums[i] - target)) {
                distance = abs(nums[i] - target);
                distance_i = i;
            }

            if(nums[i] + distance == target)
                distance_i = i + 1;             
        }
        return distance_i;
}

/*
int searchInsert(vector<int>& nums, int target) { // better alternative
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] >= target) {
                return i;
            }
        }
        return nums.size();
    }
*/

int main() {
    vector<int> nums = {1, 3, 5, 6};
    int target = 7;
    int index = searchInsert(nums, target);
    cout << "Index of target " << target << " is: " << index << endl;
    return 0;
}