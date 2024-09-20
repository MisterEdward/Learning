#include <iostream>
#include <vector>
#include <string>
using namespace std;

int closest_to_zero(vector<int>& array) {
    int distance = array[0];
    for(int i : array) {
        if(abs(i) < abs(distance))
            distance = i;
        else if(abs(i) == abs(distance) && i > distance)
            distance = i;
    }
    return distance;
}

int main() {
    vector<int> array {};
    return 0;
}