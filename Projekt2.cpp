#include<iostream>
#include<vector>
#include<stack>
#include <future>
#include <thread>
using namespace std;

struct graf {
    bool stos = 0;
    vector <int> polaczenia;
}*w;

void DFS(int n)
{
    cout << "Podaj liczbe wierzcholkow w grafie: " << endl;
    int p, a, b;
    cin >> n;
    w = new graf[n + 1];
    cout << "Podaj liczbe polaczen: " << endl;
    cin >> p;

    for (int i = 0; i < p; i++)
    {
        cout << "Podaj numery wierzcholkow, ktore chcesz ze soba polaczyc: " << endl;
        cin >> a >> b;
        w[a].polaczenia.push_back(b); 
        w[b].polaczenia.push_back(a); 
    }
    n = 1;
    stack<int> stos; 
    stos.push(n);
    while (!stos.empty())
    {
        n = stos.top();

        stos.pop();
        cout << "Odwiedzono wierzcholek o numerze: " << n << endl;

        for (int i = 0; i < w[n].polaczenia.size(); i++)
            if (!w[w[n].polaczenia[i]].stos)
            {
                if (w[n].polaczenia[i] != 1)
                {
                    stos.push(w[n].polaczenia[i]);
                    w[w[n].polaczenia[i]].stos = 1;
                    cout << "Dodano na stos wierzcholek nr " << w[n].polaczenia[i] << endl;
                }
            }
    }
    delete[] w;
}

int main()
{
    while (1)
    {
        std::packaged_task<void(int)> tsk(DFS);
        std::thread test(std::move(tsk), 1);
        test.join();
    }
    return 0;
}