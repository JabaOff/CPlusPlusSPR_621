#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Zadacha 1
/*
double Pow(double num, int step)
{
    if (step == 1)
        return num;
    return num * Pow(num, step - 1);
}
*/

// Zadacha 2
/*
void printStars(int n)
{
    if (n <= 0)
        return;
    cout << "*";
    printStars(n - 1);
}
*/

// Zadacha 3
/*
int sumRange(int a, int b)
{
    if (a > b)
        return 0;
    return a + sumRange(a + 1, b);
}
*/

int main()
{
    // Zadacha 1
    /*
        double num;
        int step;
        cout << "num = "; cin >> num;
        cout << "step = "; cin >> step;
        cout << num << "^" << step << " = " << Pow(num, step) << endl;
    */

    // Zadacha 2
    /*
        int n;
        cout << "N = "; cin >> n;
        printStars(n);
        cout << endl;
    */

    // Zadacha 3
    /*
        int a, b;
        cout << "a = "; cin >> a;
        cout << "b = "; cin >> b;
        cout << "Sum[" << a << ".." << b << "] = " << sumRange(a, b) << endl;
    */

    return 0;
}