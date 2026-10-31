#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // Задача 1
    int a, b, c;
    int* pa, * pb, * pc;
    pa = &a;
    pb = &b;
    pc = &c;

    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;

    int product = (*pa) * (*pb) * (*pc);
    double ser = ((*pa) + (*pb) + (*pc)) / 3.0;

    int minVal = *pa;
    if (*pb < minVal) minVal = *pb;
    if (*pc < minVal) minVal = *pc;

    cout << "Dobutok = " << product << endl;
    cout << "Ser = " << ser << endl;
    cout << "Min = " << minVal << endl;

    // Задача 2
    int arr[10];
    int* p;

    srand(time(0));
    for (p = arr; p < arr + 10; p++)
        *p = -10 + rand() % 21;

    cout << "Prjamo: ";
    for (p = arr; p < arr + 10; p++)
        cout << *p << "\t";
    cout << endl;

    cout << "Zadovt: ";
    for (p = arr + 9; p >= arr; p--)
        cout << *p << "\t";
    cout << endl;

    int sum = 0;
    for (p = arr; p < arr + 10; p++)
        sum += *p;

    cout << "Sum = " << sum << endl;

    return 0;
}
