// Create a function that takes an array and finds the integer which appears an odd number of times.
#include <iostream>
#include <vector>

using namespace std;

int findOdd(vector<int> arr) {  // this is still fucking wizardry to me
    int number = 0;
    for (int r : arr) {
        number = number ^ r;    // foloseste XOR pentru a vedea daca numarul apare de un numar 
    }                           // impar de ori, eu nu inteleg cum dar o face
    return number;
}


int main() {
    vector<int> first_example {20, 1, -1, 2, -2, 3, 3, 5, 5, 1, 2, 4, 20, 4, -1, -2, 5};
    vector<int> second_example {20, 1, 1, 2, 2, 3, 3, 5, 5, 4, 20, 4, 5};
    vector<int> third_example {10};
    vector<int> fourth_example {1, 1, 1, 1, 1, 1, 10, 1, 1, 1, 1};
    vector<int> fifth_example {5, 4, 3, 2, 1, 5, 4, 3, 2, 10, 10};

    cout << findOdd(first_example) << endl;
    cout << findOdd(second_example) << endl;
    cout << findOdd(third_example) << endl;
    cout << findOdd(fourth_example) << endl; // o face mai putin in cazuri particulare
    cout << findOdd(fifth_example) << endl;
    return 0;
}

/*
    Acest program definește o funcție `findOdd`, care primește un vector de numere întregi
    și returnează acel număr care apare de un număr impar de ori în vector.

    Algoritmul folosește operația XOR pentru a identifica numărul dorit:
    - XOR (^) are proprietatea de a "anula" numerele care apar de două ori, deoarece `a ^ a = 0`.
    - Prin parcurgerea tuturor elementelor din vector și aplicarea XOR între ele,
      toate numerele care apar de un număr par de ori se vor anula reciproc,
      lăsând doar numărul care apare de un număr impar de ori.

    Notă importantă:
    - Algoritmul funcționează corect doar dacă **exact un singur** număr apare de un număr impar de ori în vector,
      iar restul numerelor apar de un număr par de ori.
    - În cazurile în care mai multe numere apar de un număr impar de ori sau toate apar de un număr par de ori,
      rezultatul poate fi imprevizibil.

    Exemplu de utilizare:
    - Pentru vectorul `{1, 1, 2, -2, 5, 2, 4, 4, -1, -2, 5}`, funcția va returna `-1`,
      deoarece `-1` este singurul număr care apare o singură dată (un număr impar de ori).

    Complexitate:
    - Temporală: O(n), unde n este numărul de elemente din vector.
    - Spațială: O(1), deoarece folosește o singură variabilă auxiliară.
*/