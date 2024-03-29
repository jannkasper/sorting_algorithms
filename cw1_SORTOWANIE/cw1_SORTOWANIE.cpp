// cw1_SORTOWANIE.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;

//-----------------------------------------------RANDOM ARRAY------------------------------------------
void randomRange(int arr[], int n)
{

	int range = n + 1;
	for (int i = 0; i < n; ++i)
	{
		arr[i] = rand() % range;
		//cout << "Random number is: " << arr[i] << endl;
	}
}


//-----------------------------------------------ZAPIS DO PLIKU------------------------------------------
int saveArray(int points2, int arg[], double funcB[], double funcH[], double funcC[], double funcSh[])
{
	fstream plik("plik.txt", ios::out);
	if (plik.good())
	{
		plik << "ARG \t BUBBLE \t HEAP \t COUNTING \t SHELL" << endl;
		for (int i = 0; i < points2; i++)
		{
			plik << arg[i] << "\t " << funcB[i] << "\t " << funcH[i] << "\t " << funcC[i] << "\t " << funcSh[i] << endl;
			plik.flush();
		}
		plik.close();
	}
	return(0);
}
//-----------------------------------------------BUBBLE SORT------------------------------------------
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	bool swapped;
	for (i = 0; i < n - 1; i++)  // N RAZY ROZPOCZÊCIE OD NOWA SPRAWDZENIA
	{
		swapped = false;
		for (j = 0; j < n - i - 1; j++) //SPRAWDZENIE RAZ OD POCZ¥TKU, KAZDEJ PARY WYRAZÓW (BEZ USTAWIONEGO KOÑCA)
		{
			if (arr[j] > arr[j + 1]) // SPRAWDZENIE PARY WYRAZÓW
			{
				swap(&arr[j], &arr[j + 1]); //FUNKCJA ZAMIANY
				swapped = true;
			}
		}

		if (swapped == false) //JE¯ELI PRZEZ JEDEN CYKL NIE BY£O ZAMIANY ZAKOÑCZ FUNKCJE
			break;
	}
}
//-----------------------------------------------HEAP SORT------------------------------------------

