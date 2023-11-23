#ifndef sintaxis_Autogram
#define sintaxis_Autogram
#include <vector>
#include <map>
using namespace std;

struct nodoTabla{
    int tipo;
    int numero;
};
struct nodoAutomata{
    vector <int> indice;
    vector <int> dir;
    vector <bool> visto;
    map<int,vector<int> > elementos;
    nodoAutomata(int t,int v):indice(vector<int>(t,v)){};
};

#endif