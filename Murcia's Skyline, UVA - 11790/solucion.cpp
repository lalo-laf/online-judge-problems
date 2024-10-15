#include <iostream>
#include <vector>
using namespace std;
struct Building {
    int height;
    int width;
};

int increasing(vector<Building> &v) {
    vector<int> res(v.size(),0);

    for (int i = 0; i < v.size(); ++i) {
        //En cada posicion i de res, quiero poner la "mejor sublista que termina con el edif i", o "MSI".
        //Y también se que la MSI se construye a partir de agregarle el edificio I a una sublista que termina con un edificio J anterior a I.
        //Asique de todas las sublistas MSJ que terminan con un edificio J anterior a I, MSI = la mejor de las "MSJ ++ I".

        for (int j = 0; j < i; ++j) {                       //Recorro las MSJ
            if (v[j].height < v[i].height) {
                res[i] = max(res[i], res[j]);               //Actualizo la MSI con la mejor de las MSJ (siempre que haya compatibilidad de altura)
            }
        }
        res[i] += v[i].width;                               //Y agrego el edificio I
    }

    int max = res[0];
    for (int i = 1; i < res.size(); ++i) {
        max = max<res[i] ? res[i] : max;
    }
    return max;                                             //Devuelvo la mejor de las MSI
}

int decreasing(vector<Building> &v) {
    vector<int> res(v.size(),0);

    for (int i = 0; i < v.size(); ++i) {

        for (int j = 0; j < i; ++j) {
            if (v[j].height > v[i].height) {
                res[i] = max(res[i], res[j]);
            }
        }
        res[i] += v[i].width;
    }

    int max = res[0];
    for (int i = 1; i < res.size(); ++i) {
        max = max<res[i] ? res[i] : max;
    }
    return max;
}

void imprimir(int testCase, int i, int d) {
    if (i>=d) {
        //increasing primero
        cout << "Case " << testCase << ". Increasing (" << i << "). Decreasing (" << d << ")." << endl;
    } else {
        //decreasing primero
        cout << "Case " << testCase << ". Decreasing (" << d << "). Increasing (" << i << ")." << endl;
    }
}

int main() {
    int testCases;
    int numberOfBuildings;
    cin >> testCases;

    for (int i = 0; i < testCases; ++i) {
        cin >> numberOfBuildings;
        vector<Building> buildings (numberOfBuildings);
        int height;
        int width;

        for (int j = 0; j < numberOfBuildings; ++j) {
            cin >> height;
            buildings[j].height = height;
        }
        for (int j = 0; j < numberOfBuildings; ++j) {
            cin >> width;
            buildings[j].width = width;
        }
        //a este punto, ya tengo completo el vector de alturas y anchos.

        int increasingLength = increasing(buildings);
        int decreasingLength = decreasing(buildings);
        imprimir(i+1,increasingLength,decreasingLength);

        //for (int j = 0; j < buildings.size(); ++j) {
        //    cout << buildings[j].height << " " << buildings[j].width << endl;
        //}

    }

    return 0;
}
