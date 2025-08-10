#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
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
string especialidadLista[10] = {"Cardiologia", "Traumatologia", "Neurologia", "Medicina familiar",
                                "Endocrinologia", "Medicina General", "Urologia", "Nutricion",
                                "Ginecologia", "Pediatria"};
string nombreArchivo(const paciente &p) // sub - funcion especifica para nombrar un archivo con la cedula
{
    string nombreArc = p.cedula + ".txt";
    return nombreArc;
} // a libereria
////////////////////////////////////////////////////////////////////////////////////////////////////
int moduloDiez(paciente p) // funcion necesaria para validar los numeros de cedula
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
////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
bool crearArchivoPaciente(paciente &p) // funcion encargada de crear el archivo con el numero de cedula
{
    ifstream archivoE(nombreArchivo(p));
    if (archivoE)
    {
        cout << "El registro para este paciente ya existe." << endl;
        archivoE.close();
        return false;
    }
    ofstream archivo(nombreArchivo(p), ios::out);
    if (!archivo)
    {
        cout << "Error al crear el registro: " << nombreArchivo << endl;
        return false;
    }
    cout << "El registro para el paciente con cedula " << p.cedula << " ha sido creado exitosamente." << endl;
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void registrarPaciente(paciente &nuevoPaciente) // funcion encargada de registrar la infromacion fija del paciente, que no varia entre citas
{

    cout << "Ingrese la fecha de atencion (dd mm aaaa): " << endl;
    ;
    cout << "Dia: ";
    cin >> nuevoPaciente.dia1;
    cout << "Mes: ";
    cin >> nuevoPaciente.mes1;
    cout << "Anio: ";
    cin >> nuevoPaciente.anio1;
    cin.ignore();
    cout << "Ingrese el nombre del paciente: ";
    getline(cin, nuevoPaciente.nombre);
    cout << "Ingrese el apellido del paciente: ";
    getline(cin, nuevoPaciente.apellido);
    cin.ignore();
    cout << "Ingrese la fecha de nacimiento del paciente (dd mm aaaa): " << endl;
    cout << "Dia: ";
    cin >> nuevoPaciente.dia2;
    cout << "Mes: ";
    cin >> nuevoPaciente.mes2;
    cout << "Anio: ";
    cin >> nuevoPaciente.anio2;
    do
    {
        cout << "Ingresa el sexo del paciente (M/F): ";
        cin >> nuevoPaciente.sexo;
    } while (nuevoPaciente.sexo != 'M' && nuevoPaciente.sexo != 'F');

    cout << "Paciente registrado con exito!" << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool archivoExistente(paciente p)
{ // funcion encargada de buscar el archivo en funcion del numero de cedula
    string nombreAr = p.cedula + ".txt";
    ifstream archivo(nombreAr);
    return archivo.good();
    archivo.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
void busquedaFecha(paciente p, registro r)
{
    int dia, mes, anio, citas=0;
    registro registroFecha[citas];
    cout << "Ingrese la feccha que desea buscar: " << endl;
    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    ifstream archivo(nombreArchivo(p));
    
   if(!archivo){
        cout << "No se puede abrir el archivo." << endl;
        return;
   } else {
    string linea;
    string fechaBuscada = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    bool encontrado = false;
    while(getline(archivo, linea)){
        if(linea.find(fechaBuscada) != string::npos){
            encontrado=true;
            
        }
    }
   }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void busquedaEspecialidad(paciente pac)
{
    string especialidad;
    string nombreArc = nombreArchivo(pac) + ".txt";
    ifstream archivo(nombreArc);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int seleccionarEspecialidad()
{
    int opcion;
    do
    {
        cout << "Seleccione una especialidad: " << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << i + 1 << ".- " << especialidadLista[i] << endl;
        }
        cin >> opcion;
    } while (opcion < 1 || opcion > 10);
    return opcion;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void registroInfo(paciente &pac, registro &reg)
{
    if (!archivoExistente(pac))
    {
        cout << "No se encontro ningun registro con esta cedula." << endl;
    }
    else
    {
        cout << "Registro encontrado." << endl;
        cout << "Ingrese la fecha de la consulta: " << endl;
        cout << "Dia: ";
        cin >> reg.dia;
        cout << "Mes: ";
        cin >> reg.mes;
        cout << "Anio: ";
        cin >> reg.anio;
        cout << "Ingrese la especialidad de la cita: ";
        reg.especialidad = especialidadLista[seleccionarEspecialidad() - 1];
        cin.ignore();
        cout << "Ingrese el nombre del doctor a cargo de la cita: ";
        getline(cin, reg.doctor);
        ofstream archivo(nombreArchivo(pac), ios::app);
        archivo << "_________________________________________" << endl;
        archivo << "Fecha de cita: " << reg.dia << "/" << reg.mes << "/" << reg.anio << endl;
        archivo << "Especialidad: " << reg.especialidad << endl;
        archivo << "Doctor: " << reg.doctor << endl;
        archivo.close();    
        cout << "Informacion registrada exitosamente." << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
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
    archivo << "Nombres: " << p.nombre << '\t' << "Apellidos:" << p.apellido << endl;
    archivo << "Fecha de nacimiento: " << p.dia2 << "/" << p.mes2 << "/" << p.anio2 << endl;
    archivo.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    paciente pac;
    registro reg;
    int op;
    cout << "============================" << endl;
    cout << "REGISTRO DE HISTORIAL MEDICO" << endl;
    cout << "============================" << endl;
    cout << "Bienvenido al sistema de registro de pacientes." << endl;
    do
    {
        cout << "Por favor ingrese una opcion" << endl;
        cout << "1.- Registro de un paciente nuevo." << endl;
        cout << "2.- Agregar informacion de un paciente." << endl;
        cout << "3.- Consulta de informacion del paciente (Por numero de cedula)." << endl;
        cout << "4.- Modificar informacion de un paciente." << endl;
        cout << "5.- Salir" << endl;
        do
        {
            cout << "Por favor, ingrese una de las opciones mostradas (1 - 5)" << endl;
            cin >> op;
        } while (op < 1 || op > 5);

        switch (op)
        {
        case 1:
            pedirCedula(pac);
            if (crearArchivoPaciente(pac))
            {
                registrarPaciente(pac);
                imprimirArchivo(pac);
            }
            break;
        case 2:
            pedirCedula(pac);
            registroInfo(pac, reg);
            break;
        case 3:
            int metodo;
            pedirCedula(pac);
            if (!archivoExistente(pac))
            {
                cout << "No se encontro ningun registro con esta cedula." << endl;
            }
            else
            {
                cout << "Registro encontrado." << endl;
                do
                {
                    cout << "Ingrese el metodo por el que buscara la informacion del paciente." << endl;
                    cout << "1.- Fecha de atencion." << endl;
                    cout << "2.- Especialidad." << endl;
                    cin >> metodo;
                } while (metodo != 1 && metodo != 2);
                switch (metodo)
                {
                case 1:
                    busquedaFecha(pac, reg);
                    break;
                case 2:
                    seleccionarEspecialidad();
                    break;
                }
            }
            break;
        case 4:
            break;
        case 5:
            cout << "Saliendo..." << endl;
            break;
        default:
            break;
        }
    } while (op != 5);
    return 0;
}