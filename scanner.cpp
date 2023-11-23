#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>
#include <set>
#include "TRIE.cpp"
#include "automata.cpp"
#include "token.cpp"
#include "sintaxis.cpp"
#include "gramaut.cpp"
using namespace std;

int main(int argc,char *argv[]){
    nodo_TRIE *arbol = new nodo_TRIE();
    token registro_Tokens = token();
    nodo_TRIE *it = arbol;
    int cantidadTokens = 0;
    vector< string > reservadas = {"select", "distinct", "from"};
    vector<string> simbolos = {"*",",","."};
    vector<string> nombres = {"","select","distinct","from","star","coma","dot"};
    nombres.push_back("NUMERO");
    nombres.push_back("IDENTIFICADOR");
    nombres.push_back("CADENA");
    arbol->inicializa(cantidadTokens , reservadas);
    arbol -> inicializa(cantidadTokens , simbolos);
    /*for(int i = 1; i < argc ; i++){
        cout << argv[i] << "\n";
    }*/
    arbol->pasito('-')->pasito('-')->trabado=1;
    arbol->pasito('/')->pasito('*')->trabado=2;
    arbol->pasito('*')->pasito('/')->trabado=3;
    cantidadTokens++;
    nodo_TRIE actual;
    //arbol -> saca_Tokens();
    //------------------Chequeo de sintáxis----------------------------------------
    map<string,int> terminos;
    map<int,string> inversoterminos;
    vector<set<int> > primeros;
    vector<set<int> > siguientes;
    int todosComponentes=0;
    int ptotales=0;
    if(!registro(terminos,primeros,siguientes,arbol,cantidadTokens+1,todosComponentes,inversoterminos,ptotales))return 0;
    vector<vector<int> > lecturas;
    guarda_registro(lecturas);
    //cout<<":)\n";
    /*for(int i=1;i<todosComponentes;i++){
        cout<<inversoterminos[i]<<"::\n{";
        for(int z:primeros[i]){
            if(z>cantidadTokens+1){cout<<"Epsilon, ";continue;}
            cout<<nombres[z]<<", ";
        }
        cout<<"}\n";
    }
    cout<<"\n\n";
    for(int i=1;i<todosComponentes;i++){
        cout<<inversoterminos[i]<<"::\n{";
        for(int z:siguientes[i]){
            if(z>cantidadTokens+1){cout<<"Epsilon, ";continue;}
            cout<<nombres[z]<<", ";
        }
        cout<<"}\n";
    }
    cout<<terminos.size()-cantidadTokens-1<<"\n";
    */
    //vector<vector<vector<int> > > tabla(terminos.size()+1,vector<vector<int> >(cantidadTokens+4));
    //int epsilon = cantidadTokens+1;
    //if(!entabla(primeros,siguientes,tabla,cantidadTokens+2,terminos["3ps"],terminos["1d"]))return 0;
    vector<nodoAutomata> ascendente(1);
    ascendente.push_back(nodoAutomata(ptotales,0));
    vector<vector<nodoTabla> > tabla;
    entabla(tabla,ascendente,ptotales);
    //-----------------------------------------------------------------------------
    bool existe_Error=0;
    bool comentariote = 0;
    ifstream fin;
    fin.open(argv[1]);
    if(argc>1){
        bool errores_general=0;
        string lecturas;
        while(getline(fin,lecturas)){
            existe_Error = evalua(lecturas,arbol,cantidadTokens,nombres,comentariote,registro_Tokens);
            errores_general|=existe_Error;
            if(existe_Error)continue;
            //registro_Tokens.recorre();
        }
        if(errores_general)cout<<"El programa termino con errores\n";
        else cout<<"El programa termino exitosamente\n";
    }else{
        string lectura;
        while(1){
            getline(cin,lectura);
            existe_Error = evalua(lectura,arbol,cantidadTokens,nombres,comentariote,registro_Tokens);
            if(existe_Error){
                while(registro_Tokens.indice_final>registro_Tokens.indice_inicial){
                    registro_Tokens.indice_final--;
                    registro_Tokens.elementos.pop_back();
                }
            }
            if(existe_Error)continue;
            //cout<<registro_Tokens.indice_inicial<<","<<registro_Tokens.indice_final<<"::\n";
            bool correcto;
            //correcto = 
            
            if(!correcto){
                while(registro_Tokens.indice_final>registro_Tokens.indice_inicial){
                    registro_Tokens.indice_final--;
                    registro_Tokens.elementos.pop_back();
                }
                continue;
            }
            registro_Tokens.indice_inicial=registro_Tokens.indice_final;
            //registro_Tokens.recorre();
        }
    }
}