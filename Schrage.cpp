// Schrage.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#pragma comment(linker, "/STACK:512000000")
#pragma comment(linker, "/HEAP:128000000")
#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <string>
#include <list>
#include <queue> 
#include "heap_sort.h"
#include "chrono"
#include <vector>
#include "Carlier.h"
//#include "result_shrage.h"

using namespace std;



void wypisz_kolejnosc(int n, zadanie tab[])
{
	for (int i = 0; i < n; i++)
	{
		cout << tab[i].id << " ";
	}
	cout << endl;
}


int main()
{
	int n;
	int temp;
	zadanie tab[50];
	list<zadanie> lista_zadan;
	int res1;
	

	int total = 0;
	int total_duration = 0;
	int temp_dur;
	
	cout << endl << endl << "*****************Carlier ***********************" << endl;
	for (int g = 0; g < 9; g++)
	{
		Carlier obiekt;
		ifstream data("carl.data.txt");
		string s = "";
		string nazwa = "data." + to_string(g) + ":";
		while (s != nazwa)
		{
			data >> s;
		}
		data >> obiekt.n;
		for (int i = 0; i < obiekt.n; i++)
		{
			obiekt.schrage[i].id = i;
			data >> obiekt.schrage[i].R;
			data >> obiekt.schrage[i].P;
			data >> obiekt.schrage[i].Q;
		}
		cout << "Wczytano" << endl;
		auto t1 = std::chrono::high_resolution_clock::now();
		res1 = obiekt.do_carlier();
		auto t2 = std::chrono::high_resolution_clock::now();
		temp_dur = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		total_duration += temp_dur;
		std::cout << "Czas wykonywania algorytmu carliera: " << temp_dur << "ms\n";

		//cout << "schrpmtn: " << res2.dlugoscUsz << endl;
		cout << "Kolejnosc zestaw " << g << ": " << endl;
		wypisz_kolejnosc(obiekt.n, obiekt.best);
		cout << "czas zestaw " << g << ": ";
		cout << res1 << endl;
		total += res1;
	}

	cout << "Calkowity czas wykonywania testu to: " << total_duration <<"ms\n";
	total = 0;
	total_duration = 0;

	system("pause");
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
