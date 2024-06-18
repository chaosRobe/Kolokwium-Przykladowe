#include <iostream>
using namespace std;
class Klient
{
private:
	char nazwa[25];
public:
	void set_nazwa(const char le_tablica[25])
	{
		for (int i = 0; i < 25; i++)
		{
			nazwa[i] = le_tablica[i];
		}
	}
	char* get_nazwa()
	{
		return nazwa;
	}
	void wypisz() 
	{
		for (int i = 0; i < 25; i++)
		{
			cout<< nazwa[i];
		}
	}
};
class Konto_Bankowe 
{
private:
	unsigned int numer_konta[26];
	double stan_konta;
	bool stan_aktywnosci; //hmm
	Klient* wlasciciel;
	
public:
	static int liczba_instancji;
	Konto_Bankowe()
	{
		for (int i = 0; i < 26; i++)
		{
			numer_konta[i] = 0;
		}
		stan_konta = 0;
		stan_aktywnosci = false;
		wlasciciel = nullptr;
		liczba_instancji++;
	}
	Konto_Bankowe(int* id, double $, bool stan, Klient* klient)
	{
		for (int i = 0; i < 26; i++)
		{
			if (id[i] > 9) numer_konta[i] = 9;
			else numer_konta[i] = id[i];
		}
		stan_konta = $;
		stan_aktywnosci = stan;
		wlasciciel = klient;
		liczba_instancji++;
	}
	~Konto_Bankowe()
	{
	liczba_instancji--;
	}
	void set_numer_konta(unsigned int id[26])
	{
		for (int i = 0; i < 26; i++)
		{
			if (id[i] > 9) numer_konta[i] = 9;
			else numer_konta[i] = id[i];
		}
	}
	void set_stan_konta(double $)
	{
		stan_konta = $;
	}
	void set_czy_aktywne(bool taknie)
	{
		stan_aktywnosci = taknie;
	}
	void set_wlasciciel(Klient* klient)
	{
		wlasciciel = klient;
	}
	unsigned int* get_numer_konta() 
	{
		return numer_konta;
	}
	double get_stan_konta()
	{
		return stan_konta;
	}
	bool get_stan_aktywnosci()
	{
		return stan_aktywnosci;
	}
	Klient* get_wlasciciel()
	{
		return wlasciciel;
	}
	virtual double stan_konta_po_roku()
	{
		return get_stan_konta();
	}
	operator double()
	{
		return stan_konta;
	}
	static Konto_Bankowe klient_to_konto(Klient& nowy)
	{
		int numer[26];
		for (int i = 0; i < 26; i++)
		{
			numer[i] = rand() % 10;
		}
		//int* wsk = &numer[0];
		Konto_Bankowe nowe(numer, 0, true, &nowy);
	};
	void operator+(double liczba)
	{
		stan_konta = stan_konta + liczba;
	}
	void wypiszNumer()
	{
		for (int i = 0; i < 26; i++)
		{
			cout << numer_konta[i];
		}
	}
};
int Konto_Bankowe::liczba_instancji = 0;

std::ostream& operator<<(std::ostream& str, Konto_Bankowe& konto)
{
	if (konto.get_stan_aktywnosci() == true)
	{
		konto.wypiszNumer();
		cout << " ";
		konto.get_wlasciciel()->wypisz();
		cout << " : ";
		cout << konto.get_stan_konta();
	}
	else 
	{
		konto.wypiszNumer();
		cout << " NIEAKTYWNE";
	}
	return str;
}
class Konto_Oszczednosciowe : public Konto_Bankowe
{
private:
	int stopa_oprocentowania;
public:
	void set_stopa_oprocentowania(int wartosc)
	{
		if (wartosc < 0) stopa_oprocentowania = 0;
		else stopa_oprocentowania = wartosc;
	}
	int get_stopa_oprocentowania()
	{
		return stopa_oprocentowania;
	}
	double stan_konta_po_roku() override
	{
		return get_stan_konta() * (1 + stopa_oprocentowania / 100.00);
	}
};

int main() 
{
	{
		Klient Nowy;
		Nowy.set_nazwa("ni");
		Konto_Bankowe konto_test;
		Konto_Oszczednosciowe konto_test2;
		konto_test2.set_stan_konta(100);
		konto_test2.set_stopa_oprocentowania(10);
		cout<<konto_test2.stan_konta_po_roku()<<endl;

		konto_test2 + 1000.0;
		konto_test2.set_wlasciciel(&Nowy);
		cout<<konto_test2.get_stan_konta() << endl;
		cout << konto_test2<<endl;
		konto_test2.set_czy_aktywne(true);
		cout << konto_test2;
		//cout<<Konto_Bankowe::liczba_instancji;
	}
	//cout << Konto_Bankowe::liczba_instancji;
}