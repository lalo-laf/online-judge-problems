#include <iostream>
using namespace std;

bool equivalentes(string a, string b) {
    if (a == b) return true;                //caso son iguales
    if (a.size() % 2 == 1) return false;    //caso son distintos y longitud impar
    
    int t = a.size()/2;                     //divido en 4 problemas
    string a1 = a.substr(0,t);
    string a2 = a.substr(t,t);
    string b1 = b.substr(0,t);
    string b2 = b.substr(t,t);
    return (equivalentes(a1,b2) && equivalentes(a2,b1)) || (equivalentes(a1,b1) && equivalentes(a2,b2));
}

int main() {
    string s1;
    string s2;
    cin >> s1;
    cin >> s2;

    //IMPRIMIR RESULTADO
    bool res = equivalentes(s1, s2);
    if (res) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
