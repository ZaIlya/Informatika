#include <iostream>
using namespace std;

void show_system(float** A, float* Y, int n);
float* gauss(float** A, float* Y, int n);
float* matrix_method(float** A, float* Y, int n);
float determinant(float** A);
float* Jacobi_method(float** A, float* Y, float eps);
float* Seidel_method(float** A, float* Y, float eps);

int main()
{
	setlocale(LC_ALL, "RUS");

	float** A;
	float* Y, *x, eps;
    int n, v=1;

    while (v != 0)
    {
        cout << "Выберите действие:\n"
            "1-Решение СЛАУ матричным методом\n"
            "2-Решение СЛАУ методом Гаусса\n"
            "3-Решение СЛАУ методом Якоби\n"
            "4-Решение СЛАУ методом Зейделя\n"
            "0-Выход\n";
        cin >> v;
        if (v == 0) break;

        cout << "Введите размер n квадратной матрицы" << endl;
        cin >> n;

        A = new float* [n];
        Y = new float[n];

        for (int i = 0; i < n; i++) /*вывод примера заполнения матрицы*/
        {
            for (int j = 0; j < n; j++)
            {
                if (j == 0) cout << "A[" << i + 1 << "][" << j + 1 << "]*X" << j + 1;
                else cout << " + A[" << i + 1 << "][" << j + 1 << "]*X" << j + 1;
            }
            cout << " = " << "Y[" << i + 1 << "]" << endl;
        } cout << "\n";


        for (int i = 0; i < n; i++) /*создание и заполнение элементов матрицы*/
        {
            A[i] = new float[n];

            for (int j = 0; j < n; j++) 
            {
                cout << "A[" << i + 1 << "][" << j + 1 << "]= ";
                cin >> A[i][j];
            }
            cout << "Y[" << i + 1 << "]=";
            cin >> Y[i];
        } cout << "\n";

        switch (v)
        {
            case 1:
            {
                show_system(A, Y, n);
                x = matrix_method(A, Y, n);

                for (int i = 0; i < n; i++)
                    cout << "x" << i+1 << "=" << x[i] << endl;

                break;
            }
            case 2:
            {
               show_system(A, Y, n);
               x = gauss(A, Y, n);

               for (int i = 0; i < n; i++)
                   cout << "x" << i + 1 << "=" << x[i] << endl;

               break;
            }
            case 3:
            {
                show_system(A, Y, n);

                if (fabs(A[0][0]) <= fabs(A[0][1]) + fabs(A[0][2]) || fabs(A[1][1]) <= fabs(A[1][0]) + fabs(A[1][2]) || fabs(A[2][2]) <= fabs(A[2][1]) + fabs(A[2][0]))
                {
                    cout << "Невозможно применить метод Якоби. Должно выполняться условие:\n"
                        "|A[1][1]|>|A[1][2]|+|A[1][3]|\n"
                        "|A[2][1]|>|A[2][2]|+|A[2][3]|\n"
                        "|A[3][1]|>|A[3][2]|+|A[3][3]|" << endl;
                    continue;
                }

                cout << "Введите точность" << endl;
                cin >> eps;

                x = Jacobi_method(A, Y, eps);

                for (int i = 0; i < n; i++)
                    cout << "x" << i + 1 << "=" << x[i] << endl;

                break;
            }
            case 4:
            {
                show_system(A, Y, n);

                if (fabs(A[0][0]) <= fabs(A[0][1]) + fabs(A[0][2]) || fabs(A[1][1]) <= fabs(A[1][0]) + fabs(A[1][2]) || fabs(A[2][2]) <= fabs(A[2][1]) + fabs(A[2][0]))
                {
                    cout << "Невозможно применить метод Зейделя. Должно выполняться условие:\n"
                        "|A[1][1]|>|A[1][2]|+|A[1][3]|\n"
                        "|A[2][1]|>|A[2][2]|+|A[2][3]|\n"
                        "|A[3][1]|>|A[3][2]|+|A[3][3]|" << endl;
                    continue;
                }
              
                cout << "Введите точность" << endl;
                cin >> eps;

                x = Seidel_method(A, Y, eps);

                for (int i = 0; i < n; i++)
                    cout << "x" << i + 1 << "=" << x[i] << endl;

                break;
            }
        }
    }
}

void show_system(float** A, float* Y, int n)//Вывод системы уравнений с заполненными значениями
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0) 
			{
				cout << A[i][j] << "*X" << j + 1 << " ";
				continue;
			}

			if (A[i][j] < 0) cout << " - ";
				else cout << " + ";

			cout << fabs(A[i][j]) << "*X" << j + 1 << " ";
		}
		cout << " = " << Y[i] << endl;
	}
    cout << "\n";
}

