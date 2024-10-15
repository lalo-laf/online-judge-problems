#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> arista;
const int INF = numeric_limits<int>::max();

int pisos, n, k;

//ESTRUCTURAS DE PRUEBA, IGNORAR
vector<int> a0 = {0,1,5,6,9};
vector<int> a1 = {0,2,4};
vector<int> a2 = {5,6,8,9};
int t0 = 1;
int t1 = 2;
int t2 = 3;
vector<int> a3 = {0,1,3,5,7,9,11,13,15,20,99};
vector<int> a4 = {4,13,15,19,20,25,30};
int t3 = 10;
int t4 = 5;
vector<int> a5 = {0, 5, 10, 12, 14, 20, 25, 30};
vector<int> a6 = {2, 4, 6, 8, 10, 12, 14, 22, 25, 28, 29};
int t5 = 10;
int t6 = 1;
vector<int> a7 = {0,10,30,40};
vector<int> a8 = {0,20,30};
vector<int> a9 = {0,20,50};
int t7 = 10;
int t8 = 50;
int t9 = 100;
vector<int> a10 = {0,2,4,6,8,10};
int t10 = 2;

void dijkstra(const vector<vector<vector<arista>>>& adyacencias) {
    vector<vector<int>> dist(n+1, vector<int>(pisos,INF));      //diccionario de distancias
    priority_queue<arista, vector<arista>, greater<arista>> pq; //sale el minimo con greater<>, el maximo con less<>
    pii inicial = {n,0};

    dist[inicial.first][inicial.second] = 0;
    pq.push({0,{n,0}});

    while(!pq.empty()) {
        //TOMO EL MENOR NODO
        pii nodo = pq.top().second;
        int peso = pq.top().first;
        pq.pop();

        //PARA EL PROBLEMA DE ENCOLAR VARIAS VECES EL MISMO VERTICE:
        if (peso > dist[nodo.first][nodo.second]) continue;

        //PARA CADA UNO DE LOS ADYACENTES
        for (int i = 0; i < adyacencias[nodo.first][nodo.second].size(); ++i) {
            pii adyacente = adyacencias[nodo.first][nodo.second][i].second;
            int pesoArista = adyacencias[nodo.first][nodo.second][i].first;

            //RELAJO LA ARISTA SI CORRESPONDE
            if(dist[nodo.first][nodo.second] + pesoArista < dist[adyacente.first][adyacente.second]) {
                dist[adyacente.first][adyacente.second] = dist[nodo.first][nodo.second] + pesoArista;
                //LOS RELAJADOS PASAN A SER MENORES A INFINITO, ASI QUE PASAN A SER CONSIDERADOS EN LA QUEUE:
                pq.push({dist[adyacente.first][adyacente.second],{adyacente.first,adyacente.second}});
            }
        }
    }

    //IMPRIMIR TODAS LAS DISTANCIAS:
    //cout << "DISTANCIAS:" << endl;
    //for (int i = 0; i < n+1; ++i) {
    //    for (int j = 0; j < pisos; ++j) {
    //        cout << dist[i][j] << ", ";
    //    }
    //    cout << endl;
    //}

    //IMPRIMIR DISTANCIAS AL PISO K:
    //cout << "DISTANCIAS:" << endl;
    //for (int i = 0; i < n+1; ++i) {
    //    cout << dist[i][k] << ", ";
    //} cout << endl;

    //IMPRIMIR RESPUESTA:
    int res = INF;
    for (int i = 0; i < n+1; ++i) {
        if (dist[i][k] < res) {
            res = dist[i][k];
        }
    }
    if (res < INF) {
        cout << res << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

}

int main() {
    pisos = 101;

    vector<vector<int>> elevadores;
    vector<int> tiempos;

    /////////////////////////////TOMO LOS DATOS//////////////////////////////////////////////////////
    string renglon;
    while(getline(cin, renglon)) {
        //TOMO N, K
        stringstream ss1(renglon);
        ss1 >> n >> k;
        elevadores = vector<vector<int>>(n);
        tiempos = vector<int>(n);

        //TOMO LOS TIEMPOS
        getline(cin, renglon);
        stringstream ss2(renglon);
        for (int i = 0; i < n; ++i) {
            int tiempo = 0;
            ss2 >> tiempo;
            tiempos[i] = tiempo;
        }

        //TOMO LOS PISOS
        for (int i = 0; i < n; ++i) {
            getline(cin, renglon);
            stringstream ss3(renglon);
            int f;
            while (ss3 >> f) {
                elevadores[i].push_back(f);
            }
        }

        ////////////INICIALIZO GRAFO DEL TEST CASE////////////
        vector<vector<vector<arista>>> adyacencias(n+1, vector<vector<arista>>(pisos)); //matriz de vectores de aristas
        //INICIALIZO LAS ADYACENCIAS
        for (int i = 0; i < elevadores.size(); ++i) {
            for (int j = 0; j < elevadores[i].size()-1; ++j) {
                int actual = elevadores[i][j];
                int siguiente = elevadores[i][j+1];
                int peso = 5;
                peso = abs(siguiente-actual) * tiempos[i];
                arista ida = {peso,{i,siguiente}};
                arista vuelta = {peso,{i,actual}};
                adyacencias[i][actual].push_back(ida);                  //ARISTAS PARA SUBIR DE PISO EN ESE ELEVADOR
                adyacencias[i][siguiente].push_back(vuelta);            //ARISTAS PARA BAJAR DE PISO EN ESE ELEVADOR

                adyacencias[i][actual].push_back({60,{n,actual}});      //ARISTAS PARA BAJAR DEL ELEVADOR
                adyacencias[n][actual].push_back({0,{i,actual}});       //ARISTAS PARA SUBIR AL ELEVADOR
            }
            int ultimoPiso = elevadores[i][elevadores[i].size()-1];
            adyacencias[i][ultimoPiso].push_back({60,{n,ultimoPiso}});  //ULTIMA ARISTA PARA BAJAR DEL ELEVADOR
            adyacencias[n][ultimoPiso].push_back({0,{i,ultimoPiso}});   //ULTIMA ARISTA PARA SUBIR AL ELEVADOR
        }
        ///////////////////////////////////////////////////////

        //RESUELVO TESTCASE CON DIJKSTRA
        dijkstra(adyacencias);
    }


    //PARA DEBUGGEAR:

    //PRINT NODOS
    //for (int i = 0; i < adyacencias.size(); ++i) {
    //    for (int j = 0; j < adyacencias[i].size(); ++j) {
    //        cout << adyacencias[i][j].size() << " ";
    //    }
    //    cout << endl;
    //}

    //PRINT ARISTAS
    //for (int e = 0; e < adyacencias.size(); ++e) {
    //    for (int i = 0; i < adyacencias[e].size(); ++i) {
    //        for (int j = 0; j < adyacencias[e][i].size(); ++j) {
    //            cout << adyacencias[e][i][j].first << "," << adyacencias[e][i][j].second.first << "," << adyacencias[e][i][j].second.second << " | ";
    //        }
    //    }
    //    cout << endl;
    //}

    //PRINT ELEVADORES
    //for (int i = 0; i < elevadores.size(); ++i) {
    //    for (int j = 0; j < elevadores[i].size(); ++j) {
    //        cout << elevadores[i][j] << " ";
    //    }
    //}

    return 0;
}
