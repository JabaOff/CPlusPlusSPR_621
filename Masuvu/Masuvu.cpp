#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // Zadacha 1
    /*
        int a[10];
        double product = 1.0;
        for (int i = 0; i < 10; i++)
        {
            cout << "a[" << i + 1 << "] = ";
            cin >> a[i];
            product *= a[i];
        }

        for (int i = 0; i < 10; i++)
            cout << a[i] << " ";
        cout << endl;

        cout << "Dobutok = " << product << endl;
    */

    // Zadacha 2
    /*
        int a[7];
        int neg = 0, pos = 0;
        srand(time(0));

        for (int i = 0; i < 7; i++)
        {
            a[i] = -12 + rand() % 63;
            cout << a[i] << "\t";
            if (a[i] < 0) neg++;
            else if (a[i] > 0) pos++;
        }
        cout << endl;

        cout << "neg = " << neg << endl;
        cout << "pos = " << pos << endl;
    */

    // Zadacha 3
    /*
        long a[7] = {10, 25, 3, 42, 7, 18, 9};

        for (int i = 0; i < 7; i++)
            cout << a[i] << " ";
        cout << endl;

        long sum = 0;
        for (int i = 0; i < 7; i++)
            if (a[i] % 2 == 0)
                sum += a[i];

        cout << "Sum parnih = " << sum << endl;
    */

    // Zadacha 4
    /*
        int a[10];

        for (int i = 0; i < 10; i++)
            a[i] = 1 << (i + 1);

        cout << "Prjame:" << endl;
        for (int i = 0; i < 10; i++)
            cout << a[i] << " ";
        cout << endl;

        cout << "Oberzene:" << endl;
        for (int i = 9; i >= 0; i--)
            cout << a[i] << " ";
        cout << endl;
    */

    // Zadacha 5
    /*
        int a[10];
        for (int i = 0; i < 10; i++)
        {
            cout << "a[" << i + 1 << "] = ";
            cin >> a[i];
        }

        for (int i = 0; i < 10; i++)
            if (a[i] < 0)
                a[i] = a[i] * -1;

        for (int i = 0; i < 10; i++)
            cout << a[i] << " ";
        cout << endl;
    */

    return 0;
}
