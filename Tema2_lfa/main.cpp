#include <iostream>
#include <fstream>
#include <string.h>
#include <typeinfo>
using namespace std;

class AFN
{
    int nr_total;            ///nr. stari totale
    char F[101];             ///starea/starile finala/finale
    char q0;                 ///starea initiala
    int nr_tranzitii;        ///cate tranzitii am
    char alf[256];           ///alfabetul
    int a;                  ///starea de la care pleaca o tranzitie
    char b[101];            /// starea/stariile la care ajunge o tranzitie
    char c;                 ///  tranzitiile

    char m[100][50][100];   ///matricea tranzitiilor

public:
    AFN(char *fisier)           ///constructor
    {
        int i;
        ifstream fin(fisier);

        fin>>nr_total;               ///citesc nr. stari totale
        fin>>q0;                     ///starea initiala
            fin>>F;                      ///citesc starea/starile finale
        fin>>alf;                   ///citesc alfabetul
        fin>>nr_tranzitii;          ///citesc cate tranzitii am
        int p=strlen(alf);
        for(i=0; i<nr_total; i++)
            for(int j=0; j<p; j++)
                strcpy(m[i][j],"-1");  /// pe m[i][j] punem -1

        for (i=0; i<nr_tranzitii; i++)
        {
            fin>>a>>c>>b;         ///citesc muchiile : a=starea din care pleaca muchia/linia
                                    ///  c=litera cu ajutorul careia se realizeaza tranzitia/coloana, b=starea in care ajunge=m[a][c-'a']
            for (int j=0; j<p; j++) ///construim matricea tranzitiilor
                if(alf[j]==c)
                {
                    strcpy(m[a][j],b);
                    break;
                }
        }


    }
    void reuniune(char s[], int col, char t[]);
    void sortare (char s[]);
    int cauta (char C[][100],int n, char t[]);
    int cauta_litera(char t[],char u[]);
    void Acceptare();

};

void interclasare (char s[],char t[], char inter[])
{
    int x,y;
    x=strlen(s);
    y=strlen(t);
    int i,j;
    i=0;
    j=0;
    int k=0;

    while(i<x&&j<y)
    {
        if(s[i]<t[j])
        {
            inter[k]=s[i];
            k++;
            i++;
        }
        else if(s[i]>t[j])
        {
            inter[k]=t[j];
            k++;
            j++;
        }
        else
        {
            inter[k]=t[j];
            k++;
            i++;
            j++;
        }

    }
    while(i<x)
    {
        inter[k]=s[i];
        k++;
        i++;
    }

    while(j<y)
    {
        inter[k]=t[j];
        k++;
        j++;
    }

    inter[k]='\0';
}

int AFN::cauta(char C[][100],int n, char t[])
{
    for(int i=0; i<=n; i++)
        if(strcmp(C[i],t)==0)   ///verificam daca cele doua siruri sunt egale din punct de vedere lexico-gramatical
            return 1;
    return 0;
}
void AFN::sortare(char s[])
{
    int x=strlen(s);
    char aux;
    for(int i=0; i<x-1; i++)
        for(int j=i+1; j<x; j++)
            if(s[i]>s[j])
            {
                aux=s[i];
                s[i]=s[j];
                s[j]=aux;
            }
}

int fcv1[256], fcv2[256];
int frecvente_litere(char s[], char t[]) ///returneaza 1 daca doua siruri au litere comune
{
    int x,y;
    x=strlen(s);
    y=strlen(t);
    for(int i=0; i<x; i++) /// punem 1 pe pozitia s[i]
        fcv1[s[i]]=1;
    for(int j=0; j<y; j++) /// punem 1 pe pozitia t[i]
        fcv2[t[j]]=1;

    for(int i=0; i<256; i++)
        if(fcv1[i]==fcv2[i])
            return 1;
    return 0;

}

void AFN::reuniune(char s[], int col, char t[])   ///realizeaza reuniune starilor in care se duc starile din s cu litera de la coloana col
{
    int x=strlen(s);
    t[0]='\0';   ///rezultatul va fi retinut in t
    char u[100], inter[100];
    int c;
    for(int i=0; i<x; i++)
    {
        c=s[i]-'0';         ///convertim pe s[i] din char in int

        strcpy(u,m[c][col]);   ///copiem in u starile in care se duce s[i]

        if(strcmp(u,"-1")!=0 && frecvente_litere(t,u)==0)   ///dorim ca starile sa fie distincte
        {
            strcat(t,u);

        }
        else if(strcmp(u,"-1")!=0&&frecvente_litere(t,u)==1) ///daca starile sunt la fel
        {

            interclasare(t,u, inter);  /// interclasam cele doua siruri

            strcpy(t,inter);
        }
        sortare(t);  ///sortam starile
    }

}

void AFN::Acceptare()
{
    int p,u;
    p=u=0;

    char C[101][100];
    C[0][0]=q0;
    char x[100],t[100];

    int z=strlen(alf);
    while(p<=u)
    {
        strcpy(x,C[p++]);
        if(strlen(x)!=0)
        {
            cout<<endl;
            cout<<"Starea "<<x<<"  ";
            cout<<endl;
        }
        for(int i=0; i<z; i++) ///parcurgem alfabetul/coloanele matricei
        {
            reuniune(x,i,t);
            if(strlen(x)!=0)
            {
                cout<<"Pentru simbolul "<< alf[i] <<" avem:";
                if(strlen(t)==0)
                    cout<<"-"<<endl;
                else
                    cout<<t<<endl;
            }
            if(cauta(C,u,t)==0)    ///verificam sa nu mai existe in coada starea curenta
            {
                strcpy(C[++u],t);
            }
        }

    }
    cout<<endl;
    cout<<"Starile finale sunt:  ";

    for(int i=0; i<=u; i++)
    {
        int v=strlen(C[i]);
        for(int j=0; j<v; j++)

            if(strchr(F,C[i][j]))
            {
                cout<<C[i]<< "   ";
                break;
            }
    }

}

int main()
{
    AFN a("AFN.in");
    a.Acceptare();
    return 0;
}
