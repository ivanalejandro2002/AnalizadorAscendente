#ifndef sintaxis_Cabecera
#define sintaxis_Cabecera
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <stack>
#include <cassert>
#include "gramaut.cpp"
using namespace std;
struct nodoCiclo{
    int grupos;
    vector<int> cuentas;
    bool epsilon;
    void inicializa(){
        cuentas.resize(grupos+1);
    }
};
struct aristaCiclo{
    int destino;
    int grupo;
    int prioridad;
};
int act= 0;
struct nodoPendientes{
    int fila;
    int columna;
    int tipo;
};
bool entabla(vector<vector<nodoTabla> > &tabla, vector<nodoAutomata> &ascendente, int ptotales,int nodo,vector<vector<int> > &lecturas,int espacios,vector<set<int> > &siguientes,int normales,vector<vector<int> > &cualesProducciones, vector<int> &varOriginal){   
    vector<nodoPendientes> pendientes;
    for(int pii=0;pii<lecturas.size();pii++){
        if((int)ascendente[nodo].indices[pii]>=(int)lecturas[pii].size() || lecturas[pii][ascendente[nodo].indices[pii]]==0){
            cout<<"@"<<pii<<ascendente[nodo].indices[pii]<<","<<lecturas[pii].size()<<"@";
            ascendente[nodo].indices[pii]=-1;
            cout<<":0";
            for(int reduc: siguientes[varOriginal[pii]]){
                cout<<reduc<<",";
                pendientes.push_back({nodo,reduc,2});
                /*if(tabla[nodo][reduc].tipo!=0){
                    cout<<"La gramatica es redundante por la derecha\n";
                    return 0;
                }
                tabla[nodo][reduc]={2,zi};
                */
            }
            cout<<":__:";
        }
    }
    if(ascendente[nodo].visto)return 1;
    for(int i =0;i<lecturas.size();i++){
        if(ascendente[nodo].indices[i]<0)continue;
        ascendente[nodo].elementos[lecturas[i][ascendente[nodo].indices[i]]].push_back(i);
    }
    map<int,vector<int> >::iterator it;
    for(it=ascendente[nodo].elementos.begin();it!=ascendente[nodo].elementos.end();it++){

        pair<int,vector<int> > z;
        z.first = it->first;
        z.second = it->second;
        cout<<")";
        cout<<z.first<<"::(";
        while(!orden.empty())orden.pop();
        ascendente[nodo].resetea(ptotales+2);
        vector<int> aux(ascendente[nodo].indices.size(),-1);
        for(auto zi: z.second){
            cout<<zi<<",";
            ascendente[nodo].metidos[zi]=1;
            orden.push({zi,1});
        }
        while(!orden.empty()){
            pair<int,bool> frentecola = orden.front();
            int zi = frentecola.first;
            cout<<zi<<",";
            orden.pop();
            
            if(frentecola.second)
                aux[zi]=ascendente[nodo].indices[zi]+1;
            else aux[zi] = 0;
            if(aux[zi]>=lecturas[zi].size()){
                
            }else{
                //pendientes.push_back({nodo,lecturas[zi][aux[zi]],1});
                cout<<":|";
                if(lecturas[zi][aux[zi]]>normales){
                    cout<<"_"<<lecturas[zi][aux[zi]]-normales-1;
                    cout<<"#"<<aux[lecturas[zi][aux[zi]]-normales-1];
                    for(int variables:cualesProducciones[lecturas[zi][aux[zi]]]){
                        if(ascendente[nodo].metidos[variables])continue;
                        if(aux[variables]>0){
                            cout<<"La gramatica es redundante por la derecha version II\n";
                            return 0;
                        }
                        if(aux[variables]<0){
                            ascendente[nodo].metidos[variables]=1;
                            cout<<"meto{"<<variables<<"}";
                            orden.push({variables,0});
                        }
                    }
                }
            }
        }
        cout<<"YAY";
        if(!tradEstados[aux]){
            tabla.push_back(vector<nodoTabla>(espacios,{0,0}));
            cout<<z.first<<"OOO";
            cout<<tabla[nodo].size();
            if(tabla[nodo][z.first].numero>0){
                cout<<"La gramatica tiene redundancias por la derecha :(\n";
                return 0;
            }
            ascendente.push_back(nodoAutomata(ascendente[nodo].indices.size(),-1));
            ascendente[ascendente.size()-1].indices = aux;
            cout<<ascendente.size()-1<<":&&\n";
            for(int z:aux){
                cout<<z<<",";
            }
            cout<<"\n";
            tradEstados[aux]=ascendente.size()-1;
            if(nodo == 1 && z.first==normales+1)estadoFinal=ascendente.size()-1;
        }else{
            int auxiliar = tradEstados[aux];
            cout<<"Dirigiendo a "<<auxiliar<<"\n";
            if(tabla[nodo][z.first].tipo==2){
                cout<<"La gramatica tiene redundancias por la derecha R y S\n";
                return 0;
            }
            if(tabla[nodo][z.first].numero>0 && tabla[nodo][z.first].numero!=auxiliar){
                cout<<"La gramatica tiene redundancias por la derecha S y S\n";
                return 0;
            }
            tabla[nodo][z.first]={1,auxiliar};
        }
        cout<<"\n\t";
        int direccionandose = tradEstados[aux];
        cout<<direccionandose<<":____\n";
        ascendente[nodo].dir.push_back({direccionandose,z.first});
        if(tabla[nodo][z.first].tipo==2){
            cout<<"La gramatica tiene redundancias por la derecha VI\n";
            return 0;
        }
        if(tabla[nodo][z.first].tipo==1 && tabla[nodo][z.first].numero!=direccionandose){
            cout<<"La gramatica tiene redundancias por la derecha VII\n";
            return 0;
        }
        tabla[nodo][z.first]={1,direccionandose};
        cout<<"TErmino\n";
        cout<<"\n";
    }


    for(auto w:pendientes){
        cout<<"["<<nodo<<","<<tabla.size()<<"]";
        cout<<"{"<<w.fila<<","<<w.columna<<","<<w.tipo<<"} ("<<tabla[w.fila][w.columna].tipo<<","<<tabla[w.fila][w.columna].numero<<")";
        if(tabla[w.fila][w.columna].tipo>0 && tabla[w.fila][w.columna].tipo!=w.tipo){
            cout<<"La gramatica tiene redundancias por la derecha IV\n";
            return 0;
        }
        if(tabla[w.fila][w.columna].tipo>0 && tabla[w.fila][w.columna].numero != w.columna){
            cout<<"La gramatica tiene redundacias por la derecha V\n";
        }
        tabla[w.fila][w.columna] = {2,w.columna};
    }
    ascendente[nodo].visto=1;
    bool ret=1;
    for(pair<int,int> z:ascendente[nodo].dir){
        cout<<"\n................."<<z.first<<"\n";
        for(int z:ascendente[z.first].indices){
            cout<<z<<",";
        }
        cout<<"\n";
        ret&=entabla(tabla,ascendente,ptotales,z.first,lecturas,espacios,siguientes,normales,cualesProducciones,varOriginal);
        if(!ret)return 0;
    }
    return ret;
}

