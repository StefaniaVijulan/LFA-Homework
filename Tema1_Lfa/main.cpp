#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

 struct tranz
    {
        int a,b;    ///tranzitiile
        char c;
    };

            /// cuvantul       starea curenta    pozitia st_totale nr_tranz nr_st_f  s_f
int verifica(char cuvant[], int stare_curenta, int pozitie, int n,int nr, int f, int F[], tranz G[], int &ok)
{
    int i;
     ok=0;     ///variabila cu valoarea 0 daca cuvantul nu este acceptat si 1 in caz contrar

    if ((pozitie==strlen(cuvant))&&(stare_curenta<=n)) ///daca am terminat cuvantul si nu am depasit numarul de stari
    {
        ///verific daca ma aflu intr-o stare finala
        for (i=0;i<f;i++)
            if (stare_curenta==F[i])
            {
                ok=1;
                return 1;
            }
    }
    else
    {
        for (i=0;i<nr;i++)
        {
            ///daca exista este 1, nu il las sa se mai apeleze recursiv, ci ii opresc orice apel recursiv curent sau
            ///aflat pe stiva returnand true, astfel fortandu-l sa se termine
            if (ok==1)
                return 1;
            ///daca if-ul de mai sus nu este executat, testez daca starea mea curenta si litera curenta din cuvant se afla
            ///in vreun triplet, iar in caz afirmativ backtracking-ul continua
            if ((G[i].a==stare_curenta)&&(G[i].c==cuvant[pozitie]))

                verifica(cuvant,G[i].b,pozitie+1,n,nr,f,F,G,ok);

        }
        return 0;
    }
}
int main()
{
    int n;          ///nr. stari totale
    int f;          ///nr. stari finale
    int F[100];         ///starea/starile finala/finale
    int q0;          ///starea initiala
    int nr;          ///cate triplete/tranzitii am
    tranz G[100];
    int stare_curenta;      ///starea curenta
    int ok=0;       ///variabila cu valoarea 0 daca cuvantul nu apartine nu este acceptat si 1 in caz contrar

    ifstream fin("afn.in");
    int i;
         ///citesc nr. stari totale, nr. stari finale si starea initiala
        fin>>n;
        fin>>f;
        fin>>q0;
        for (i=0;i<f;i++)
            fin>>F[i];           ///citesc starea/starile finale

        fin>>nr;                  ///citesc cate triplete am
        for (i=0;i<nr;i++)
        {
            fin>>G[i].a>>G[i].b>>G[i].c;         ///citesc tripletele
        }

    char cuvant[256];      ///declaram cuvantul pe care dorim sa-l verificam
    cout<<"Cuvantul este: ";
    cin.getline(cuvant,256);  /// citim cuvantul

    if(strcmp(cuvant," ")==0)    ///daca este cuvantul vid
        {
            for(i=0;i<f&&ok==0;i++)
                if(q0==F[i])  ///verificam daca starea initiala este si stare finala si asta inseamna ca este cuvant acceptat
                ok=1;

        }
        else
      verifica(cuvant,q0,0,n,nr,f,F,G,ok);


    if(ok==1)
        cout<<"Cuvant acceptat";
    else
        cout<<"Cuvant neacceptat";

    fin.close();

    return 0;
}



