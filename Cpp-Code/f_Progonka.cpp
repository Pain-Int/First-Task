#include<iostream>
#include<fstream>
using namespace std;

void PrintMatrix(float ** const AB, const int I, const int J);
void PrintMatrix(float * const AB, const int N);
void PrintMatrix(float * const A, float * const B, float * const C, float * const F, const int N);

void f_Progonka(float ** const AB, const int N)
{
	cout << "Вызов успешен" << endl;

	//Копирование массива

		float * A = new float[N];
		float * B = new float[N];
		float * C = new float[N];
		float * F = new float[N];

		for (int i = 0; i < N; i++)
		{
			A[i] = AB[i][i-1];
			B[i] = AB[i][i];
			C[i] = AB[i][i+1];
			F[i] = AB[i][N];
		}
		A[0] = 0;
		C[N - 1] = 0;

		PrintMatrix(A, B, C, F, N);
	//Прямой ход
		float * Alpha = new float[N];
		float * Beta = new float[N];
		Alpha[0] = 0;
		Beta[0] = 0;

		for (int i = 0; i < N-1; i++)
		{
			Alpha[i + 1] = -C[i] / (A[i]*Alpha[i] + B[i]);
			Beta[i + 1] = (F[i] - A[i]*Beta[i]) / (A[i]*Alpha[i] + B[i]);
		}

	//Обратный ход
		float * X = new float[N];

		X[N-1] = (F[N-1] - A[N-1] * Beta[N-1]) / (A[N-1] * Alpha[N-1] + B[N-1]);

		for (int i = N-2; i >= 0; i=i-1)
		{
			X[i] = Alpha[i+1] * X[i+1] + Beta[i+1];
		}
		
	//Вывод
		cout << "X =";
		PrintMatrix(X, N);

		cout << "\nОтвет ждет вас в файле Otvet.txt" << endl;
		ofstream fout;
		fout.open("Otvet.txt");

		for (int i = 0; i >= N; i++)
		{
			fout << X[i] << " ";
		}

		fout.close();

	//Очищаем память
		delete[] X;
		delete[] A;
		delete[] B;
		delete[] C;
		delete[] F;
		delete[] Alpha;
		delete[] Beta;
}