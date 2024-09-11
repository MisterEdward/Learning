#include <iostream> // nu-i chiar problema de acolo. 
#include <vector>   // Asta nu are context de varianta optima, doar ce vede in fata cu una.
using namespace std;    // pentru a face optim trebuie invatat binary tree si tipuri de search :(

int minimumTotal(vector<vector<int>>& triangle) {
        int sum = triangle[0][0], k = 0;
        for(int i = 1; i < triangle.size(); i++) {
            if(triangle[i][k] <= triangle[i][triangle[i].size() - i])
                sum += triangle[i][k];
            else
                sum += triangle[i][++k];
        }
        return sum;
    }

int main() {
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    cout << "Minimum path sum: " << minimumTotal(triangle) << endl;
    return 0;
}
