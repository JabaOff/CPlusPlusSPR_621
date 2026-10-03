#include <iostream>
using namespace std;

int main()
{
	const int size = 11;
	const int middle = size / 2;

	for (int choice = 1; choice <= 10; choice++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				bool star = false;
				if (choice == 1)
					star = j >= i;
				else if (choice == 2)
					star = j <= i;
				else if (choice == 3)
					star = i <= middle and j >= i and j <= size - 1 - i;
				else if (choice == 4)
					star = i >= j and i + j >= size - 1;
				else if (choice == 5)
					star = (i <= middle and j >= i and j <= size - 1 - i) or
						(i >= middle and j >= size - 1 - i and j <= i);
				else if (choice == 6)
					star = (j <= i and j <= size - 1 - i) or
						(j >= i and j >= size - 1 - i);
				else if (choice == 7)
					star = j <= i and j <= size - 1 - i;
				else if (choice == 8)
					star = j >= i and j >= size - 1 - i;
				else if (choice == 9)
					star = i + j <= size - 1;
				else if (choice == 10)
					star = i + j >= size - 1;

				if (star)
					cout << "* ";
				else
					cout << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
