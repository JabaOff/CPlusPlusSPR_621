#include <iostream>
#include <algorithm>
using namespace std;

int main()
{

    // Zadacha 1
    /*
        int i = 14;
        while (i <= 123)
        {
            cout << i << " ";
            i++;
        }
        cout << endl;
    */


    // Zadacha 2
    /*
        int i = 1;
        while (i <= 100)
        {
            cout << i << " ";
            i += 2;
        }
        cout << endl;
    */


    // Zadacha 3
    /*
        int N, x, cnt = 0, i = 1;
        cout << "N = ";
        cin >> N;
        while (i <= N)
        {
            cout << "a[" << i << "] = ";
            cin >> x;
            if (x < 0) cnt++;
            i++;
        }
        cout << "cnt = " << cnt << endl;
    */


    // Zadacha 4
    /*
        double x, product = 1.0, sum = 0.0;
        int i = 1;
        while (i <= 8)
        {
            cout << "a[" << i << "] = ";
            cin >> x;
            product *= x;
            sum += x;
            i++;
        }
        cout << "Dobutok = " << product << endl;
        cout << "Ser = " << sum / 8 << endl;
    */


    // Zadacha 5
    /*
        int i = 100;
        do
        {
            cout << i << " ";
            i -= 2;
        } while (i >= 2);
        cout << "1" << endl;
    */


    // Zadacha 6
    /*
        double x, product = 1.0;
        int i = 1;
        do
        {
            cout << "a[" << i << "] = ";
            cin >> x;
            product *= x;
            i++;
        } while (i <= 5);
        cout << "Dobutok = " << product << endl;
    */


    // Zadacha 7
    /*
        int i, sum;
        i = 0; sum = 0;
        while (i < 50)
        {
            if (i % 4 == 0) sum += i;
            i++;
        }
        cout << "while sum = " << sum << endl;

        i = 0; sum = 0;
        do
        {
            if (i % 4 == 0) sum += i;
            i++;
        } while (i < 50);
        cout << "do-while sum = " << sum << endl;
    */


    // Zadacha 8
    /*
        int N, i = 0;
        cout << "N = ";
        cin >> N;
        while (i <= N)
        {
            cout << i << " ";
            i++;
        }
        cout << endl;
    */


    // Zadacha 9
    /*
        int a, b, lo, hi, i;
        cout << "a = "; cin >> a;
        cout << "b = "; cin >> b;
        lo = min(a, b);
        hi = max(a, b);

        cout << "Vsi: ";
        for (i = lo; i <= hi; i++)
            cout << i << " ";
        cout << endl;

        cout << "Parni: ";
        for (i = lo; i <= hi; i++)
            if (i % 2 == 0) cout << i << " ";
        cout << endl;

        cout << "Nepar: ";
        for (i = lo; i <= hi; i++)
            if (i % 2 != 0) cout << i << " ";
        cout << endl;

        cout << "Krat 7: ";
        for (i = lo; i <= hi; i++)
            if (i % 7 == 0) cout << i << " ";
        cout << endl;
    */


    // Zadacha 10
    /*
        int a, b, lo, hi, i, sum = 0;
        cout << "a = "; cin >> a;
        cout << "b = "; cin >> b;
        lo = min(a, b);
        hi = max(a, b);
        for (i = lo; i <= hi; i++)
            sum += i;
        cout << "Sum = " << sum << endl;
    */


    // Zadacha 11
    /*
        double x, sum = 0;
        do
        {
            cout << "x = ";
            cin >> x;
            sum += x;
        } while (x != 0);
        cout << "Sum = " << sum << endl;
    */

    return 0;
}
