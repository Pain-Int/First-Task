#include<iostream>
using namespace std;

void PrintMatrix(float ** const AB, const int I, const int J);

float Det(float ** const A, const int N)
{
	//Копирование массива
	float ** Matrix = new float *[N];
	for (int i = 0; i < N; i++)
	{
		Matrix[i] = new float[N];
		for (int j = 0; j < N; j++)
		{
			Matrix[i][j] = A[i][j];
		}
	}

	//Приведение к треугольному виду
	for (int k = 1; k < N; k++)
	{
		//Если главный элемент равен 0
		if (Matrix[k-1][k-1] == 0)
		{
			float A;
			for (int j = 0; j < N + 1; j++)
			{
				A = Matrix[k-1][j];
				Matrix[k-1][j] = Matrix[k][j];
				Matrix[k][j] = A;
			}
		}
		for (int i = k; i < N; i++)
		{
			float m = Matrix[i][k - 1] / Matrix[k - 1][k - 1];
			for (int j = 0; j < N; j++)
			{
				Matrix[i][j] = Matrix[i][j] - m * Matrix[k - 1][j];
			}
		}
	}

	float D = Matrix[0][0];

	for (int i = 1; i < N; i++)
	{
		D = D*Matrix[i][i];
	}
	return D;
}

float Norma(float ** const A, const int N)
{
	float Norm = 0;

	if (Det(A,N) == 0)
	{
		Norm = 0;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Norm += pow(A[i][j], 2);
			}
		}
	}

	Norm = sqrt(Norm);
	return Norm;
}

float ADop(float ** const A, const int N, const int I, const int J)
{
	float Dop=0;

	//Объявление массива
		float ** Minor = new float *[N - 1];
		for (int i = 0; i < N-1; i++)
		{
			Minor[i] = new float[N - 1];
		}

	//Заполнение массива
		for (int i = 0; i < N-1; i++)
		{
			for (int j = 0; j < N-1; j++)
			{
				if (i < I and j < J) Minor[i][j] = A[i][j];
				if (i >= I and j < J) Minor[i][j] = A[i + 1][j];
				if (i < I and j >= J) Minor[i][j] = A[i][j + 1];
				if (i >= I and j >= J) Minor[i][j] = A[i + 1][j + 1];
			}
		}

		Dop = pow(-1, I + J)*Det(Minor, N-1);

	return Dop;
}

void Invert(float ** A, const int N)
{
	//Копирование массива
	float ** Matrix = new float *[N];
	for (int i = 0; i < N; i++)
	{
		Matrix[i] = new float[N];
		for (int j = 0; j < N; j++)
		{
			Matrix[i][j] = A[i][j];
		}
	}

	float D = Det(A, N);

	if (D==0)
	{
		cout << "Обратной матрицы не существует" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Matrix[j][i] = ADop(A,N,i,j);
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				A[i][j] = 1 / D * Matrix[i][j];
			}
		}
	}
}

float COND(float ** const A, const int N)
{
	float ** InvA = new float *[N];
	for (int i = 0; i < N; i++)
	{
		InvA[i] = new float[N];
		for (int j = 0; j < N; j++)
		{
			InvA[i][j] = A[i][j];
		}
	}

	Invert(InvA, N);

	float COND = Norma(A, N)*Norma(InvA,N);

	return COND;
}

//копирование массива