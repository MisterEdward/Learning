#include <iostream>
#include <vector>
using namespace std;

int combinations(int *items, size_t size) {
	int result = 1;
	for(int i = 0; i < size; ++i)
		if(*(items + i))
			result *= *(items + i);
	
	return result;
}

int main() {
	int items[] = {1, 2, 3, 4, 5};
	cout << combinations(&items[0], sizeof(items)/sizeof(items[0]));
	return 0;
}