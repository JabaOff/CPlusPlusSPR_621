#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Zadacha 1
/*
void rect(int n, int k)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            cout << "* ";
        cout << endl;
    }
}
*/

// Zadacha 2
/*
long fact(int n)
{
    long f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}
*/

// Zadacha 3
/*
bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
*/

// Zadacha 4
/*
void minMax(int a[], int n, int &mnVal, int &mnIdx, int &mxVal, int &mxIdx)
{
    mnVal = mxVal = a[0];
    mnIdx = mxIdx = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] < mnVal)
        {
            mnVal = a[i];
            mnIdx = i;
        }
        if (a[i] > mxVal)
        {
            mxVal = a[i];
            mxIdx = i;
        }
    }
}
*/

// Zadacha 5
/*
double cube(double x)
{
    return x * x * x;
}
*/

// Zadacha 6
/*
bool isPositive(double x)
{
    return x > 0;
}
*/

// Zadacha 7
/*
bool isLeap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int dayCount(int d, int m, int y)
{
    static int md[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for (int i = 1; i < y; i++)
    {
        days += 365;
        if (isLeap(i)) days++;
    }
    for (int i = 1; i < m; i++)
    {
        days += md[i];
        if (i == 2 && isLeap(y)) days++;
    }
    days += d;
    return days;
}
*/

// Zadacha 8
/*
double avg(int a[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum / n;
}
*/

// Zadacha 9
/*
void countElements(int a[], int n, int &pos, int &neg, int &zero)
{
    pos = neg = zero = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0) pos++;
        else if (a[i] < 0) neg++;
        else zero++;
    }
}
*/

int main()
{
    // Zadacha 1
    /*
        int n, k;
        cout << "N = "; cin >> n;
        cout << "K = "; cin >> k;
        rect(n, k);
    */

    // Zadacha 2
    /*
        int x;
        cout << "n = "; cin >> x;
        cout << x << "! = " << fact(x) << endl;
    */

    // Zadacha 3
    /*
        int x;
        cout << "n = "; cin >> x;
        cout << "Proste? " << (isPrime(x) ? "Tak" : "Ni") << endl;
    */

    // Zadacha 4
    /*
        int a[8];
        srand(time(0));
        for (int i = 0; i < 8; i++)
        {
            a[i] = -10 + rand() % 21;
            cout << a[i] << "\t";
        }
        cout << endl;

        int mnVal, mnIdx, mxVal, mxIdx;
        minMax(a, 8, mnVal, mnIdx, mxVal, mxIdx);

        cout << "Min = " << mnVal << " (idx " << mnIdx << ")" << endl;
        cout << "Max = " << mxVal << " (idx " << mxIdx << ")" << endl;
    */

    // Zadacha 5
    /*
        double x;
        cout << "x = "; cin >> x;
        cout << "x^3 = " << cube(x) << endl;
    */

    // Zadacha 6
    /*
        double x;
        cout << "x = "; cin >> x;
        cout << "Dodatne? " << (isPositive(x) ? "Tak" : "Ni") << endl;
    */

    // Zadacha 7
    /*
        int d1, m1, y1, d2, m2, y2;
        cout << "Data 1 (d m y): ";
        cin >> d1 >> m1 >> y1;
        cout << "Data 2 (d m y): ";
        cin >> d2 >> m2 >> y2;

        int days1 = dayCount(d1, m1, y1);
        int days2 = dayCount(d2, m2, y2);
        int diff = abs(days1 - days2);

        cout << "Riznytsya = " << diff << " dniv" << endl;
    */

    // Zadacha 8
    /*
        int a[10];
        srand(time(0));
        for (int i = 0; i < 10; i++)
        {
            a[i] = -10 + rand() % 21;
            cout << a[i] << "\t";
        }
        cout << endl;

        cout << "Ser = " << avg(a, 10) << endl;
    */

    // Zadacha 9
    /*
        int a[10];
        srand(time(0));
        for (int i = 0; i < 10; i++)
        {
            a[i] = -5 + rand() % 11;
            cout << a[i] << "\t";
        }
        cout << endl;

        int pos, neg, zero;
        countElements(a, 10, pos, neg, zero);

        cout << "Dodatni = " << pos << endl;
        cout << "Vid'ємні = " << neg << endl;
        cout << "Nullovi = " << zero << endl;
    */

    return 0;
}
