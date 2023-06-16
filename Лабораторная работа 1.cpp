#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

bool inaccuracy(double a1, double b1, double c1, double a2, double c2);
string currect_number(string a, string eps);
string inaccuracy_correct_number(string a);

int main()
{
	setlocale(LC_ALL, "RUS");

	int menu;
	double a1, b1, c1, a2, c2;
	string a, eps;

	do {
		cout << "Выберите задание:\n"
			"1 - Определить, какое выражение точнее\n"
			"2 - Округлить сомнительные цифры числа\n"
			"3 - Найти предельные абсолютную и относительную погрешности приближенного числа\n"
			"0 - Выход" << endl;
		cin >> menu;

		switch (menu)
		{
			case 1://Определить, какое выражение точнее
			{
				cout << "Введите первое выражение (__/__=__)\n";
				cin >> a1;
				cin >> b1;
				cin >> c1;

				cout << "Введите второе выражение(sqrt(_)=__)\n";
				cin >> a2;
				cin >> c2;

				if(inaccuracy(a1, b1, c1, a2, c2)) cout << "Значит, более точное выражение: " << "sqrt(" << a2 << ") = " << c2 << endl << endl;
				else cout << "Значит, более точное выражение: " << a1 << "/" << b1 << " = " << c1 << endl << endl;
				break;
			}

			case 2://Округлить сомнительные цифры числа
			{
				cout << "Введите число" << endl;
				cin >> a;
				cout << "Введите погрешность числа" << endl;
				cin >> eps;

				for (int i = 0; i < a.length(); i++)
					if (a[i] == '.')a[i] = ',';

				cout << "\nЧисло только с верными знаками:" << currect_number(a, eps) << endl;
				cout << "Абсолютная погрешность результата: " << abs(stod(currect_number(a, eps)) - stod(a)) << endl << endl;
				break;
			}

			case 3://Найти предельные абсолютную и относительную погрешности приближенного числа
			{
				cout << "Введите число с верными знаками" << endl;
				cin >> a;

				for (int i = 0; i < a.length(); i++)
					if (a[i] == '.')a[i] = ',';

				cout << "Абсолютная погрешность числа: " << stod(inaccuracy_correct_number(a)) << endl;
				cout << "Относительная погрешность числа: " << stod(inaccuracy_correct_number(a)) / stod(a) * 100 << endl << endl;
				break;
			}
		}
	} while (menu != 0);
}

bool inaccuracy(double a1, double b1, double c1, double a2, double c2)
{
	double dop1, dop2;
	dop1 = a1 / b1;
	dop2 = sqrt(a2);

	cout << "Какое выражение точнее: 1) " << a1 << "/" << b1 << " = " << c1 << " или 2) sqrt(" << a2 << ") = " << c2 << endl << endl;

	cout << "Значения выражений с большим количеством десятичных знаков :" << endl;
	cout << "1) " << a1 << "/" << b1 << " = " << setprecision(9) << dop1 << "\n" << "2) sqrt(" << a2 << ") = " << dop2 << setprecision(5) << endl << endl;

	cout << "Предельные абсолютные погрешности, округляя их с избытком:" << endl;
	cout << setprecision(7) << "1) " << abs(dop1 - c1) << endl;
	cout << "2) " << abs(dop2 - c2) << setprecision(5) <<endl;

	cout << "Предельные абсолютные погрешности составляют в %:" << endl;
	cout << "1) " << abs(dop1 - c1) / dop1 * 100 << "\n" << "2) " << abs(dop2 - c2) / dop2 * 100 << endl;

	if (abs(dop1 - c1) / c1 * 100 < abs(dop2 - c2) / c2 * 100) return false;
	return true;
}

string currect_number(string a, string eps)
{
	string newA = a;
	for (int i = 0; i < a.length(); i++)
	{
		if (i >= eps.length() - 1 || (i < eps.length() - 1 && eps[i] != '0' && eps[i] != '.' && a[i] != '.' && eps[i] != ',')) newA[i] = 0;
		if (newA[i] == '.')newA[i] = ',';
	}
	return newA;
}

string inaccuracy_correct_number(string a)
{
	string newA = "0,";

	for (int i = 0; i < a.length() - 2; i++)
	{
		newA += "0";
	}
	newA += "1";

	return newA;
}
