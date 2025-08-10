#include<iostream>
#include <regex>
using namespace std;
bool validarNombre(string nombre){
    if (nombre.empty()) {
        return false;
    }
    regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ]+( [A-Za-zÁÉÍÓÚáéíóúÑñ]+)*$");//khejesto, explayen el regex
    return regex_match(nombre, patron);
}
bool bisiesto(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool validarFecha(int dia, int mes, int anio) {
    if (anio < 1910 || anio > 2025) { 
        cout << "Error: Anio fuera de rango." << endl;
        return false;
    }
    if (mes < 1 || mes > 12) {
        cout << "Error: Mes fuera de rango." << endl;
        return false;
    }
    if (dia < 1 || dia > 31) {
        cout << "Error: Dia fuera de rango." << endl;
        return false;
    }
    if (mes == 2) {
        if (bisiesto(anio)){
            if (dia > 29) {
                cout << "Error: Febrero tiene 29 dias en un anio bisiesto." << std::endl;
                return false;
            }
        } else {
            if (dia > 28) {
                cout << "Error: Febrero tiene 28 dias en un anio no bisiesto." << std::endl;
                return false;
            }
        }
    }
    else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
        if (dia > 31) {
            cout << "Error: El mes tiene 31 dias." << endl;
            return false;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) {
            cout << "Error: El mes tiene 30 dias." << endl;
            return false;
        }
    }
    return true;
}
int main() {
    int dia, mes, anio;

    cout << "Ingrese la fecha de nacimiento (dd mm aaaa): "<<endl;
    cin>>dia;
    cin>>mes;
    cin>>anio;

    if (validarFecha(dia, mes, anio)) {
        cout << "Fecha de nacimiento valida." << std::endl;
    } else {
        cout << "Fecha de nacimiento invalida." << std::endl;
    }

    return 0;
}
