#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();
int testCases;
int cantNodos;

int main() {
    cin >> testCases;
    for (int t = 0; t < testCases; ++t) {
        cin >> cantNodos;
        vector<vector<int>> pesos(cantNodos, vector<int>(cantNodos,INF));
        vector<int> orden(cantNodos);
        long long int sumatoria = 0;
        long long int sumaActual = 0;

        //RECIBO LOS PESOS ENTRE TORRES
        for (int i = 0; i < cantNodos; ++i) {
            for (int j = 0; j < cantNodos; ++j) {
                cin >> pesos[i][j];
            }
        }
        //RECIBO EL ORDEN DE DESTRUCCIÓN
        for (int i = cantNodos-1; i >= 0; --i) {
            cin >> orden[i];
        }

        //ARRANCO FLOYD-WARSHALL
        for (int k = 0; k < cantNodos; ++k) {
            //CALCULO DISTANCIAS INCLUYENDO AL NUEVO NODO
            for (int i = 0; i < cantNodos; ++i) {
                for (int j = 0; j < cantNodos; ++j) {
                    if (pesos[i][j] > pesos[i][orden[k]] + pesos[orden[k]][j]) {
                        pesos[i][j] = pesos[i][orden[k]] + pesos[orden[k]][j];
                    }
                }
            }
            //CALCULO LA SUMA DE LAS DISTANCIAS TODOS A TODOS
            sumaActual = 0;
            for (int i = 0; i <= k; ++i) {
                for (int j = 0; j <= k; ++j) {
                    if (i != j) sumaActual = sumaActual + pesos[orden[i]][orden[j]];
                }
            }
            sumatoria = sumatoria + sumaActual;
        }
        //DOY RESULTADO
        cout << sumatoria << endl;


        //PRINT PESOS
        //for (int i = 0; i < cantNodos; ++i) {
        //    for (int j = 0; j < cantNodos; ++j) {
        //        cout << pesos[i][j] << ",";
        //    }   cout << endl;
        //}       cout << endl;
        //PRINT ORDEN
        //for (int i = 0; i < cantNodos; ++i) {
        //    cout << orden[i] << ",";
        //}   cout << endl << endl;
    }

    return 0;
}
