#include<iostream>
using namespace std;

int main()
{
        //Задача 1
        /*double a, b, c;    cout << "Введіть три числа: ";    cin >> a >> b >> c;    double sum = a + b + c;    cout << "Ви ввели числа: " << a << ", " << b << ", " << c << endl;    cout << "Їх сума: " << sum << endl;*/


        //Задача 2
        //double a, b;
        //cout << "Введіть два числа: ";
        //cin >> a >> b;

        //double average = (a + b) / 2.0;

        //cout << "Середнє арифметичне: " << average << endl;


        //Задача 3
        //double kilometers;
        //cout << "Введіть кількість кілометрів: ";
        //cin >> kilometers;
        //
        //double meters = kilometers * 1000;
        //
        //cout << kilometers << " км = " << meters << " м" << endl;


        //Задача 4
        //const double PRICE_1 = 25.50;
        //const double PRICE_2 = 120.00;
        //const double PRICE_3 = 15.20;
        //const double PRICE_4 = 340.00;

        //int qty1, qty2, qty3, qty4;
        //cout << "Введіть кількість для 4 товарів (через пробіл): ";
        //cin >> qty1 >> qty2 >> qty3 >> qty4;

        //double totalCost = (PRICE_1 * qty1) + (PRICE_2 * qty2) + (PRICE_3 * qty3) + (PRICE_4 * qty4);

        //cout << "Загальна вартість покупки: " << totalCost << " грн" << endl;


        //Задача 5
        //double number;
        //cout << "Введіть число: ";
        //cin >> number;

        //double square = number * number;

        //cout << "Квадрат числа " << number << " дорівнює " << square << endl;


        //Задача 6
        const int HOURS_IN_DAY = 24;
        const int MINUTES_IN_HOUR = 60;

        int days;
        cout << "Введіть кількість днів: ";
        cin >> days;

        long long totalMinutes = (long long)days * HOURS_IN_DAY * MINUTES_IN_HOUR;

        cout << days << " днів це " << totalMinutes << " хвилин." << endl;

 
}