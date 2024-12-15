#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>*> memoryHog; // To hold pointers to vectors
    try {
        while (true) {
            // Allocate a large vector
            vector<int>* v = new vector<int>(1000000, 42); // 1,000,000 integers initialized to 42
            memoryHog.push_back(v); // Store pointer to prevent deallocation
            cout << "Allocated 1,000,000 integers. Total allocations: " << memoryHog.size() << endl;
        }
    } catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
    }
    // Cleanup (optional, since the program will likely crash before reaching here)
    for (auto ptr : memoryHog) {
        delete ptr;
    }
    return 0;
}