bool tarjan(int nodo,vector<vector<aristaCiclo> > &mapa,vector<nodoCiclo> &infoNodos,vector<int> &vis,vector<pair<int,int> > &visitas,vector<int> &dag,stack<int> &pila,int &cont,int cantidadTokens,int codeps){
    if(vis[nodo] > 0)return infoNodos[nodo].epsilon;
    vis[nodo] = 1;
    visitas[nodo].first = visitas[nodo].second=++act;
    pila.push(nodo);

    for(auto z:mapa[nodo]){
        /*if(nodo ==9){
            cout<<nodo<<","<<z.destino<<","<<infoNodos[nodo].cuentas[z.grupo]<<","<<z.prioridad<<"\n";
        }*/
        if(infoNodos[nodo].cuentas[z.grupo]<z.prioridad)continue;
        //if(nodo == 9)cout<<"O\n";
        if(!vis[z.destino]){
            bool x = tarjan(z.destino,mapa,infoNodos,vis,visitas,dag,pila,cont,cantidadTokens,codeps);
            infoNodos[nodo].epsilon|=x;
            if(x  && z.destino>cantidadTokens)infoNodos[nodo].cuentas[z.grupo]++;
            visitas[nodo].second = min(visitas[nodo].second,visitas[z.destino].second);
        }else{
            if(infoNodos[z.destino].epsilon  && z.destino>cantidadTokens)infoNodos[nodo].cuentas[z.grupo]++;
            infoNodos[nodo].epsilon|=infoNodos[z.destino].epsilon;
            if(vis[z.destino]==1){
                visitas[nodo].second = min(visitas[nodo].second,visitas[z.destino].first);
            }
        }
    }

    int k = 0;
    if(visitas[nodo].first == visitas[nodo].second){
        cont++;
        int zi =0;
        do{
            k = pila.top();
            pila.pop();
            dag[k] = cont;
            vis[k] = 2;
        }while(k!=nodo);
    }
    return infoNodos[nodo].epsilon;
}

