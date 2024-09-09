#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
    if (m * n != original.size())
        return vector<vector<int>>();

    vector<vector<int>> matrix(m, vector<int>(n));
    int ind = 0;
    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j)
            matrix[i][j] = original[ind++];

    return matrix;
}

int main() { // AI Generated Test dont judge me...| Leetcode 109/109
    // Test case 1
    vector<int> original1 = {1, 2, 3, 4, 5, 6};
    int m1 = 2;
    int n1 = 3;
    vector<vector<int>> result1 = construct2DArray(original1, m1, n1);
    cout << "Test case 1:" << endl;
    for (const auto& row : result1) {
        for (const auto& num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Test case 2
    vector<int> original2 = {1, 2, 3, 4, 5, 6};
    int m2 = 3;
    int n2 = 2;
    vector<vector<int>> result2 = construct2DArray(original2, m2, n2);
    cout << "Test case 2:" << endl;
    for (const auto& row : result2) {
        for (const auto& num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}



