#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
struct paciente{
    string cedula;
    string nombre;
    string apellido;
    int dia1, mes1, anio1, edad;
    int dia2, mes2, anio2;
    char sexo;
    
};
void crearArchivoPaciente(paciente &p){
    cin.ignore();
    do {
        cout << "Ingrese la cedula del paciente: ";
        getline(cin, p.cedula);
        if (p.cedula.empty()) {
            cout << "El campo de cédula no puede estar vacío. Por favor ingrese una cedula válida." << endl;
        }
    } while (p.cedula.empty());
    string nombreA = p.cedula + ".txt";
    ofstream archivo(nombreA, ios:: out); //ios::out crea el archivo en cuestion
    if (!archivo) {
        cout << "Error al crear el archivo: " << nombreA << endl;
        return;
    }
    cout<< "El archivo para el paciente con cedula " << p.cedula << " ha sido creado exitosamente."<< endl;
}
void registrarPaciente(paciente &nuevoPaciente) {
    cout << "Ingrese la fecha de atencion (dd mm aaaa): " << endl;;
    cout << "Dia: ";    cin >> nuevoPaciente.dia1;
    cout << "Mes: "; cin >> nuevoPaciente.mes1;
    cout << "Anio: "; cin >> nuevoPaciente.anio1;
    cout << "Ingrese el nombre del paciente: ";
    cin >> nuevoPaciente.nombre;
    cout << "Ingrese el apellido del paciente: ";
    cin >> nuevoPaciente.apellido;
    cout << "Ingrese la fecha de nacimiento del paciente (dd mm aaaa): " << endl;;
    cout << "Dia: ";
    cin >> nuevoPaciente.dia2;
    cout << "Mes: ";
    cin >> nuevoPaciente.mes2;
    cout << "Anioo: ";
    cin >> nuevoPaciente.anio2;
    cout << "Ingresa el sexo del paciente (M/F): ";
    cin >> nuevoPaciente.sexo;

    cout << "Paciente registrado con exito!" << endl;

}
void imprimirArchivo(paciente &p){
    string nombreA = p.cedula + ".txt";
    ofstream archivo(nombreA, ios:: app);
    if(!archivo){
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    archivo << "Fecha de atención: " << p.dia1 << "/" << p.mes1 << "/" << p.anio1 << endl;
    archivo << "Cedula: " << p.cedula << endl;
    archivo << "Nombre: " << p.nombre << '\t' << "Apellido:" << p.apellido << "\t" << "Cédula: " << p.cedula << endl;
    archivo << "Fecha de nacimiento: " << p.dia2 << "/" << p.mes2 << "/" << p.anio2 << endl;
    archivo.close();

}
int main(){
    paciente pac;
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
    switch (op)
    {
    case 1:
        crearArchivoPaciente(pac);
        registrarPaciente(pac);
        imprimirArchivo(pac);
        break;
    
    default:
        break;
    }
    return 0;
}