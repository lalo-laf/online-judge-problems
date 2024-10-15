#include <iostream>
#include <vector>
using namespace std;

//vector<vector<int>> memo;     //memoización para top-down
vector<vector<int>> mapa;
int cantArboles, altura, salto;

////PODA PARA TOP-DOWN: si en los proximos (2*f)-1 alturas no hay bellota, descarto este hijo (saltar es mejor o igual)
//bool hayBellota(int t, int h) {
//    for (int i = 0; i < (2*salto)-1; ++i) {
//        if (mapa[t][h-1-i] != 0) return true;
//    }
//    return false;
//}

////PODA PARA TOP-DOWN: SI SALTO ME PIERDO LOS PROXIMOS 2*F-1
////O SEA QUIERO SALTAR SI EN LOS PROXIMOS 2*F-1 HAY MENOS QUE EN LA ALTURA H-F DE OTRO ARBOL
////devuelve true si en los proximos 2f-1 hay menos que en la altura h-f de otro arbol
//bool convieneSaltar(int t, int h) {
//    if (h-(2*salto)+1 <= 0) return false;   //caso los proximos 2f-1 llegan al suelo
//    int proximas = 0;
//    for (int i = 0; i < (2*salto)-1; ++i) {
//        proximas += mapa[t][h-1-i];
//    }
//    //recorro los otros arboles para ver si alguno tiene mas bellotas en h-f
//    for (int arbol = 0; arbol < cantArboles; ++arbol) {
//        if (arbol != t && mapa[arbol][h-salto] >= proximas) return true;
//    }
//    return false;
//}

////VERSIÓN TOP-DOWN:
//int f(int t, int h) {
//    if (h <= 0) return 0;                   //caso no hay hijos
//    if (h-salto < 0) {                      //caso tiene 1 solo hijo
//        if (memo[t][h-1] == -1) {
//            memo[t][h-1] = f(t, h-1);
//        }
//        return memo[t][h-1] + mapa[t][h];
//    }
//
//    int res = 0;
//    //if (!convieneSaltar(t,h)) {
//        if (memo[t][h-1] == -1) {
//            memo[t][h-1] = f(t, h-1);
//        }
//        res = memo[t][h-1] + mapa[t][h];
//    //}
//
//    for (int arbol = 0; arbol < cantArboles; ++arbol) {
//        if (arbol != t) {
//            if (memo[arbol][h-salto] == -1) {
//                memo[arbol][h-salto] = f(arbol, h-salto);
//            }
//            res = max(res, memo[arbol][h-salto] + mapa[t][h]);
//        }
//    }
//    return res;
//}

////VERSIÓN BOTTOM-UP:
void g() {
    int f = min(salto, altura);
    //for (int height = 1; height <= salto; ++height) {...
    for (int height = 1; height <= f; ++height) {               //lleno las alturas de 0 a f:
        for (int arbol = 0; arbol < cantArboles; ++arbol) {
            mapa[arbol][height] += mapa[arbol][height-1];
        }
    }

    for (int height = salto+1; height <= altura; ++height) {    //calculo el max de los h-f:
        int maximo = mapa[0][height-salto];
        for (int arbol = 1; arbol < cantArboles; ++arbol) {
            maximo = max(maximo, mapa[arbol][height-salto]);
        }

        for (int arbol = 0; arbol < cantArboles; ++arbol) {     //observo si conviene el max de los h-f, o el h-1
            mapa[arbol][height] += max(maximo, mapa[arbol][height-1]);
        }
    }
}

int main() {
    int testCases, cantAcorns, alturaAcorn, res;

    cin >> testCases;
    for (int testCase = 0; testCase < testCases; ++testCase) {
        cin >> cantArboles;
        cin >> altura;
        cin >> salto;
        mapa = vector<vector<int>> (cantArboles, vector<int>(altura+1, 0));
        //memo = vector<vector<int>> (cantArboles, vector<int>(altura+1, -1));  //memo para top-down
        //en memo[t][h] tengo la cantidad de acorns al partir del arbol t y altura h

        for (int arbol = 0; arbol < cantArboles; ++arbol) {
            cin >> cantAcorns;
            for (int acorn = 0; acorn < cantAcorns; ++acorn) {
                cin >> alturaAcorn;
                mapa[arbol][alturaAcorn] += 1;
            }
        }
        //a este punto ya tengo toda la información del testCase cargada en el mapa

        res = 0;
        ////VERSION TOP-DOWN:
        //for (int arbol = 0; arbol < cantArboles; ++arbol) {
        //    res = max(res, f(arbol,altura));
        //}
        ////VERSION BOTTOP-UP:
        g();
        for (int arbol = 0; arbol < cantArboles; ++arbol) {
            res = max(res,mapa[arbol][altura]);
        }

        cout << res << endl;
    }

    //IMPRIMIR  MAPA:
    //for (int i = 0; i < mapa.size(); ++i) {
    //    for (int j = 0; j < mapa[0].size(); ++j) {
    //        cout << mapa[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    return 0;
}
