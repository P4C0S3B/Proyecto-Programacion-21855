#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
struct paciente
{
    string cedula;
    string nombre;
    string apellido;
    int dia1, mes1, anio1, edad;
    int dia2, mes2, anio2;
    char sexo;
};
string nombreArchivo(const paciente &p)
{
    string nombreArc = p.cedula + ".txt";
    return nombreArc;
} // a libereria
int moduloDiez(paciente p){
    int suma=0;
    for(int i=0; i<9;i++){
        int digito = p.cedula[i]-'0';// en la tabla ASCII, los numeros del 0 al 9 son consecutivos, al restar el '0', restamos el valor ASCII de 0 al valor ASCII del numero en cuestion, obteniendo el valor entero
        if(i%2==0){
            digito*=2;
            if(digito > 9){
                digito -= 9;
            }
        }
        suma += digito;
    }
    int digitoVerificador = 10 - (suma % 10);
    if(digitoVerificador == 10){
        digitoVerificador = 0;
    }
    return digitoVerificador;
} // a libreria

void pedirCedula(paciente &p)
{
    bool cedulaValida;
    cin.ignore();
    do
    {
        cedulaValida = true;
        cout << "Ingrese la cedula del paciente: ";
        getline(cin, p.cedula);

        if (p.cedula.empty())
        {
            cout << "El campo de cédula no puede estar vacío. Por favor ingrese una cedula válida." << endl;
            cedulaValida = false;
            continue;
        }

        if (p.cedula.length() != 10)
        {
            cout << "Numero de caracteres no valido. Por favor ingrese una cedula valida." << endl;
            cedulaValida = false;
            continue;
        }
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit(p.cedula[i]))
            {
                cout << "La cedula solo puede contener caracteres numericos. Por favor ingrese una cedula valida." << endl;
                cedulaValida = false;
                break;
            }
        }
        int tercerDigito = p.cedula[2]-'0';
        if (tercerDigito > 6 ){
            cout << "Cedula no valida (tercer digito invalido). Por favor ingrese una cedula valida." << endl;
            cedulaValida = false;
            continue;
        }
        if (cedulaValida)
        {
            int provincia = stoi(p.cedula.substr(0, 2));
            if (provincia < 1 || (provincia > 24 && provincia != 30))
            {
                cout << "La cedula ingresada no es valida. Por favor ingrese una cedula valida." << endl;
                cedulaValida = false;
                continue;
            }
        }
        if(moduloDiez(p)!= (p.cedula[9]- '0')){
            cout << "La cedula ingresada no es valida. Por favor ingrese una cedula valida." << endl;
            cedulaValida = false;
            continue;
        }
    } while (cedulaValida == false);
} // a libreria

void crearArchivoPaciente(paciente &p)
{
    cin.ignore();
    ofstream archivo(nombreArchivo(p), ios::out);
    if (!archivo)
    {
        cout << "Error al crear el archivo: " << nombreArchivo << endl;
        return;
    }
    if(nombreArchivo){
        cout << "El archivo ya existe." << endl;
    }
    cout << "El archivo para el paciente con cedula " << p.cedula << " ha sido creado exitosamente." << endl;
}
void registrarPaciente(paciente &nuevoPaciente)
{

    cout << "Ingrese la fecha de atencion (dd mm aaaa): " << endl;
    ;
    cout << "Dia: ";
    cin >> nuevoPaciente.dia1;
    cout << "Mes: ";
    cin >> nuevoPaciente.mes1;
    cout << "Anio: ";
    cin >> nuevoPaciente.anio1;
    cout << "Ingrese el nombre del paciente: ";
    cin >> nuevoPaciente.nombre;
    cout << "Ingrese el apellido del paciente: ";
    cin >> nuevoPaciente.apellido;
    cout << "Ingrese la fecha de nacimiento del paciente (dd mm aaaa): " << endl;
    ;
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

void imprimirArchivo(paciente &p)
{
    ofstream archivo(nombreArchivo(p), ios::app);
    if (!archivo)
    {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    archivo << "Fecha de atención: " << p.dia1 << "/" << p.mes1 << "/" << p.anio1 << endl;
    archivo << "Cédula: " << p.cedula << endl;
    archivo << "Nombre: " << p.nombre << '\t' << "Apellido:" << p.apellido << endl;
    archivo << "Fecha de nacimiento: " << p.dia2 << "/" << p.mes2 << "/" << p.anio2 << endl;
    archivo.close();
}
int main()
{
    paciente pac;
    int op;
    cout << "==========================" << endl;
    cout << "REGISTRO DE CITAS MEDICAS" << endl;
    cout << "==========================" << endl;
    cout << "Ingrese una opcion" << endl;
    cout << "1.- Registro de un paciente nuevo." << endl;
    cout << "2.- Consulta de informacion del paciente (Por numero de cedula)" << endl;
    cout << "3.- Agregar informacion del paciente" << endl;
    cout << "4.- Salir" << endl;
    do
    {
        cout << "Por favor, ingrese una de las opciones mostradas (1 - 4)" << endl;
        cin >> op;
    } while (op < 1 || op > 4);
    switch (op)
    {
    case 1:
        pedirCedula(pac);
        crearArchivoPaciente(pac);
        registrarPaciente(pac);
        imprimirArchivo(pac);
        break;

    default:
        break;
    }
    return 0;
}