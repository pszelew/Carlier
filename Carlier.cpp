#include "Carlier.h"

using namespace std;

Carlier::Carlier() : UB(INT_MAX), LB(0), U(0), r_k(INT_MAX), flag(0)
{

}


struct CompareR {
	bool operator()(zadanie const& p1, zadanie const& p2)
	{
		if (p1.R < p2.R) return false;
		if (p1.R == p2.R)
		{
			if (p1.id < p2.id) return false;
			else return true;
		}
		if (p1.R > p2.R) return true;
	}
};

struct CompareQ {
	bool operator()(zadanie const& p1, zadanie const& p2)
	{
		//return p1.Q < p2.Q;
		if (p1.Q < p2.Q) return true;
		if (p1.Q == p2.Q)
		{
			if (p1.id < p2.id) return false;
			else return true;
		}
		if (p1.Q > p2.Q) return false;
	}
};


int Carlier::check_time()
{
	int m = 0;
	int c = 0;
	int i = 0;

	for (int i = 0; i < n; i++)
	{
		m = max(m, schrage[i].R) + schrage[i].P;
		c = max(m + schrage[i].Q, c);
	}
	return c;
}

int Carlier::check_time_stop_working(int k)
{
	int m = 0;
	int c = 0;
	int i = 0;

	for (int i = 0; i < k; i++)
	{
		m = max(m, schrage[i].R) + schrage[i].P;
		c = max(m + schrage[i].Q, c);
	}
	return m;
}



int Carlier::schrage_normal() 
{
	//chcia³bym otrzymaæ dane w vectorze
	vector<zadanie> N;
	for (int i = 0; i < n; i++)
	{
		N.push_back(this->schrage[i]);
	}
	vector<zadanie> G;
	//zmienne do obliczenia czasu dzialania programu
	int m = 0;
	int c = 0;
	//reszta zmiennych programu
	int t = 0;
	zadanie e;
	int pe = 0;
	int t_next = 0;
	int pos = 0;
	//musimy tutaj dac liste zadan do wykonania, zeby mozna ich bylo dodac nieskonczenie wiele
	//list<zadanie> lista_zadan;
	//zadanie *tab_res = new zadanie[99];
	//odtworzenie kopca	

	std::make_heap(N.begin(), N.end(), CompareR()); //kopiec, w ktorym minimalizujemy R
	while (!G.empty() || !N.empty())
	{
		//odswiez zbior zadan gotowych
		while (!N.empty() && N[0].R <= t)
		{
			e = N[0];
			pe = N[0].P;
			G.push_back(e);
			push_heap(G.begin(), G.end(), CompareQ());
			pop_heap(N.begin(), N.end(), CompareR());
			N.pop_back();
		}
		//wyznacz t_next
		{
			if (!N.empty())
				t_next = N[0].R;
			else
				t_next = INT_MAX;
		}
		//jesli nie ma zadan gotowych, to przesuwamy sie do momentu gdy bedzie gotowe zadanie do realizacji
		if (G.empty())
		{
			t = t_next;
		}
		//jezeli mamy jakies zadania do wykonania. Tutaj bedzie roznica w algorytmie
		else
		{
			//e to nastepne zadanie do wykonania. w pseudokodzie to "j".
			e = G[0];
			//pe to czas wykonania nastepnego zadania
			pe = G[0].P;
			//wykonujemy cale zadanie
			{
				//usuwamy zadanie z kolejki gotowych do wykonania
				pop_heap(G.begin(), G.end(), CompareQ());
				G.pop_back();
				//przesuwamy sie do opdowiedniej chwili czasowej

				//aktualizujemy czas wykonania zadania
				m = max(m, t) + e.P;
				c = max(m + e.Q, c);
				t = t + pe;
			}
			this->schrage[pos++] = e;
		}
	}



	return c;
}


int Carlier::schrage_inter()
{
	//chcia³bym otrzymaæ dane w vectorze
	vector<zadanie> N;
	for (int i = 0; i < n; i++)
	{
		N.push_back(this->schrage[i]);
	}
	vector<zadanie> G;
	//zmienne do obliczenia czasu dzialania programu
	int m = 0;
	int c = 0;
	//reszta zmiennych programu
	int t = 0;
	zadanie e;
	int pe = 0;
	int t_next = 0;
	//musimy tutaj dac liste zadan do wykonania, zeby mozna ich bylo dodac nieskonczenie wiele
	//list<zadanie> lista_zadan;
	//odtworzenie kopca	

	std::make_heap(N.begin(), N.end(), CompareR()); //kopiec, w ktorym minimalizujemy R
	while (!G.empty() || !N.empty())
	{
		//odswiez zbior zadan gotowych
		while (!N.empty() && N[0].R <= t)
		{
			e = N[0];
			pe = N[0].P;
			G.push_back(e);
			push_heap(G.begin(), G.end(), CompareQ());
			pop_heap(N.begin(), N.end(), CompareR());
			N.pop_back();
		}
		//wyznacz t_next
		{
			if (!N.empty())
				t_next = N[0].R;
			else
				t_next = INT_MAX;
		}
		//jesli nie ma zadan gotowych, to przesuwamy sie do momentu gdy bedzie gotowe zadanie do realizacji
		if (G.empty())
		{
			t = t_next;
		}
		//jezeli mamy jakies zadania do wykonania. Tutaj bedzie roznica w algorytmie
		else
		{
			//e to nastepne zadanie do wykonania. w pseudokodzie to "j".
			e = G[0];
			//pe to czas wykonania nastepnego zadania
			pe = G[0].P;
			//wykonujemy zadanie j w czesci
			if (t_next < t + pe)
			{
				//aktualizacja czasu zadania
				pe = pe - (t_next - t);
				e.P = pe;
				pop_heap(G.begin(), G.end(), CompareQ());
				G.pop_back();
				G.push_back(e);
				push_heap(G.begin(), G.end(), CompareQ());
				//przechodzimy do nastepnej chwili czasowej
				t = t_next;
			}
			//wykonujemy cale zadanie j
			else
			{
				//usuwamy zadanie z kolejki gotowych do wykonania
				pop_heap(G.begin(), G.end(), CompareQ());
				G.pop_back();
				//przesuwamy sie do opdowiedniej chwili czasowej

				//aktualizujemy czas wykonania zadania
				m = max(m, t) + e.P;
				c = max(m + e.Q, c);
				t = t + pe;
			}
			//dodajemy zadanie do listy rozwiazan
		//	if (!lista_zadan.empty() && lista_zadan.back().id != e.id)
		//		lista_zadan.push_back(e);
		//	if (lista_zadan.empty())
		//		lista_zadan.push_back(e);
		}
	}
	//result_shrage ret;
	//ret.lista_zadan = lista_zadan;
	//ret.dlugoscUsz = c;

	return c;
}




