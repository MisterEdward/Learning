// Create a function that transposes a 2D matrix.
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> transposeMatrix(vector<vector<int>> arr) {
    vector<vector<int>> temp ((arr[0].size()), vector<int> (arr.size()));
	for(int i = 0; i < arr.size(); ++i) {
        for(int j = 0; j < arr[i].size(); ++j) {
            temp[i][j] = arr[j][i];
        }
    }  
    return temp;
}

int main() {
    vector<vector<int>> arr {{1, 1, 1},
                             {2, 2, 2},
                             {3, 3, 3}};

    arr = transposeMatrix(arr);
    for(int i = 0; i < arr.size(); ++i) {
        for(int j = 0; j < arr[i].size(); ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}