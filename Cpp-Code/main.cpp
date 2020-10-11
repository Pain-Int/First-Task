#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Прототипы
void f_Gauss(float ** const AB, const int N);
void f_Progonka(float ** const AB, const int N);
void f_Seidel(float ** const AB, const int N, const float MinPogr);

float COND(float ** const A, const int N);

void PrintMatrix(float ** const AB, const int I, const int J);

//Главная программа
int main()
{
	setlocale(LC_ALL, "ru");

	cout << "Вы открыли программу для решения Систем Линейных Алгебраических Уравнений(СЛАУ)\n" << endl;
	cout << "Пожалуйста, создайте .txt-файл, в который внесите коэфициенты вашей системы\nВведите имя файла: ";

	string FileIn;		//Имя файла
	ifstream fin;		//Файл ввода
	int N;				//Размер матрицы

	//Открытие файла
		cin >> FileIn;

		FileIn = FileIn + ".txt";
		fin.open(FileIn);

		//Удалось ли открыть файл?
			if (!fin.is_open())
			{
				cout << "Ошибка открытия файла!" << endl;
				cout << "Вы точно создали файл?" << endl;
				return 0;
			}

	//Считывание данных
		cout << "Введите размер вашей матрицы: ";
		cin >> N;

		//Объявление массива
			float ** AB = new float*[N];
			for (int i = 0; i < N; i++)
			{
				AB[i] = new float[N+1];
			}

		//считывание массива
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N+1; j++)
				{
					fin >> AB[i][j];
				}
			}

		fin.close();
	//Рассчет обусловленности
		float C = COND(AB, N);
		cout << "\nCOND(A) = " << C << endl;

		if (C < 10) cout << "Матрица хорошо обсуловлена\n" << endl;
		if (C < 100) cout << "Матрица плохо обусловлена \n(Решение следует проверить на корректность)\n" << endl;
		if (C >= 100) cout << "Решение заведомо неверно\n" << endl;

	//Выбор метода

		int Met;
		float Pogr = 0;

		cout << "Выберете метод:" << endl;
		cout << "1. Метод Гаусса" << endl;
		cout << "2. Метод Прогонки \n\t(Только для трехдиагональных матриц)" << endl;
		cout << "3. Метод Зейделя" << endl;
		cout << "666. Выход" << endl;
		cin >> Met;
		
		switch (Met)
		{
			case 1:
			//Метод Гаусса
				f_Gauss(AB, N);
				break;
			case 2:
			//Метод Прогонки
				f_Progonka(AB, N);
				break;
			case 3:
			//Метод Зейделя
				//Ввод допустимой погрешности
					cout << "Введите допустимую погрешность: ";
					cin >> Pogr;

				f_Seidel(AB, N, Pogr);
				break;
			case 666:
			//Выход
				return 0;

			default:
				cout << "Таких методов я не знаю(((" << endl;
				break;
		}

	//Подсчет времени

	//Очищаем память
		for (int i = 0; i < N; i++)
		{
			delete[] AB[i];
		}
		delete [] AB;
	return 0;
}

//Габариты гитары:
	//дека 33
	//длина 97
	//хедсток 18