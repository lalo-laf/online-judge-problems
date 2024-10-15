#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <chrono>
using namespace std;

int cantDigitos(int a) {
    if (a == 0) return 1;
    int contador = 0;
    while (a != 0) {
        a = a/10;
        contador++;
    }
    return contador;
}

int distancia(int a, int b) {
    int res = abs(a-b);
    if (res > 5) {res = 10-res;}
    return res;
}

int rolls(int* a, int* b) {     //RECIBE 2 ARRAY(keys) Y DEVUELVE EL MINROLL
    int res = 0;
    for (int i = 0; i < 4; ++i) {
        res = res + distancia(a[i], b[i]);
    }
    return res;
}

void unir(vector<int>& nodosDelGrupoDeU, vector<int>& nodosDelGrupoDeV, int* grupoDeNodo){
    int grupoDeU = grupoDeNodo[nodosDelGrupoDeU[0]];
    for (int i = 0; i < nodosDelGrupoDeV.size(); ++i) {
        grupoDeNodo[nodosDelGrupoDeV[i]] = grupoDeU;
        nodosDelGrupoDeU.push_back(nodosDelGrupoDeV[i]);
    }
    vector<int>().swap(nodosDelGrupoDeV);
}

int main() {
    int testCases, cantKeys, key;
    cin >> testCases;
    auto start = chrono::high_resolution_clock::now();  //para testear tiempo de ejecución

    for (int t = 0; t < testCases; ++t) {
        bool tiene0000 = false;
        int menorDistanciaA0000 = numeric_limits<int>::max();   //"infinito"
        cin >> cantKeys;

        //DECLARO LA MATRIZ DE CLAVES CON CEROS, SIZE KEYS*4
        int claves[cantKeys][4];
        for (int i = 0; i < cantKeys; ++i) {
            for (int j = 0; j < 4; ++j) {
                claves[i][j] = 0;
            }
        }

        //INICIALIZO LA MATRIZ
        for (int j = 0; j < cantKeys; ++j) {
            cin >> key;
            if (key == 0) tiene0000 = true;
            if (cantDigitos(key) == 4) {
                claves[j][3] = key %10;
                claves[j][2] = key/10 %10;
                claves[j][1] = key/100 %10;
                claves[j][0] = key/1000 %10;
            }
            if (cantDigitos(key) == 3) {
                claves[j][3] = key %10;
                claves[j][2] = key/10 %10;
                claves[j][1] = key/100 %10;
            }
            if (cantDigitos(key) == 2) {
                claves[j][3] = key %10;
                claves[j][2] = key/10 %10;
            }
            if (cantDigitos(key) == 1) {
                claves[j][3] = key %10;
            }
        }

        //DECLARO EL GRAFO (MATRIZ DE ADYACENCIA, SIZE KEYS*KEYS) (no es necesario)
        //int grafo[cantKeys][cantKeys];

        //INICIALIZO EL GRAFO
        //for (int i = 0; i < cantKeys; ++i) {
        //    for (int j = 0; j < cantKeys; ++j) {
        //        grafo[i][j] = rolls(claves[i],claves[j]);
        //    }
        //}

        //DECLARO ARRAY grupoDeNodo
        int grupoDeNodo[cantKeys];

        //DECLARO ARRAY DE VECTORES nodosDeGrupo
        vector<int> nodosDeGrupo[cantKeys];

        //INICIALIZO grupoDeNodo Y nodosDeGrupo. Empiezo con 1 grupo para cada nodo.
        for (int i = 0; i < cantKeys; ++i) {
            grupoDeNodo[i] = i;
            nodosDeGrupo[i].push_back(i);
        }

        //DECLARO VECTOR DE ARISTAS. 1ra componente=peso, 2da y 3ra componentes=nodos
        vector<tuple<int,int,int>> aristas;

        //INICIALIZO VECTOR DE ARISTAS
        tuple<int,int,int> temporal;
        for (int i = 0; i < cantKeys; ++i) {
            for (int j = i+1; j < cantKeys; ++j) {
                temporal = make_tuple(rolls(claves[i],claves[j]),i,j);
                aristas.push_back(temporal);
            }
        }
        sort(aristas.begin(), aristas.end());

        //PRINT ARISTAS
        //for (int i = 0; i < aristas.size(); ++i) {
        //    cout << get<0>(aristas[i]) << ", ";
        //    cout << get<1>(aristas[i]) << ", ";
        //    cout << get<2>(aristas[i]) << endl;
        //}

        //PRINT ESTADO
        //for (int i = 0; i < cantKeys; ++i) {
        //    cout << "Grupo" << i << "=" << grupoDeNodo[i] << ", ";
        //    if (!nodosDeGrupo[i].empty()) {
        //        cout << "nodos grupo " << i << ": ";
        //        for (int j = 0; j < nodosDeGrupo[i].size(); ++j) {
        //            cout << nodosDeGrupo[i][j] << ",";
        //        }
        //    }
        //    cout << endl;
        //}

        ///////////////////////// ARRANCO ALGORITMO KRUSKAL /////////////////////////
        int u, v, peso;
        int suma = 0;
        for (int i = 0; i < aristas.size(); ++i) {
            peso = get<0>(aristas[i]);
            u = get<1>(aristas[i]);
            v = get<2>(aristas[i]);
            if (grupoDeNodo[u] != grupoDeNodo[v]) {
                suma = suma + peso;
                unir(nodosDeGrupo[grupoDeNodo[u]], nodosDeGrupo[grupoDeNodo[v]], grupoDeNodo);
            }
            //PRINT SUMA
            //cout << "Suma" << ": " << suma << endl;

            //PRINT ESTADO
            //for (int i = 0; i < cantKeys; ++i) {
            //    cout << "Grupo" << i << "=" << grupoDeNodo[i] << ", ";
            //    if (!nodosDeGrupo[i].empty()) {
            //        cout << "nodos grupo " << i << ": ";
            //        for (int j = 0; j < nodosDeGrupo[i].size(); ++j) {
            //            cout << nodosDeGrupo[i][j] << ",";
            //        }
            //    }
            //    cout << endl;
            //}
        }

        //Finalizo sumando la menor arista al 0000, si corresponde:
        if (!tiene0000) {
            int nodoCero[4] = {0,0,0,0};
            int dist = 0;
            for (int i = 0; i < cantKeys; ++i) {
                dist = rolls(nodoCero, claves[i]);
                if (dist != 0 && dist < menorDistanciaA0000) menorDistanciaA0000 = dist;
            }
            suma = suma + menorDistanciaA0000;
        }
        cout << suma << endl;

        //PRINT ESTADO
        //for (int i = 0; i < cantKeys; ++i) {
        //    cout << "Grupo" << i << "=" << grupoDeNodo[i] << ", ";
        //    if (!nodosDeGrupo[i].empty()) {
        //        cout << "nodos grupo " << i << ": ";
        //        for (int j = 0; j < nodosDeGrupo[i].size(); ++j) {
        //            cout << nodosDeGrupo[i][j] << ",";
        //        }
        //    }
        //    cout << endl;
        //}

        //PRINT grupoDeNodo
        //for (int i = 0; i < cantKeys; ++i) {
        //    cout << "Grupo" << i << "=" << grupoDeNodo[i] << ", ";
        //}

        //PRINT nodosDeGrupo
        //for (int i = 0; i < cantKeys; ++i) {
        //    if (!nodosDeGrupo[i].empty()) {
        //        cout << "Nodos grupo " << i << ": ";
        //        for (int j = 0; j < nodosDeGrupo[i].size(); ++j) {
        //            cout << nodosDeGrupo[i][j] << ",";
        //        }
        //    }
        //}

        //PRINT ARISTAS
        //cout << "ARISTAS: " << endl;
        //for (int i = 0; i < aristas.size(); ++i) {
        //    cout << get<0>(aristas[i]) << ", ";
        //    cout << get<1>(aristas[i]) << ", ";
        //    cout << get<2>(aristas[i]) << endl;
        //}

        //PRINT CLAVES
        //cout << "CLAVES: " << endl;
        //for (int i = 0; i < cantKeys; ++i) {
        //    for (int j = 0; j < 4; ++j) {
        //        cout << claves[i][j] << " ";
        //    }
        //    cout << endl;
        //}

        //PRINT GRAFO
        //cout << "GRAFO: " << endl;
        //for (int i = 0; i < cantKeys; ++i) {
        //    for (int j = 0; j < cantKeys; ++j) {
        //        cout << grafo[i][j] << " ";
        //    }
        //    cout << endl;
        //}

    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    //cout << duration.count();
    return 0;
}
