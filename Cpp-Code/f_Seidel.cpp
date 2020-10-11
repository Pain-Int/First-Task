#include<iostream>
#include<fstream>
using namespace std;

void PrintMatrix(float ** const AB, const int I, const int J);
void PrintMatrix(float * const AB, const int N);

void f_Seidel(float ** const AB, const int N, const float MinPogr)
{
	cout << "Вызов успешен" << endl;

	//Копирование массива
		float ** Matrix = new float *[N];
		for (int i = 0; i < N; i++)
		{
			Matrix[i] = new float[N + 1];
			Matrix[i][N] = AB[i][N] / AB[i][i];

			for (int j = 0; j < N; j++)
			{
				if (i == j)
				{
					Matrix[i][j] = 0;
				}
				else
				{
					Matrix[i][j] = -AB[i][j] / AB[i][i];
				}
			}
		}

		PrintMatrix(Matrix, N, N+1);

	//Считаем
		float * X = new float[N];
		float * Xprov = new float[N];

		for (int i = 0; i < N; i++)
		{
			X[i] = Matrix[i][N];
			Xprov[i] = X[i];
		}

		int Ticker = 0;

		for (;;)
		{
			Ticker = Ticker + 1;
			int NeShodit = 0;

			for (int i = 0; i < N; i++)
			{
				float Summ = 0;

				for (int j = 0; j < N; j++)
				{
					Summ =  Summ + (Matrix[i][j] * X[j]);
				}

				Xprov[i] = Summ + Matrix[i][N];

				//Подсчет погрешности
					float Pogr = 0;
					Pogr = abs((Xprov[i] - X[i]) / X[i]);

					if (Pogr >= MinPogr)
					{
						NeShodit = NeShodit + 1;
					}

				X[i] = Xprov[i];
			}

			//Условие выхода
				if (NeShodit == 0)
				{
					break;
				}
		}
	//Вывод
		cout << "Итераций = " << Ticker << endl;
		cout << "X =";
		PrintMatrix(X, N);

		cout << "\nОтвет ждет вас в файле Otvet.txt"<<endl;

		ofstream fout;
		fout.open("Otvet.txt");

		for (int i = 0; i >= N; i++)
		{
			fout << X[i] << " ";
		}

		fout.close();

	//Очищаем память
		for (int i = 0; i < N; i++)
		{
			delete[] Matrix[i];
		}
		delete[] Matrix;
		delete[] X;
		delete[] Xprov;
}