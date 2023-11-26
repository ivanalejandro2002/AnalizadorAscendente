#ifndef sintaxis_Autogram
#define sintaxis_Autogram
#include <vector>
#include <map>
#include <queue>
using namespace std;
int estadoFinal=-1;
queue<pair<int,bool> > orden;
map<vector<int> , int> tradEstados;
struct nodoTabla{
    int tipo;
    int numero;
};
struct nodoAutomata{
    bool visto;
    vector<bool> metidos;
    vector <int> indices;
    vector <pair<int,int> > dir;
    map<int,vector<int> > elementos;
    nodoAutomata(int t,int v):metidos(vector<bool>(t)),indices(vector<int>(t,v)),visto(0){};
    void resetea(int x){
        metidos.clear();
        metidos.resize(x);
    }
};

#endif