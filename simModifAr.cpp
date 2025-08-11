#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
using namespace std;

const string separador = "_________________________________________";
struct paciente
{
    string cedula;
    string nombre;
    string apellido;
    string especialidad;
    string telefono;
    string direccion;
    int dia1, mes1, anio1, edad;
    int dia2, mes2, anio2;
    char sexo;
};
struct registro
{
    string especialidad;
    string doctor;
    int dia, mes, anio;
};
string nombreArchivo(const paciente &p) // sub - funcion especifica para nombrar un archivo con la cedula
{
    string nombreArc = p.cedula + ".txt";
    return nombreArc;
}

int moduloDiez(const paciente &p) // funcion necesaria para validar los numeros de cedula

{
    int suma = 0;
    for (int i = 0; i < 9; i++)
    {
        int digito = p.cedula[i] - '0'; // en la tabla ASCII, los numeros del 0 al 9 son consecutivos, al restar el '0', restamos el valor ASCII de 0 al valor ASCII del numero en cuestion, obteniendo el valor entero
        if (i % 2 == 0)
        {
            digito *= 2;
            if (digito > 9)
            {
                digito -= 9;
            }
        }
        suma += digito;
    }
    int digitoVerificador = 10 - (suma % 10);
    if (digitoVerificador == 10)
    {
        digitoVerificador = 0;
    }
    return digitoVerificador;
} // a libreria

void pedirCedula(paciente &p) // funcion principal encargada de, ademas de pedir cedula, valida su tamaño, caracteres, etc
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
        int tercerDigito = p.cedula[2] - '0';
        if (tercerDigito > 6)
        {
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
        if (moduloDiez(p) != (p.cedula[9] - '0'))
        {
            cout << "La cedula ingresada no es valida. Por favor ingrese una cedula valida." << endl;
            cedulaValida = false;
            continue;
        }
    } while (cedulaValida == false);
} // a libreria

int contarRegistro(const paciente &p)
{
    ifstream archivo(nombreArchivo(p));
    int contador = 0;
    if (!archivo)
    {
        cout << "Error al abrir el archivo." << endl;
        return 0;
    }
    else
    {
        string linea;
        while (getline(archivo, linea))
        {
            if (linea == separador)
            {
                contador++;
            }
        }
    }
    cout << contador << endl;
    archivo.close();
    return contador;
}

registro *cargarRegistro(const paciente &p, int &numeReg)
{
    numeReg = contarRegistro(p);
    if (numeReg == 0)
    {
        cout << "No existen registros para este paciente." << endl;
        return nullptr;
    }
    registro *infoPaciente = new registro[numeReg];
    ifstream archivo(nombreArchivo(p));
    if (!archivo)
    {
        delete[] infoPaciente;
        numeReg = 0;
        return nullptr;
    }
    string linea;
    int i = 0;
    while (getline(archivo, linea) && i < numeReg)
    {
        if (linea == separador)
        {
            
        }
    }
}

int main()
{
    paciente p;
    int numeroRegistros;
    pedirCedula(p);
    cout << "El nombre del archivo es: " << nombreArchivo(p) << endl;
    contarRegistro(p);

    return 0;
}