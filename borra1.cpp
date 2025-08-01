#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
struct paciente{
    string cedula;
    string nombre;
    string apellido;
    int dia, mes, anio, edad;
    char sexo;
    
};

int main(){
    int op;
    cout<<"=========================="<<endl;
    cout<<"REGISTRO DE CITAS MEDICAS"<<endl;
    cout<<"=========================="<<endl;
    cout<<"Ingrese una opcion"<<endl;
    cout<<"1.- Registro de un paciente nuevo."<<endl;
    cout<<"2.- Consulta de informacion del paciente (Por numero de cedula)"<<endl;
    cout<<"3.- Agregar informacion del paciente"<<endl;
    cout<<"4.- Salir"<<endl;
    do{
        cout<<"Por favor, ingrese una de las opciones mostradas (1 - 4)"<<endl;
        cin >>op;
    } while(op<1 || op>4);
    return 0;
}