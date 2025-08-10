#include <iostream>
#include <string>
using namespace std;
void split(string str, char pattern,string results[]) {
    
    int posInit = 0;
    int posFound = 0;
    string splitted;
    int indice=0;
    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results[indice]=splitted;
        indice++;
    }
}
