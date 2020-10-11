#include<iostream>
using namespace std;

void PrintMatrix(float ** const AB, const int I, const int J)
{
	cout << "\n";
	for (int i = 0; i < I; i++)
	{
		for (int j = 0; j < J; j++)
		{
			if (j == J-1)
			{
				cout << AB[i][j] << " " << endl;
			}
			else
			{
				cout << AB[i][j] << " ";
			}
		}
	}
	cout << "\n" << endl;
}

void PrintMatrix(float * const AB, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << AB[i]<<" "<< endl;
	}
}

void PrintMatrix(float * const A, float * const B, float * const C, float * const F, const int N)
{
	cout << "\n" << "Alpha" << "\t" << "Beta" << "\t" << "Gamma" << "\t" << "Delta" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << A[i]<<"\t"<<B[i]<<"\t"<<C[i]<<"\t"<<F[i]<<"\n"<< endl;
	}
}