float* gauss(float** A, float* Y, int n)//Метод Гаусса
{
    float* x, max;
    int k, index;
    x = new float[n];
    k = 0;

    while (k < n)
    {
        //поиск строки с максимальным элементом 
        max = abs(A[k][k]);
        index = k;

        for (int i = k + 1; i < n; i++)
        {
            if (abs(A[i][k]) > max)
            {
                max = abs(A[i][k]);
                index = i;
            }
        }
        if (max == 0)
        {
            // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно" << endl;
            return 0;
        }

        // перестановка строк
        for (int j = 0; j < n; j++)
        {
            float temp = A[k][j];
            A[k][j] = A[index][j];
            A[index][j] = temp;
        }
        float temp = Y[k];
        Y[k] = Y[index];
        Y[index] = temp;

        // вычисление
        for (int i = k; i < n; i++)
        {
            float temp = A[i][k];
            if (abs(temp) == 0) continue; // для нулевого коэффициента пропускаем

            for (int j = 0; j < n; j++) /*преобразуем элемент в единицу путём деления всех элементов строки на этот элемент*/
                A[i][j] = A[i][j] / temp;
            Y[i] = Y[i] / temp;

            if (i == k)  continue; // уравнение не вычитать само из себя
            
            for (int j = 0; j < n; j++) //вычитание строки из другой строки
                A[i][j] -= A[k][j];
            Y[i] = Y[i] - Y[k];
        }
        k++;
    }

    // нахождение всех корней по одному из найденных
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = Y[k];

        for (int i = 0; i < k; i++)
            Y[i] -= A[i][k] * x[k];
    }

    return x;
}

float* matrix_method(float** A, float* Y, int n)//Матричный метод
{
    float detA = determinant(A);

    float* Y_new, **A_new;
    Y_new = new float[n];
    A_new = new float* [n];

    for (int i = 0; i < n; i++)
        A_new[i] = new float[n];

    for (int o = 0; o < n; o++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A_new[i][j] = A[i][j];

        for (int j = 0; j < n; j++)
            A_new[j][o] = Y[j];

        Y_new[o] = determinant(A_new) / detA;
    }

    return Y_new;
}

float determinant(float** A)//Определитель матрицы третьего порядка
{
    return A[0][0] * A[1][1] * A[2][2] +
           A[0][1] * A[1][2] * A[2][0] +
           A[1][0] * A[2][1] * A[0][2] -
           A[2][0] * A[1][1] * A[0][2] -
           A[1][0] * A[0][1] * A[2][2] -
           A[2][1] * A[1][2] * A[0][0];
}

float* Jacobi_method(float** A, float* Y, float eps)
{
    float* X = new float[3];

    float X_old[3];
    int i = 1;

    X_old[0] = (Y[0] - A[0][1] *0 - A[0][2] * 0) / A[0][0];
    X_old[1] = (Y[1] - A[1][0] * 0 - A[1][2] * 0) / A[1][1];
    X_old[2] = (Y[2] - A[2][0] * 0 - A[2][1] *0) / A[2][2];

    printf("--------------------------------------------------------\n");
    printf("| Итерация |      х1      |     х2       |      х2      |\n");
    printf("--------------------------------------------------------\n");
    do {
        if (i != 1)
        {
            X_old[0] = X[0];
            X_old[1] = X[1];
            X_old[2] = X[2];
        }

        X[0] =  (Y[0] - A[0][1] * X_old[1] - A[0][2] * X_old[2]) / A[0][0];
        X[1] =  (Y[1] - A[1][0] * X_old[0] - A[1][2] * X_old[2]) / A[1][1];
        X[2] =  (Y[2] - A[2][0] * X_old[0] - A[2][1] * X_old[1]) / A[2][2];

        printf("|%10d|%14f|%14f|%14f|\n", i, X_old[0], X_old[1], X_old[2]);
        printf("--------------------------------------------------------\n");

        i++;
    } while (fabs(X[0]- X_old[0])>eps && fabs(X[1] - X_old[1]) > eps && fabs(X[2] - X_old[2]) > eps);

    return X;
}

float* Seidel_method(float** A, float* Y, float eps)
{
    float* X = new float[3];
    float x_old_prov[3];
    int i = 1;
    
    X[0] = (Y[0] - A[0][1] * 0 - A[0][2] * 0) / A[0][0];
    X[1] = (Y[1] - A[1][0] * 0 - A[1][2] * 0) / A[1][1];
    X[2] = (Y[2] - A[2][0] * 0 - A[2][1] * 0) / A[2][2];

    printf("--------------------------------------------------------\n");
    printf("| Итерация |      х1      |     х2       |      х2      |\n");
    printf("--------------------------------------------------------\n");
    do {
        x_old_prov[0] = X[0];
        x_old_prov[1] = X[1];
        x_old_prov[2] = X[2];
    
        X[0] = (Y[0] - A[0][1] * X[1] - A[0][2] * X[2]) / A[0][0];
        X[1] = (Y[1] - A[1][0] * X[0] - A[1][2] * X[2]) / A[1][1];
        X[2] = (Y[2] - A[2][0] * X[0] - A[2][1] * X[1]) / A[2][2];

        printf("|%10d|%14f|%14f|%14f|\n", i, X[0], X[1], X[2]);
        printf("--------------------------------------------------------\n");

        i++;
    } while (fabs(X[0] - x_old_prov[0]) > eps && fabs(X[1] - x_old_prov[1]) > eps && fabs(X[2] - x_old_prov[2]) > eps);

    return X;
}
