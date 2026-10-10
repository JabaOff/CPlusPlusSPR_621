#include <iostream>
using namespace std;

int main()
{


	//srand(time(0));
	//int a;
	//a = rand();
	//cout << "a = " << a << endl;
	//a = rand();
	//cout << "a = " << a << endl;
	//a = rand();
	//cout << "a = " << a << endl;



	//int array1[3][3] = { {1,2,3}, {4,5,6}, { 7,8,9 } };
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cout << array1[i][j] << " ";

	//	}
	//	cout << endl;


	//}

	//1


	//int arr[4][3] = {
	//	{0, 5, 0},
	//	{2, 0, 8},
	//	{0, 0, 0},
	//	{1, 4, 7}
	//};

	//int count = 0;

	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		if (arr[i][j] != 0) {
	//			count++;
	//		}
	//	}
	//}


	//
	//cout << "Count elements that not 0: "<< count << endl;

	srand(time(0));
	//int arr[4][3] = {};

	//int count = 0;

	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		arr[i][j] = rand() % 6;
	//		cout << arr[i][j] << " ";
	//		if (arr[i][j] != 0) {
	//			count++;
	//			
	//		}

	//	}
	//	cout << endl;
	//}


	//cout << "Count elements that not 0: " << count << endl;

	////2
	//const int row = 3;
	//	const int col = 3;
	//int arr2[row][col] = {};

	//int count2 = 0;

	//for (int i = 0; i < row; i++) {
	//	for (int j = 0; j < col; j++) {
	//		arr2[i][j] = rand() % 6;
	//		cout << arr2[i][j] << " ";
	//		if (arr2[i][j] == 0) {
	//			count2++;

	//		}

	//	}
	//	cout << endl;
	//}


	//cout << "Count elements that is 0: " << count2 << endl;


	////2
	//const int row = 3;
	//const int col = 3;
	//int arr2[row][col] = {};

	//int count2 = 0;

	//for (int i = 0; i < row; i++) {
	//	for (int j = 0; j < col; j++) {
	//		arr2[i][j] = rand() % 6;
	//		cout << arr2[i][j] << " ";
	//		if (arr2[i][j] == 0) {
	//			count2++;

	//		}

	//	}
	//	cout << endl;
	//}


	//cout << "Count elements that is 0: " << count2 << endl;


	//3
	const int row = 7;
	const int col = 3;
	int arr3[row][col] = {};

	int count3 = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			arr3[i][j] = rand() % 40 - 20;

			cout << arr3[i][j] << " ";
			if (arr3[i][j] <= 12 and arr3[i][j] >= -12) {
				count3++;

			}

		}
		cout << endl;
	}


	cout << "Count numbers between 12 and -12: " << count3 << endl;


}
