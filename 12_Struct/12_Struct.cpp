#include <iostream>
#include <string>
using namespace std;

// Завдання 1
// struct WashingMachine {
//     string firm;
//     string color;
//     float width;
//     float length;
//     float height;
//     int power;
//     int spinSpeed;
//     float temp;
// };
//
// void printWM(WashingMachine& m) {
//     cout << "Фірма:        " << m.firm << endl;
//     cout << "Колір:        " << m.color << endl;
//     cout << "Ширина:       " << m.width << " см" << endl;
//     cout << "Довжина:      " << m.length << " см" << endl;
//     cout << "Висота:       " << m.height << " см" << endl;
//     cout << "Потужність:   " << m.power << " Вт" << endl;
//     cout << "Швидкість:    " << m.spinSpeed << " об/хв" << endl;
//     cout << "Температура:  " << m.temp << " °C" << endl;
// }
//
// void task1() {
//     WashingMachine m;
//     m.firm      = "Samsung";
//     m.color     = "Білий";
//     m.width     = 60.0;
//     m.length    = 60.0;
//     m.height    = 85.0;
//     m.power     = 2000;
//     m.spinSpeed = 1400;
//     m.temp      = 60.0;
//
//     cout << "=== Пральна машинка ===" << endl;
//     printWM(m);
// }


// Завдання 2
// 
// 
//
// struct Iron {
//     string firm;
//     string model;
//     string color;
//     int minTemp;
//     int maxTemp;
//     bool steam;
//     int power;
// };
//
// void printIron(Iron& i) {
//     cout << "Фірма:          " << i.firm << endl;
//     cout << "Модель:         " << i.model << endl;
//     cout << "Колір:          " << i.color << endl;
//     cout << "Мін. темп:      " << i.minTemp << " °C" << endl;
//     cout << "Макс. темп:     " << i.maxTemp << " °C" << endl;
//     cout << "Подача пари:    " << (i.steam ? "Так" : "Ні") << endl;
//     cout << "Потужність:     " << i.power << " Вт" << endl;
// }
//
// void task2() {
//     Iron i;
//     i.firm    = "Philips";
//     i.model   = "GC3650";
//     i.color   = "Синій";
//     i.minTemp = 80;
//     i.maxTemp = 220;
//     i.steam   = true;
//     i.power   = 2400;
//
//     cout << "=== Праска ===" << endl;
//     printIron(i);
// }

// Завдання 3
struct Boiler {
    string firm;
    string color;
    int power;
    int volume;
    int temp;
};

void printBoiler(Boiler& b) {
    cout << "Фірма:      " << b.firm << endl;
    cout << "Колір:      " << b.color << endl;
    cout << "Потужність: " << b.power << " Вт" << endl;
    cout << "Обсяг:      " << b.volume << " л" << endl;
    cout << "Температура:" << b.temp << " °C" << endl;
}

void task3() {
    Boiler b;
    b.firm = "Dantec";
    b.color = "Білий";
    b.power = 2000;
    b.volume = 50;
    b.temp = 75;

    cout << "=== Бойлер ===" << endl;
    printBoiler(b);
}

int main() {
    task3();
    return 0;
}
