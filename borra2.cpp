#include <iostream>
#include <fstream>
using namespace std;

struct paciente {
    string cedula;
    string nombre;
    string apellido;
    int dia = 0, mes = 0, anio = 0, edad = 0;
    char sexo = ' ';
};

void imprimirArchivo(paciente p) {
    ofstream archivo("pacientes2.txt", ios::app); // Modo agregar
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    archivo << "Fecha de atencion: " << p.dia << "/" << p.mes << "/" << p.anio << endl;
    archivo << "Cedula: " << p.cedula << endl;
    archivo << "Nombre: " << p.nombre << endl;
    archivo << "Apellido: " << p.apellido << endl;
    archivo << "Edad: " << p.edad << endl;
    archivo << "Sexo: " << p.sexo << endl;
    archivo << "-------------------------------" << endl;

    archivo.close();
}

int main() {
    paciente pac; // Sin pedir datos

    imprimirArchivo(pac); // Escribe los campos vacíos

    cout << "Archivo pacientes.txt generado con campos vacíos." << endl;
    return 0;
}
