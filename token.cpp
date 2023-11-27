#ifndef token_Cabecera
#define token_Cabecera
#include <iostream>
#include <vector>
#include <stack>
#include "gramaut.cpp"
using namespace std;
struct nodo_Token{
    int token;
    string tipo_Token;
    string lexema;
};
struct token{
    int indice_inicial,indice_final;
    vector<nodo_Token> elementos;
    token():indice_inicial(0),indice_final(0){};
    void agrega(int &numero_Token,string &tipoToken,string &lexema){
        elementos.push_back({numero_Token,tipoToken,lexema});
        indice_final++;
    }
    void recorre(){
        for(indice_inicial;indice_inicial<indice_final;indice_inicial++){
            cout<<elementos[indice_inicial].tipo_Token<<","<<elementos[indice_inicial].token<<"::"<<elementos[indice_inicial].lexema<<"\n";
        }
    }
    void elimina(){
        elementos.pop_back();
        indice_final--;
    }

    bool sintaxisea(vector<vector<nodoTabla> > tabla,int inicio,int fin,int cantidadTokens,vector<vector<int> > &lecturas,vector<int> &varOriginal,vector<string> &nombres,map<int,string> &inversoTerminos){
        stack<int> pila;
        stack<int> simbolos;
        pila.push(1);
        for(int i =inicio;i<=fin;){
            //cout<<":|";
            int posactual = pila.top();
            //cout<<i<<","<<fin<<"\n";
            nodo_Token z;
            if(i<fin)
                z = elementos[i];
            else z={0,"Vacio","epsilon"};
            int x;
            if(i<fin)x = z.token;
            else x = 0;
            //cout<<posactual<<","<<x<<"::";
            
            if(tabla[posactual][x].tipo==0){
                cout<<"No se esperaba el termino "<<nombres[x];
                if(x==cantidadTokens)cout<<" "<<z.lexema;
                cout<<" en el elemento "<<i-inicio+1<<"\n";
                return 0;
            }
            //cout<<tabla[posactual][x].tipo<<","<<tabla[posactual][x].numero<<"\n";
            if(tabla[posactual][x].tipo==1){
                pila.push(tabla[posactual][x].numero);
                simbolos.push(x);
                i++;
            }else if(tabla[posactual][x].tipo==2){
                for(int j = lecturas[tabla[posactual][x].numero].size()-1;j>=0;j--){
                    //cout<<simbolos.top()<<":_"<<lecturas[tabla[posactual][x].numero][j]<<"\n";
                    if(lecturas[tabla[posactual][x].numero][j]!=0){
                        if(pila.size()==0 || simbolos.size()==0 || simbolos.top()!=lecturas[tabla[posactual][x].numero][j]){
                            cout<<"Se esperaba una produccion del tipo: ";
                            cout<<inversoTerminos[varOriginal[tabla[posactual][x].numero]]<<" -> ";
                            for(int w: lecturas[tabla[posactual][x].numero]){
                                if(w<=cantidadTokens)
                                    cout<<nombres[w]<<" ";
                                else cout<<inversoTerminos[w]<<" ";
                            }
                            cout<<"\n";
                            return 0;
                        }
                        simbolos.pop();
                        pila.pop();
                    }
                }
                simbolos.push(varOriginal[tabla[posactual][x].numero]);
                //cout<<varOriginal[tabla[posactual][x].numero]<<",,\n";
                posactual = pila.top();
                //cout<<posactual<<"\n";
                if(tabla[posactual][simbolos.top()].numero==0){
                    cout<<"La tabla no se construyo adecuadamente\n";
                    return 0;
                }
                pila.push(tabla[posactual][simbolos.top()].numero);
            }else if(tabla[posactual][x].tipo==3){
                cout<<"Aceptada\n";
                return 1;
            }
        }    
        cout<<"La instruccion esta incompleta\n";
        return 0;
    }
};
#endif