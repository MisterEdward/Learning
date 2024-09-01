#include <vector>
#include <iostream>

using namespace std;

int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Access elements using the [] operator or at() method
    std::cout << "First element: " << myVector[0] << std::endl; // using []
    std::cout << "Second element: " << myVector.at(1) << std::endl; // using at()

    // Modify elements
    myVector[2] = 10; // change third element to 10

    // Iterate over elements
    for(int value : myVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}