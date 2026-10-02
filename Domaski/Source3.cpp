#include <iostream>
using namespace std;

int main()
{
	//Zadaca1
	//int choice;
	//cout << "Vyber krayinu: 1-Ukraina, 2-Polshcha, 3-Kanada, 4-Velyka Brytaniia, 5-Uhorshchyna: ";
	//cin >> choice;

	//switch (choice)
	//{
	//case 1: cout << "Kyiv"; break;
	//case 2: cout << "Varshava"; break;
	//case 3: cout << "Ottava"; break;
	//case 4: cout << "London"; break;
	//case 5: cout << "Budapesht"; break;
	//default: cout << "Nekorektnyi vybir";
	//}


	//Zadacha 2
	//int day;
	//cout << "Vvedit nomer dnia (1-ponedilok, 7-nedilia): ";
	//cin >> day;

	//if (day == 6 || day == 7)
	//	cout << "Vykhidnyi";
	//else if (day >= 1 && day <= 5)
	//	cout << "Robochyi den";
	//else
	//	cout << "Nekorektnyi nomer dnia";


	//Zadacha 3
	//int direction;
	//cout << "Vvedit kurs (1-pivnich, 2-pivden, 3-zakhid, 4-skhid): ";
	//cin >> direction;

	//switch (direction)
	//{
	//case 1: cout << "Pivden"; break;
	//case 2: cout << "Pivnich"; break;
	//case 3: cout << "Skhid"; break;
	//case 4: cout << "Zakhid"; break;
	//default: cout << "Nekorektnyi kurs";
	//}


	//Zadacha 4
	int animal;
	cout << "Vyberit tvarynu: 1-zhyraf, 2-orol, 3-lev, 4-korova, 5-vovk, 6-kin, 7-lysytsia: ";
	cin >> animal;

	switch (animal)
	{
	case 1:
	case 4:
	case 6: cout << "Travoyidna"; break;
	case 2:
	case 3:
	case 5:
	case 7: cout << "Khyzhak"; break;
	default: cout << "Nekorektnyi nomer tvaryny";
	}

	return 0;
}
