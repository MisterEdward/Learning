#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // Range-based for loop to iterate over the array
    for (int i : arr) {
        cout << arr[i-1] << " ";
    }
    cout << endl;
    return 0;
}