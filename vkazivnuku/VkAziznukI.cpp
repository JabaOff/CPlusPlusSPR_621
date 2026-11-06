#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int arr[8], * p, i, j, tmp, t;
    srand(time(0));

    // Задача 3
    for (p = arr; p < arr + 8; p++)
        *p = -15 + rand() % 31;
    for (p = arr; p < arr + 8; p++)
        cout << *p << "\t";
    cout << endl;

    int* minP = arr, * maxP = arr;
    for (p = arr + 1; p < arr + 8; p++)
    {
        if (*p < *minP) minP = p;
        if (*p > *maxP) maxP = p;
    }
    tmp = *minP;
    *minP = *maxP;
    *maxP = tmp;
    for (p = arr; p < arr + 8; p++)
        cout << *p << "\t";
    cout << endl;

    // Задача 4
    for (i = 0; i < 7; i++)
        arr[i] = i + 1;
    for (p = arr; p < arr + 7; p++)
        cout << *p << "\t";
    cout << endl;
    for (i = 0; i + 1 < 7; i += 2)
    {
        int* pe = &arr[i], * po = &arr[i + 1];
        t = *pe;
        *pe = *po;
        *po = t;
    }
    for (p = arr; p < arr + 7; p++)
        cout << *p << "\t";
    cout << endl;

    // Задачі на додатковий бал

    // Дод. 1
    int x1, x2;
    cout << "x1 = "; cin >> x1;
    cout << "x2 = "; cin >> x2;
    p = &x1;
    if (x2 < x1) p = &x2;
    *p += 10;
    cout << "x1 = " << x1 << ", x2 = " << x2 << endl;

    // Дод. 2
    int a = 5, b = 9;
    tmp = a; a = b; b = tmp;
    cout << "a = " << a << ", b = " << b << endl;

    // Дод. 3
    for (i = 0; i < 8; i++)
        arr[i] = -10 + rand() % 21;
    for (i = 0; i < 8; i++)
        if (arr[i] < 0) arr[i] = 0;
    for (i = 0; i < 8; i++)
        cout << arr[i] << "\t";
    cout << endl;

    // Дод. 4
    int mat[3][4];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            mat[i][j] = i * 4 + j + 1;
    for (i = 0; i < 3; i++)
    {
        tmp = mat[i][0];
        mat[i][0] = mat[i][1];
        mat[i][1] = tmp;
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
            cout << mat[i][j] << "\t";
        cout << endl;
    }

    return 0;
}
