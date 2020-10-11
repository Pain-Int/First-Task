#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//���������
void f_Gauss(float ** const AB, const int N);
void f_Progonka(float ** const AB, const int N);
void f_Seidel(float ** const AB, const int N, const float MinPogr);

float COND(float ** const A, const int N);

void PrintMatrix(float ** const AB, const int I, const int J);

//������� ���������
int main()
{
	setlocale(LC_ALL, "ru");

	cout << "�� ������� ��������� ��� ������� ������ �������� �������������� ���������(����)\n" << endl;
	cout << "����������, �������� .txt-����, � ������� ������� ����������� ����� �������\n������� ��� �����: ";

	string FileIn;		//��� �����
	ifstream fin;		//���� �����
	int N;				//������ �������

	//�������� �����
		cin >> FileIn;

		FileIn = FileIn + ".txt";
		fin.open(FileIn);

		//������� �� ������� ����?
			if (!fin.is_open())
			{
				cout << "������ �������� �����!" << endl;
				cout << "�� ����� ������� ����?" << endl;
				return 0;
			}

	//���������� ������
		cout << "������� ������ ����� �������: ";
		cin >> N;

		//���������� �������
			float ** AB = new float*[N];
			for (int i = 0; i < N; i++)
			{
				AB[i] = new float[N+1];
			}

		//���������� �������
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N+1; j++)
				{
					fin >> AB[i][j];
				}
			}

		fin.close();
	//������� ���������������
		float C = COND(AB, N);
		cout << "\nCOND(A) = " << C << endl;

		if (C < 10) cout << "������� ������ �����������\n" << endl;
		if (C < 100) cout << "������� ����� ����������� \n(������� ������� ��������� �� ������������)\n" << endl;
		if (C >= 100) cout << "������� �������� �������\n" << endl;

	//����� ������

		int Met;
		float Pogr = 0;

		cout << "�������� �����:" << endl;
		cout << "1. ����� ������" << endl;
		cout << "2. ����� �������� \n\t(������ ��� ���������������� ������)" << endl;
		cout << "3. ����� �������" << endl;
		cout << "666. �����" << endl;
		cin >> Met;
		
		switch (Met)
		{
			case 1:
			//����� ������
				f_Gauss(AB, N);
				break;
			case 2:
			//����� ��������
				f_Progonka(AB, N);
				break;
			case 3:
			//����� �������
				//���� ���������� �����������
					cout << "������� ���������� �����������: ";
					cin >> Pogr;

				f_Seidel(AB, N, Pogr);
				break;
			case 666:
			//�����
				return 0;

			default:
				cout << "����� ������� � �� ����(((" << endl;
				break;
		}

	//������� �������

	//������� ������
		for (int i = 0; i < N; i++)
		{
			delete[] AB[i];
		}
		delete [] AB;
	return 0;
}

//�������� ������:
	//���� 33
	//����� 97
	//������� 18