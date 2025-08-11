#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>
#include <chrono>
#include <ctime>
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

struct registro{
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
bool validarNombre(string nombre){
    if (nombre.empty()) {
        return false;
    }
    regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ]+(\\s(de|la|los|las|del|y|d'|D')?\\s?[A-Za-zÁÉÍÓÚáéíóúÑñ]+)*$");
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
// Función que obtiene la fecha actual y la guarda en la estructura
void obtenerFechaActual(paciente &p) {
    auto ahora = chrono::system_clock::now();
    time_t tiempo_actual = chrono::system_clock::to_time_t(ahora);
    tm* fecha_local = localtime(&tiempo_actual);
    
    p.dia1 = fecha_local->tm_mday;
    p.mes1 = fecha_local->tm_mon + 1;  // Ajuste porque meses van de 0-11
    p.anio1 = fecha_local->tm_year + 1900;  // Ajuste porque cuenta desde 1900
}
bool esNumero(const string& texto) {
    regex patron("^[0-9]+$");
    return regex_match(texto, patron);
}
void registrarPaciente(paciente &nuevoPaciente) {
    obtenerFechaActual(nuevoPaciente);
    bool fechaValida = false;
    do {
        cout << "Nombre del paciente: ";
        getline(cin, nuevoPaciente.nombre);
        if(!validarNombre(nuevoPaciente.nombre)) {
            cout << "Error: Solo se permiten letras y espacios.\n";
        }
    } while(!validarNombre(nuevoPaciente.nombre));
    do {
        cout << "Apellido del paciente: ";
        getline(cin, nuevoPaciente.apellido);
        if(!validarNombre(nuevoPaciente.apellido)) {
            cout << "Error: Solo se permiten letras y espacios.\n";
        }
    } while(!validarNombre(nuevoPaciente.apellido));
     do {
        string sDia, sMes, sAnio;
        cout << "Ingrese la fecha de nacimiento del paciente (dd mm aaaa): " << endl;
        cout << "Dia: ";
        cin >> sDia;
        if (!esNumero(sDia)) { cout << "Error: El día debe contener solo números."<<endl; continue; }
        cout << "Mes: ";
        cin >> sMes;
        if (!esNumero(sMes)) { cout << "Error: El mes debe contener solo números."<<endl; continue; }
        cout << "Anio: ";
        cin >> sAnio;
        if (!esNumero(sAnio)) { cout << "Error: El año debe contener solo números."<<endl; continue; }

        nuevoPaciente.dia2  = stoi(sDia);
        nuevoPaciente.mes2  = stoi(sMes);
        nuevoPaciente.anio2 = stoi(sAnio);

        fechaValida = validarFecha(nuevoPaciente.dia2, nuevoPaciente.mes2, nuevoPaciente.anio2);
        if (!fechaValida) {
            cout << "Por favor, ingrese una fecha válida.\n";
        }

    } while (!fechaValida);

    // Validación de sexo
    do {
        cout << "Ingresa el sexo del paciente (M/F): ";
        cin >> nuevoPaciente.sexo;
        if (nuevoPaciente.sexo != 'M' && nuevoPaciente.sexo != 'F') {
            cout << "Error: Ingrese solo M o F." << endl;
        }
    } while (nuevoPaciente.sexo != 'M' && nuevoPaciente.sexo != 'F');

    cout << "Paciente registrado con éxito!" << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool archivoExistente(paciente p)
{ // funcion encargada de buscar el archivo en funcion del numero de cedula
    string nombreAr = p.cedula + ".txt";
    ifstream archivo(nombreAr);
    archivo.close();
    return archivo.good();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
void busquedaFecha(paciente p, registro r) {
    int dia, mes, anio;
    bool fechaValida = false;
    // Validación de fecha
    do {
        cout << "Ingrese la fecha que desea buscar: " << endl;
        cout << "Dia: ";
        cin >> dia;
        cout << "Mes: ";
        cin >> mes;
        cout << "Anio: ";
        cin >> anio;
        
        fechaValida = validarFecha(dia, mes, anio);
        if (!fechaValida) {
            cout << "Fecha invalida. Por favor ingrese una fecha valida." << endl;
            // Limpiar el buffer de entrada en caso de error
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!fechaValida);

    string fechaBusqueda = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
    cout << "Buscando citas para la fecha: " << fechaBusqueda << endl;
    
    ifstream archivo(nombreArchivo(p));
    bool encontrado = false;
    
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    else {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find(fechaBusqueda) != string::npos) {
                encontrado = true;
                cout << linea << endl;
                while(getline(archivo, linea) && linea != "_________________________________________") {
                    cout << linea << endl;
                }
                cout << "_________________________________________" << endl;
            }
        }
        if(!encontrado) {
            cout << "No se encontraron registros para esta fecha." << endl;
        }
        archivo.close();
    }
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
//////////////////////////////////////////////////////////////////////////////////////////////////
void busquedaEspecialidad(paciente pac, registro reg)
{
    int opcion = seleccionarEspecialidad();
    string espeselec= especialidadLista[opcion - 1];
    cout << "Buscando citas para la especialidad: " << espeselec << endl;
    ifstream archivo(nombreArchivo(pac));
    bool encontrado = false;
    if(!archivo){
        cout << "Error al abrir el arcivo."<< endl;
        return;
    } else {
        string linea;
        while(getline(archivo, linea)){
            if(linea.find(espeselec) != string::npos){
                encontrado  = true;
                cout << linea << endl;
                while(getline(archivo, linea) && linea != "_________________________________________"){
                    cout << linea << endl;
                }
                cout << "_________________________________________" << endl; 
            }
        }
        if(!encontrado){
            cout << "No se encontraron registros para esta espeialidad con este paciente." << endl;
        }
    }
    archivo.close();
}  
/////////////////////////////////////////////////////////////////////////////////////////////////////
void obtenerFechaActual(registro &reg) {
    auto ahora = chrono::system_clock::now();
    time_t tiempo_actual = chrono::system_clock::to_time_t(ahora);
    tm* fecha_local = localtime(&tiempo_actual);

    reg.dia = fecha_local->tm_mday;
    reg.mes = fecha_local->tm_mon + 1;
    reg.anio = fecha_local->tm_year + 1900;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void registroInfo(paciente &pac, registro &reg) {
    if (!archivoExistente(pac)) {
        cout << "No se encontro ningun registro con esta cedula." << endl;
        return;
    }

    cout << "Registro encontrado." << endl;
    
    // Asignación automática de fecha
    obtenerFechaActual(reg);
    cout << "Fecha de consulta asignada automaticamente: " 
         << reg.dia << "/" << reg.mes << "/" << reg.anio << endl;

    // Selección de especialidad
    cout << "Seleccione la especialidad de la cita: ";
    reg.especialidad = especialidadLista[seleccionarEspecialidad() - 1];
    
    // Validación del nombre del doctor
    bool nombreValido = false;
    do {
        cin.ignore();
        cout << "Ingrese el nombre del doctor a cargo: ";
        getline(cin, reg.doctor);
        
        nombreValido = validarNombre(reg.doctor);
        if (!nombreValido) {
            cout << "Nombre invalido. Solo se permiten letras." << endl;
        }
    } while (!nombreValido);

    // Escritura en archivo
    ofstream archivo(nombreArchivo(pac), ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo para registro." << endl;
        return;
    }

    archivo << "_________________________________________" << endl
            << "Fecha de cita: " << reg.dia << "/" << reg.mes << "/" << reg.anio << endl
            << "Especialidad: " << reg.especialidad << endl
            << "Doctor: " << reg.doctor << endl;
    
    cout << "Información registrada exitosamente el " 
         << reg.dia << "/" << reg.mes << "/" << reg.anio << endl;
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
                    busquedaEspecialidad(pac, reg);
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