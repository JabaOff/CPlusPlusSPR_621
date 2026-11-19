// Завдання 1
// #include <iostream>
// using namespace std;
//
// int main() {
//     int* a = new int(5);
//     double* b = new double(3.14);
//     float* c = new float(2.0f);
//
//     cout << "a = " << *a << endl;
//     cout << "b = " << *b << endl;
//     cout << "c = " << *c << endl;
//
//     double product = *a * *b * *c;
//     cout << "Добуток = " << product << endl;
//
//     delete a;
//     delete b;
//     delete c;
//
//     return 0;
// }

// Завдання 2
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int* createArray(int size) {
    int* arr = new int[size];
    return arr;
}

void fillArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 101;
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << i + 1 << "] - " << arr[i] << endl;
    }
}

void deleteLast(int*& arr, int& size) {
    int* newArr = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size--;
}

void addAtPosition(int*& arr, int& size, int pos, int value) {
    int* newArr = new int[size + 1];
    for (int i = 0; i < size + 1; i++) {
        if (i < pos)       newArr[i] = arr[i];
        else if (i == pos) newArr[i] = value;
        else               newArr[i] = arr[i - 1];
    }
    delete[] arr;
    arr = newArr;
    size++;
}

int main() {
    srand(time(0));

    int size = 5;
    int* arr = createArray(size);
    fillArray(arr, size);

    cout << "Початковий масив:" << endl;
    printArray(arr, size);

    deleteLast(arr, size);
    cout << "\nПісля видалення останнього:" << endl;
    printArray(arr, size);

    addAtPosition(arr, size, 2, 99);
    cout << "\nПісля додавання 99 на позицію 3:" << endl;
    printArray(arr, size);

    delete[] arr;

    return 0;
}
