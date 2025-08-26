#include "getInfo.hpp"

using namespace std;

//une fonction qui retourne la valeur saisie sous forme de chaîne de caractères.
string getString(string varNom){
    string s;
    cout << varNom << " : ";
    cin >> s;
    return s;
}

//une fonction qui retourne la valeur entière saisie par l'utilisateur.
int getInt(string varNom){
    int i;
    cout << varNom << " : ";
    cin >> i;
    return i;
}