#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Завдання 1
// void task1() {
//     string s;
//     cout << "Введіть рядок: ";
//     getline(cin, s);
//
//     int countA = 0, countO = 0;
//     for (char c : s) {
//         char lower = tolower(c);
//         if (lower == 'a') countA++;
//         if (lower == 'o') countO++;
//     }
//
//     if (countA > countO)
//         cout << "Букви 'a' більше (" << countA << ")";
//     else if (countO > countA)
//         cout << "Букви 'o' більше (" << countO << ")";
//     else
//         cout << "Однакова кількість (" << countA << ")";
// }

// Завдання 2
// void task2() {
//     string s;
//     cout << "Введіть рядок: ";
//     getline(cin, s);
//
//     int latin = 0, digits = 0, spaces = 0;
//     for (char c : s) {
//         if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
//             latin++;
//         else if (c >= '0' && c <= '9')
//             digits++;
//         else if (c == ' ')
//             spaces++;
//     }
//
//     cout << "Латинських букв: " << latin << endl;
//     cout << "Цифр: " << digits << endl;
//     cout << "Пробілів: " << spaces << endl;
// }

// Завдання 3
// void task3() {
//     string s;
//     cout << "Введіть рядок: ";
//     getline(cin, s);
//
//     for (char& c : s) {
//         if (isupper(c))
//             c = tolower(c);
//         else if (islower(c))
//             c = toupper(c);
//     }
//
//     cout << "Результат: " << s << endl;
// }

// Завдання 4
// int myLength(string s) {
//     int len = 0;
//     for (int i = 0; s[i] != '\0'; i++)
//         len++;
//     return len;
// }
//
// void task4() {
//     string s;
//     cout << "Введіть рядок: ";
//     getline(cin, s);
//     cout << "Довжина: " << myLength(s) << endl;
// }

// Завдання 5
void task5() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);

    int whitespaces = 0, vowels = 0, consonants = 0, punctuation = 0;

    for (char c : s) {
        if (isspace(c)) {
            whitespaces++;
        }
        else if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') {
            char lower = tolower(c);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
                vowels++;
            else
                consonants++;
        }
        else {
            punctuation++;
        }
    }

    cout << "Whitespaces:  " << whitespaces << endl;
    cout << "Vowels:       " << vowels << endl;
    cout << "Consonants:   " << consonants << endl;
    cout << "Punctuation:  " << punctuation << endl;
}

int main() {
    task5();
    return 0;
}
