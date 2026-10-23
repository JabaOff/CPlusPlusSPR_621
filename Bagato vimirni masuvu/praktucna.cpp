#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main()
{
    // Zadacha 1
    /*
        int a[4][3];
        srand(time(0));
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                a[i][j] = -10 + rand() % 21;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int cnt = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] != 0)
                    cnt++;

        cout << "cnt = " << cnt << endl;
    */

    // Zadacha 2
    /*
        int a[3][3];
        srand(time(0));
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                a[i][j] = rand() % 3 - 1;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int cnt = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] == 0)
                    cnt++;

        cout << "cnt = " << cnt << endl;
    */

    // Zadacha 3
    /*
        int a[7][3];
        srand(time(0));
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 3; j++)
            {
                a[i][j] = -20 + rand() % 40;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int cnt = 0;
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 3; j++)
                if (abs(a[i][j]) < 12)
                    cnt++;

        cout << "cnt = " << cnt << endl;
    */

    // Zadacha 4
    /*
        int a[4][5];
        srand(time(0));
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 5; j++)
            {
                a[i][j] = -10 + rand() % 21;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int cnt = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 5; j++)
                if (a[i][j] > 0)
                    cnt++;

        cout << "cnt = " << cnt << endl;
    */

    // Zadacha 5
    /*
        double a[5][4];
        srand(time(0));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j] = -10.0 + rand() % 20;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        double product = 1.0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (a[i][j] > 0)
                    product *= a[i][j];

        cout << "Dobutok = " << product << endl;
    */

    // Zadacha 6
    /*
        double a[5][4];
        srand(time(0));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j] = -10.0 + rand() % 20;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        double product = 1.0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (a[i][j] < 0)
                    product *= a[i][j];

        cout << "Dobutok = " << product << endl;
    */

    // Zadacha 7
    /*
        int a[4][4];
        srand(time(0));
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j] = -20 + rand() % 41;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int cnt = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if ((a[i][j] % 6 + 6) % 6 == 1)
                    cnt++;

        cout << "cnt = " << cnt << endl;
    */

    // Zadacha 8
    /*
        int a[5][6];
        srand(time(0));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
            {
                a[i][j] = -20 + rand() % 41;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int min = a[0][0];
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
                if (a[i][j] < min)
                    min = a[i][j];

        cout << "Min = " << min << endl;
    */

    // Zadacha 9
    /*
        int a[5][6];
        srand(time(0));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
            {
                a[i][j] = -20 + rand() % 41;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        int max = a[0][0];
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 6; j++)
                if (a[i][j] > max)
                    max = a[i][j];

        cout << "Max = " << max << endl;
    */

    // Zadacha 10
    /*
        double a[5][4];
        srand(time(0));
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j] = -10.0 + rand() % 20;
                cout << a[i][j] << "\t";
            }
            cout << endl;

        double sum = 0.0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (a[i][j] < 0)
                    sum += a[i][j];

        cout << "Sum = " << sum << endl;
    */

    return 0;
}