void busca(int nodo, vector<set<int> > &primeros, vector<vector<int> > &mapa,vector<int> &vis,int cantidadTokens,int g1,int g2){
    if(vis[nodo])return;
    vis[nodo]=1;
    for(int z:mapa[nodo]){
        busca(z,primeros,mapa,vis,cantidadTokens,g1,g2);
        for(int w:primeros[z])if(w<=cantidadTokens || w==g1 || w==g2)primeros[nodo].insert(w);
    }
}


void buscasegundo(int nodo, vector<set<int> > &primeros, vector<vector<int> > &mapa,vector<int> &vis,int cantidadTokens){
    if(vis[nodo])return;
    vis[nodo]=1;
    for(int z:mapa[nodo]){
        buscasegundo(z,primeros,mapa,vis,cantidadTokens);
        for(int w:primeros[z])primeros[nodo].insert(w);
    }
}

bool registro(map<string,int> &traductor,vector<set<int> > &primeros,vector<set<int> > &siguientes, nodo_TRIE *arbol,int cantidadTokens,int &todosComponentes,map<int,string> &inversoterminos, int &ptotales){
    ifstream fin;
    fin.open("gramatica");
    ofstream fout;
    fout.open("gramTraduc");
    string cad;
    int cont=cantidadTokens+1;
    int z = cont;
    while(getline(fin,cad)){
        string aux="";
        for(int i=0;cad[i]!=' ';i++){
            aux+=cad[i];
        }
        if(!traductor[aux]){
            traductor[aux]=cont++;
            inversoterminos[cont-1]=aux;
        }
    }
    int extras = cont;
    fin.close();
    fin.open("gramatica");
    vector<bool> vistos(traductor.size()+1);
    primeros.resize(cantidadTokens+cont+5);
    siguientes.resize(cantidadTokens+cont+5);
    vector<vector<aristaCiclo> > mapa(cantidadTokens+cont+5);
    vector<nodoCiclo> infoNodos(cantidadTokens+cont+5);
    vector<int> vis(cantidadTokens+cont+5);
    vector<pair<int,int> > visitas(cantidadTokens+cont+5);
    vector<int> dag(cantidadTokens+cont+5);
    stack<int> pila;
    int componentes = 0;
    while(getline(fin,cad)){
        ptotales++;
        vector<int> elementos;
        fout<<z<<" ";
        int i = 0;
        while(cad[i]!=' ')i++;
        while(i<cad.size()){
            while(cad[i]!=cad.size() && cad[i]==' ')i++;
            if(i>=cad.size())continue;
            string aux = "";
            nodo_TRIE *pasito = arbol;
            while(i<cad.size() && cad[i]!=' '){
                aux+=cad[i];
                if(pasito!=nullptr)pasito = pasito->mov_seguro(cad[i]);
                i++;
            }
            if(aux == "|"){
                ptotales++;
                fout<<elementos.size()<<" ";
                for(int z: elementos)fout<<z<<" ";
                elementos.clear();
                fout<<"\n";
                fout<<z<<" ";
                continue;
            }
            if(aux == "1d"){
                if(!traductor["1d"]){
                    traductor["1d"]=extras++;
                    inversoterminos[extras-1]="1d";
                }
                elementos.push_back(traductor["1d"]);
            }else if(aux == "3ps"){
                if(!traductor["3ps"]){
                    traductor["3ps"]=extras++;
                    inversoterminos[extras-1]="3ps";
                }
                elementos.push_back(traductor["3ps"]);
            }else if(traductor[aux]){
                elementos.push_back(traductor[aux]);
            }else{
                if(pasito == nullptr){
                    cout<<"Error la palabra reservada "<<aux<<" no existe\n";
                    return false;
                }
                elementos.push_back(pasito->token);
            }
        }
        fout<<elementos.size()<<" ";
        for(int z:elementos)fout<<z<<" ";
        fout<<"\n";
        z++;
    }
    fout.close();
    fin.close();
    fin.open("gramTraduc");
    int origen,siguiente,elementos;
    int ant = -1;
    int rep = 0;
    while(fin>>origen){
        if(origen!=ant){
            rep = 0;
            ant = origen;
        }
        rep++;
        infoNodos[origen].grupos++;
        fin>>elementos;
        for(int i =0;i<elementos;i++){
            fin>>siguiente;
            mapa[origen].push_back({siguiente,infoNodos[origen].grupos,i});
        }
    }
    fin.close();

    for(int i =cantidadTokens+1;i<cont;i++)
        infoNodos[i].inicializa();

    infoNodos[traductor["3ps"]].epsilon = 1;
    for(int i =1;i<extras;i++)
        tarjan(i,mapa,infoNodos,vis,visitas,dag,pila,componentes,cantidadTokens,traductor["3ps"]);
    
    /*for(int i =1;i<extras;i++){
        cout<<i<<","<<dag[i]<<"::<<"<<infoNodos[i].epsilon<<"\n";
    }*/

    set<pair<int,int> > listo;
    vector<vector<int> > dagueado(componentes+2);
    for(int i =1;i<extras;i++){
        for(auto z: mapa[i]){
            if(dag[i]!=dag[z.destino]){
                if(infoNodos[i].cuentas[z.grupo]>=z.prioridad && !listo.count({dag[i],dag[z.destino]})){
                    dagueado[dag[i]].push_back(dag[z.destino]);
                    listo.insert({dag[i],dag[z.destino]});
                }
            }
        }
    }
    vector<set<int> >primerosdag(componentes+2);
    vis.clear();
    vis.resize(componentes+2);
    for(int i =1;i<=cantidadTokens;i++){
        primerosdag[i].insert(i);
    }
    primerosdag[dag[traductor["3ps"]]].insert(traductor["3ps"]);
    primerosdag[dag[traductor["1d"]]].insert(cantidadTokens);
    for(int i=1;i<=componentes;i++){
        busca(i,primerosdag,dagueado,vis,cantidadTokens,traductor["3ps"],traductor["1d"]);
    }
    vector<vector<int> > tradag(componentes+2);
    for(int i=1;i<extras;i++){
        tradag[dag[i]].push_back(i);
    }
    //cout<<":0";
    for(int i=1;i<=componentes;i++){
        for(int z:tradag[i]){
            for(int zi: primerosdag[i]){
                if(zi==traductor["3ps"])continue;
                primeros[z].insert(zi);
            }
            if(infoNodos[z].epsilon)primeros[z].insert(traductor["3ps"]);
        }
    }
    /*for(int i=1;i<=componentes;i++){
        cout<<i<<":: ";
        for(int z:primerosdag[i])cout<<z<<",";
        cout<<"\n";
    }
    for(int i =1;i<=componentes;i++){
        cout<<i<<"|||";
        for(int z:dagueado[i])cout<<z<<",";
        cout<<"\n";
    }
    for(int i=cantidadTokens+1;i<cont;i++){
        cout<<i<<"__";
        for(int z:infoNodos[i].cuentas)cout<<z<<",";
        cout<<"\n";
    }*/
    todosComponentes = extras;
    mapa.clear();
    mapa.resize(cantidadTokens+cont+5);

    vis.clear();
    visitas.clear();
    dag.clear();
    vis.resize(cantidadTokens+cont+5);
    visitas.resize(cantidadTokens+cont+5);
    dag.resize(cantidadTokens+cont+5);
    dagueado.clear();
    fin.open("gramTraduc");
    while(fin>>origen){
        fin>>elementos;
        //cout<<origen<<"_:_"<<elementos<<"\n";
        vector<int> datos(elementos);
        for(int i =0;i<elementos;i++)fin>>datos[i];
        //for(auto z:datos)cout<<z<<",";
        //cout<<"\n";
        for(int i =0;i<elementos;i++){
            if(datos[i]<=cantidadTokens || datos[i]==traductor["3ps"] || datos[i]==traductor["1d"])continue;
            int j = i+1;
            for(;j<elementos;j++){
                if(datos[j]>cantidadTokens && datos[j]!=traductor["3ps"] && datos[j]!=traductor["1d"]){
                    for(int z:primeros[datos[j]]){
                        if(z==traductor["3ps"])continue;
                        siguientes[datos[i]].insert(z);
                    }
                    if(!primeros[datos[j]].count(traductor["3ps"]))break;
                }else{
                    if(datos[j]==traductor["3ps"]){
                        j++;
                        break;
                    }
                    siguientes[datos[i]].insert(datos[j]);
                    break;
                }
            }
            if(j>=elementos){
                mapa[datos[i]].push_back({origen,0,0});
            }
        }
    }
    siguientes[cantidadTokens+1].insert(traductor["3ps"]);
    /*for(int i =1;i<extras;i++){
        cout<<i<<"___\n";
        for(auto z: siguientes[i])cout<<z<<",";
        cout<<"\n";
    }*/
    componentes = 0;
    while(!pila.empty())pila.pop();
    for(int i = 1;i < extras;i++){
        //cout<<i<<"\n";
        tarjan(i,mapa,infoNodos,vis,visitas,dag,pila,componentes,cantidadTokens,traductor["3ps"]);
    }
    listo.clear();

    primerosdag.clear();
    vector<set<int> >segundosdag(componentes+2);
    for(int i =1;i<=componentes;i++){
        for(int z:siguientes[i])segundosdag[dag[i]].insert(z);
    }

    dagueado.resize(componentes+2);
    vis.clear();
    vis.resize(componentes+2);
    for(int i =1;i<extras;i++){
        for(auto z: mapa[i]){
            if(dag[i]!=dag[z.destino]){
                if(infoNodos[i].cuentas[z.grupo]>=z.prioridad && !listo.count({dag[i],dag[z.destino]})){
                    dagueado[dag[i]].push_back(dag[z.destino]);
                    listo.insert({dag[i],dag[z.destino]});
                }
            }
        }
    }
    for(int i=1;i<=componentes;i++){
        buscasegundo(i,segundosdag,dagueado,vis,cantidadTokens);
    }

    tradag.clear();
    tradag.resize(componentes+2);
    for(int i=1;i<extras;i++){
        tradag[dag[i]].push_back(i);
    }

    for(int i=1;i<=componentes;i++){
        for(int z:tradag[i]){
            for(int zi: segundosdag[i])
                siguientes[z].insert(zi);
        }
    }
    fin.close();
    return true;
}

void guarda_registro(vector<vector<int> > &lasGramaticas,int identificador,int correctoID,int vacio,vector<vector<int> > &cualesProducciones, vector<int> &varOriginal){
    ifstream fin;
    fin.open("gramTraduc");
    int origen,cantidad,v;
    while(fin>>origen){
        varOriginal.push_back(origen);
        cualesProducciones[origen].push_back(lasGramaticas.size());
        lasGramaticas.push_back({});
        fin>>cantidad;
        bool primero = (cantidad==1);
        while(cantidad--){
            fin>>v;
            if(v==identificador)v=correctoID;
            if(v==vacio)v=0;
            lasGramaticas[lasGramaticas.size()-1].push_back(v);
        }
        //if(primero && lasGramaticas[lasGramaticas.size()-1][0]==0)lasGramaticas.pop_back();
    }
}
#endif