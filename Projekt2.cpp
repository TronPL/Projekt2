#include<iostream>
#include<vector>
#include<stack>
#include <future>
#include <thread>
using namespace std;

struct graf {
    bool stos = 0; //czy dodany na stos
    vector <int> polaczenia; //do przechowywania połączeń
}*w;

void DFS(int n)
{
    cout << "Podaj liczbe wierzcholkow w grafie: " << endl;
    int p, a, b;
    cin >> n;
    w = new graf[n + 1];//przydzielenie pamięci na wierzchołki grafu
    //wczytanie wierzchołków grafu
    cout << "Podaj liczbe polaczen: " << endl;
    cin >> p;

    for (int i = 0; i < p; i++)
    {
        cout << "Podaj numery wierzcholkow, ktore chcesz ze soba polaczyc: " << endl;
        cin >> a >> b;
        w[a].polaczenia.push_back(b); //połączenie jest dwukierunkowe a-->b
        w[b].polaczenia.push_back(a); //b-->a
    }
    n = 1;
    stack<int> stos;    //utworzenie stosu 
    stos.push(n);  //dodanie pierwszego wierzcholka na stos
    while (!stos.empty()) //dopóki jest cos na stosie
    {
        n = stos.top(); //pobranie elementu ze stosu

        stos.pop(); //usuń pobrany element ze stosu
        cout << "Odwiedzono wierzcholek o numerze: " << n << endl; //odwiedź go i zrób coś

        for (int i = 0; i < w[n].polaczenia.size(); i++)
            if (!w[w[n].polaczenia[i]].stos)
            {
                if (w[n].polaczenia[i] != 1)
                {
                    stos.push(w[n].polaczenia[i]);
                    w[w[n].polaczenia[i]].stos = 1; //oznaczenie, że dodano na stos
                    cout << "Dodano na stos wierzcholek nr " << w[n].polaczenia[i] << endl;
                }
            }
    }
    delete[] w;
}

int main()
{
    //przeszukaj graf
    std::packaged_task<void(int)> tsk(DFS);
    std::thread test(std::move(tsk),1);
    test.join();
    return 0;
}