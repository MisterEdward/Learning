#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int k = 0;
    for(int i = m; i < nums1.size(); ++i) 
        nums1[i] = nums2[k++];
    
    for(int i = 0; i < nums1.size(); ++i) {
        for(int j = 0; j < nums1.size(); ++j) {
            if(nums1[i] < nums1[j]) {
                k = nums1[i];
                nums1[i] = nums1[j];
                nums1[j] = k;
            }
        }
    }
}

int main() {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n = 3;

    merge(nums1, m, nums2, n);

    cout << "Merged array: ";
    for (int num : nums1) 
        cout << num << " ";
    
    cout << endl;
    return 0;
}