void heapify(int arr[], int n, int i)
{
	int largest = i;  //PRZYPISANIE NUMERU KORZENIA DO TYMCZASOWEJ ZMIENNEJ
	int l = 2 * i + 1;  // NUMER LEWEJ GALEZI
	int r = 2 * i + 2;  // NUMER PRAWEJ GALEZI

	if (l < n && arr[l] > arr[largest]) // JEZELI LEWA GALAZ WIEKSZA USTAW NA TYMCZASOWEJ ZMIENNEJ
		largest = l;

	if (r < n && arr[r] > arr[largest]) // JEZELI PRAWA GALAZ WIEKSZA USTAW NA TYMCZASOWEJ ZMIENNEJ
		largest = r;

	if (largest != i) // JEZELI NUMER KORZENIA INNY OD RODZICA
	{
		swap(arr[i], arr[largest]); // ZAMIANA

									// REKURENCYJNE SPRAWDZA GALAZ NIZEJ
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	//ZACZYNA SPRAWDZANIE OD OSTATNIEGO RODZICA I IDZIE DO GORY, NAJWIEKSZA WARTOSC TRAFIA NA SZCZYT
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// ZACZYNA OD OSTATNIEGO WYRAZU I Z KAZDA PETLA ODCINA OSTATNI
	for (int i = n - 1; i >= 0; i--)
	{
		// SZCZYT ZAMIENIA Z OSTATNIM WYRAZEM
		swap(arr[0], arr[i]);

		// WYRAZ NA SZCZYCIE SPRAWDZA
		heapify(arr, i, 0);
	}
}
//-----------------------------------------------COUNTING SORT------------------------------------------
void countingSort(int arr[], int n) {
	const int range = n + 1;
	int* arrSort = new int[n]; // TABLICA Z WYRAZAMI POSTORTOWANYMI
	int* arrCount = new int[range]; // LICZEBNOSC KAZDEGO Z WYRAZOW

	int i;

	for (i = 0; i < range; ++i)
		arrCount[i] = 0;                // PRZYPISANIE 0 TABLICY ZLICZAJACEJ

	for (i = 0; i < n; ++i)
		++arrCount[arr[i]];               // ZLICZENIE WYSTAPIENIA KAZDEGO WYRAZU

	for (i = 1; i < range; ++i)
		arrCount[i] += arrCount[i - 1];       // DODANIE DO LICZBY WYSTAPIEN POPRZEDNIEJ LICZBY

	for (i = n - 1; i >= 0; --i)
		arrSort[--arrCount[arr[i]]] = arr[i];   // WSTAWIENIE LICZBY NA ODPOWIEDNIA POZYCJE

	for (i = 0; i < n; i++)
		arr[i] = arrSort[i];
}

//-----------------------------------------------SHELL SORT------------------------------------------

int shellSort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) // WYKONANIE WSZYSTKICH DYSTANSOW ZACZYNAJAC OD NAJWIEKSZEGO
	{

		for (int i = gap; i < n; i += 1) // W DANYM DYSTANSIE  ZACZYNAMY OD ELEMENTU O POZYCJI = AKTUALNY DYSTANS I PRZESUWAMY POZYCJE WYZEJ
		{

			int temp = arr[i]; //ZAPISUJEMY ELEMENT JAKO TYMCZASOWY

			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) //POROWNUJEMY Z ELEMENTAMI ODLEGLYCH O DYSTANS W DOL
				arr[j] = arr[j - gap];  // ZAMIANA JEZELI SPELNIA WARUNKI

			arr[j] = temp; //TYMCZASOWA WARTOSC PRZYPISANA NA ODPOWIEDNIE MIEJSCE
		}
	}
	return 0;
}
int main()
{
	int averageRepeat = 10;
	double averageSum = 0;
	const int points = 15;
	int startNumArg = 500;
	int arg[points];
	double funcB[points], funcH[points], funcC[points], funcSh[points];
	for (int i = 0; i < points; i++)
	{
		arg[i] = startNumArg;
		startNumArg += 500;
	}

	//-----------------------------------------------BUBBLE SORT------------------------------------------
	for (int i = 0; i < points; i++)
	{
		int* array = new int[arg[i]];
		for (int j = 0; j < averageRepeat; j++)
		{
			srand(time(NULL));
			randomRange(array, arg[i]);
			auto start = std::chrono::high_resolution_clock::now();
			bubbleSort(array, arg[i]); //<----------------------------------------------------- BUBBLE SORT
			auto finish = std::chrono::high_resolution_clock::now();
			double elapsed_secs = ((finish - start).count());
			//elapsed_secs /= 1000000;
			averageSum += elapsed_secs;
		}
		averageSum = averageSum / averageRepeat;
		cout << "Time for BUBBLE " << arg[i] << " arguments is: " << averageSum << "ms\n";
		funcB[i] = averageSum;
		averageSum = 0;
	}
	//-----------------------------------------------HEAP SORT------------------------------------------
	for (int i = 0; i < points; i++)
	{
		int* array = new int[arg[i]];
		for (int j = 0; j < averageRepeat; j++)
		{
			srand(time(NULL));
			randomRange(array, arg[i]);
			auto start = std::chrono::high_resolution_clock::now();
			heapSort(array, arg[i]); //<----------------------------------------------------- HEAP SORT
			auto finish = std::chrono::high_resolution_clock::now();
			double elapsed_secs = ((finish - start).count());
			//elapsed_secs /= 1000000;
			averageSum += elapsed_secs;
		}
		averageSum = averageSum / averageRepeat;
		cout << "Time for HEAP " << arg[i] << " arguments is: " << averageSum << "ms\n";
		funcH[i] = averageSum;
		averageSum = 0;
	}
	//-----------------------------------------------COUNTING SORT------------------------------------------
	for (int i = 0; i < points; i++)
	{
		int* array = new int[arg[i]];
		for (int j = 0; j < averageRepeat; j++)
		{
			srand(time(NULL));
			randomRange(array, arg[i]);
			auto start = std::chrono::high_resolution_clock::now();
			countingSort(array, arg[i]); //<----------------------------------------------------- COUNTING SORT
			auto finish = std::chrono::high_resolution_clock::now();
			double elapsed_secs = ((finish - start).count());
			//elapsed_secs /= 1000000;
			averageSum += elapsed_secs;
		}
		averageSum = averageSum / averageRepeat;
		cout << "Time for COUNTING " << arg[i] << " arguments is: " << averageSum << "ms\n";
		funcC[i] = averageSum;
		averageSum = 0;
	}
	//-----------------------------------------------SHELL SORT------------------------------------------
	for (int i = 0; i < points; i++)
	{
		int* array = new int[arg[i]];
		for (int j = 0; j < averageRepeat; j++)
		{
			srand(time(NULL));
			randomRange(array, arg[i]);
			auto start = std::chrono::high_resolution_clock::now();
			shellSort(array, arg[i]); //<----------------------------------------------------- SHELL SORT
			auto finish = std::chrono::high_resolution_clock::now();
			double elapsed_secs = ((finish - start).count());
			//elapsed_secs /= 1000000;
			averageSum += elapsed_secs;
		}
		averageSum = averageSum / averageRepeat;
		cout << "Time for SHELL " << arg[i] << " arguments is: " << averageSum << "ms\n";
		funcSh[i] = averageSum;
		averageSum = 0;
	}



	saveArray(points, arg, funcB, funcH, funcC, funcSh);
}



