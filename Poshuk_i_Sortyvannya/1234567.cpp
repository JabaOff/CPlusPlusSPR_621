#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Zadacha 1
void sortArr(int a[], int n, int order = 1)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (order == 1)
            {
                if (a[j] < a[j + 1])
                {
                    int tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                }
            }
            else
            {
                if (a[j] > a[j + 1])
                {
                    int tmp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = tmp;
                }
            }
        }
}

int main()
{
    int a[10];
    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        a[i] = -20 + rand() % 41;
        cout << a[i] << "\t";
    }
    cout << endl;

    sortArr(a, 10, 1);

    cout << "Za spadannya:" << endl;
    for (int i = 0; i < 10; i++)
        cout << a[i] << "\t";
    cout << endl;

    int b[10];
    for (int i = 0; i < 10; i++)
        b[i] = -20 + rand() % 41;

    cout << "Pochatkovий:" << endl;
    for (int i = 0; i < 10; i++)
        cout << b[i] << "\t";
    cout << endl;

    sortArr(b, 10, 0);

    cout << "Za zrostannya:" << endl;
    for (int i = 0; i < 10; i++)
        cout << b[i] << "\t";
    cout << endl;

    int c[10];
    for (int i = 0; i < 10; i++)
        c[i] = -20 + rand() % 41;

    cout << "Pochatkovий:" << endl;
    for (int i = 0; i < 10; i++)
        cout << c[i] << "\t";
    cout << endl;

    sortArr(c, 10);

    cout << "Za spadannya (default):" << endl;
    for (int i = 0; i < 10; i++)
        cout << c[i] << "\t";
    cout << endl;

    return 0;
}