int Carlier::do_carlier()
{
	//cout << flag << endl<< endl;
	++flag;
	int schr_lenght = this->schrage_normal();

	c = -1;

	if (schr_lenght < UB)
	{
		UB = schr_lenght;

		//przekopiowanie zadania optymalnego
		
		for (int i = 0; i < n; i++)
		{
			best[i] = schrage[i];
		}
	}


	//znalezeienie zadania b. Zacznijmy szukac od konca uszeregowania. Jesli czas zakonczenia go na maszynie + jego q== Cmax
	int c_max = check_time();

	for (int j = n; j > 0; --j)
	{
		if (check_time_stop_working(j) + schrage[j - 1].Q == c_max)
		{
			b = j - 1;
			break;
		}
	}

	
	//znalezienie zadania a. Zacznijmy szukac go od poczatku
	for (int j = 0; j < n; ++j)
	{
		int temp_1 = 0;

		for (int s = j; s <= b; ++s)
		{
			temp_1 += schrage[s].P;
		}

		int temp_final = schrage[j].R + temp_1 + schrage[b].Q;

		if (temp_final == c_max)
		{
			a = j;
			break;
		}

	}
	//znalezienie zadania c
	for (int j = b; j >= a; --j)
	{
		if (schrage[j].Q < schrage[b].Q)
		{
			c = j;
			break;
		}
	}
	//cout << "Zadanie a: " << schrage[a].id << " b: " << schrage[b].id << " c: " << schrage[c].id << endl;
	//jesli nie ma zadania krytycznego
	if (c == -1)
	{
		return UB;
	}

	//wyznaczenie R bloku K
	r_k = INT_MAX;
	for (int j = c + 1; j <= b; ++j)
	{
		if (schrage[j].R < r_k)
		{
			r_k = schrage[j].R;
		}
	}
	//wyznaczenie Q bloku K
	q_k = INT_MAX;
	for (int j = c + 1; j <= b; ++j)
	{
		if (schrage[j].Q < q_k)
		{
			q_k = schrage[j].Q;
		}
	}
	p_k = 0;
	//wyznaczenie p bloku K
	for (int j = c + 1; j <= b; ++j)
	{
		p_k += schrage[j].P;
	}


	//aktualizacja zadania krytycznego
	
	int num_backup_r = schrage[c].id;
	int r_backup = schrage[c].R;

	schrage[c].R = max(schrage[c].R, r_k + p_k);

	

	LB = schrage_inter();
	
	if (LB < UB)
	{
		//cout << "Wyrzucam: " << schrage[c].id << "na poczatek bloku"<< endl;
		//uruchamiamy carliera dla zmienionych danych i sprawdzamy czy udalo sie zrobic lepiej
		int temp = do_carlier();
		
		if (temp < UB)
		{
			UB = temp;
		}

	}
	//odtworzenie r
	int num_backup_q = -1;
	int q_backup = -1;
	for (int i = 0; i < n; i++)
	{
		if (num_backup_r == schrage[i].id)
		{
			schrage[i].R = r_backup;
			num_backup_q = schrage[i].id;
			q_backup = schrage[i].Q;
			schrage[i].Q = max(schrage[i].Q, q_k + p_k);
		}
	}

	//aktualizacja zadnia krytycznego


	//cout << "Dla zadania: " << num_backup_q << " zmieniam z Q " << q_backup << " do " << schrage[c].Q << endl;


	LB = schrage_inter();
	if (LB < UB)
	{
		UB = do_carlier();
	}

	//odtworzenie q
	for (int i = 0; i < n; i++)
	{
		if (num_backup_r == schrage[i].id)
		{
			//cout << "Dla zadania: " << schrage[i].id << " wracam z Q " << schrage[i].Q << " do " << q_backup << endl;
			schrage[i].Q = q_backup;
		}
	}

	return UB;
}
