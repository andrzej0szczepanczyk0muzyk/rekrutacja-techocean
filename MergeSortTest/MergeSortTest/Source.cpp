#define RAPORT "raport.txt"

#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;

typedef vector<int> V;

//sortuje rosn¹co tablicê pod referencj¹ &K u¿ywaj¹c podzia³u tablicy na P czêœci przy jednej iteracji
void mergesort(vector<int> &K, int P)
{
	if (K.size() <= 1) return;
	vector<int>::iterator k = K.begin();
	int s = K.size();

	vector<vector<int>> slice(P);

	for (int i = 0; i < P; i++)
	{
		slice[i] = vector<int>(k + s*i / P, k + s*(i + 1) / P);
		mergesort(slice[i], P);
	}

	{

		vector<int> it(slice.size(), 0);
		int mval = 0;
		int ik = 0;
		int i;
		int mi;
		bool end = false;
		while (end == false)
		{
			end = true;
			mval = 0x7FFFFFFF;
			for (i = 0; i < slice.size(); i++)
			{
				if (it[i] < slice[i].size())
				{

					if (mval > slice[i][it[i]]) { mval = slice[i][it[i]]; mi = i; }
					end = false;
				}
			}
			if (end == false)
			{
				K[ik++] = mval;  it[mi]++;
			}
		}
	}
}

void wyswietl(V k)
{
	for (int u = 0; u < k.size(); u++) cout << k[u] << "  "; cout << endl;
}

V wygenerujTablice(int k, int size)
{

	int c = 31;
	V tab(size);
	for (int u = 0; u < tab.size(); u++)
	{
		//ustawienie 1 -> generuje tablicê malej¹c¹
		//ustawienie 0 -> generuje tablicê wed³ug problemu Collatza
		if (1)
		{
			c = tab.size() - u;
		}
		else
		{
			//Problem Collatza
			if (c % 2 == 0) c = c / 2;
			else c = 3 * c + 1;
		}

		tab[u] = c;
	}
	return tab;
}

int main()
{
	clock_t start;
	clock_t stop;
	fstream f;
	f.open(RAPORT, ios::out);
	
	//wspó³czynnik > 1 -> maksymalna liczba podzia³ów w jednej iteracji w danym teœcie wiêksza, ni¿ rozmiar tablicy
	//wspó³czynnik < 1 -> w przeciwnym przypadku 
	const float wspolczynnik = 1.2;
	const int ROZMIAR_T=100;

	for (int u = 2; u < ROZMIAR_T*wspolczynnik; u++)
	{
		
		V A = wygenerujTablice(1,ROZMIAR_T);
		start = clock();
		mergesort(A, u);
		stop = clock();
		wyswietl(A);
		cout << "czas wykonania siê programu dla "<<u<<" podzialow: " << stop-start  << endl;
		f << u << "\t" << stop - start << "\n";
	}
	f.close();
}