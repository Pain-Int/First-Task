#include<iostream>
#include<fstream>
using namespace std;

void PrintMatrix(float ** const AB, const int I, const int J);
void PrintMatrix(float * const AB, const int N);

void f_Gauss(float ** const AB, const int N)
{
	cout << "Вызов успешен" << endl;

	//Копирование массива и объявление
		float ** Matrix = new float *[N];
		for (int i = 0; i < N; i++)
		{
			Matrix[i] = new float[N + 1];
			for (int j = 0; j < N+1; j++)
			{
				Matrix[i][j] = AB[i][j];
			}
		}

	//Приведение к треугольному виду
		for (int i = 1; i < N; i++)
		{
			//Если главный элемент равен 0
				if (Matrix[i][i] == 0)
				{
					float A;
					for (int k = 0; k < N+1; k++)
					{
						A = Matrix[i][k];
						Matrix[i][k] = Matrix[i+1][k];
						Matrix[i+1][k] = A;
					}
				}
			for (int j = i; j < N; j++)
			{
				float m = Matrix[j][i-1] / Matrix[i-1][i-1];
				for (int k = 0; k < N+1; k++)
				{
					Matrix[j][k] = Matrix[j][k] -  m * Matrix[i-1][k];
				}
			}
		}

	//Обратный ход
		float * X = new float[N];

		for (int i = N-1; i >= 0; i=i-1)
		{
			X[i] = Matrix[i][N]/Matrix[i][i];

			for (int j = N-1; j > i; j=j-1)
			{
				X[i] = X[i] - X[j]*Matrix[i][j]/Matrix[i][i];
			}
		}

	//Вывод
		cout << "X =";
		PrintMatrix(X, N);

		cout << "\nОтвет ждет вас в файле Otvet.txt"<<endl;

		ofstream fout;
		fout.open("Otvet.txt");

		for (int i = 0; i >= N; i++)
		{
			fout << X[i] <<" ";
		}

		fout.close();

	//Очищаем память
		for (int i = 0; i < N; i++)
		{
			delete[] Matrix[i];
		}
		delete[] Matrix;
		delete[] X;
}