#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include<vector>
#include <cstring>

#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;
using std::stoi;
const string ARCHIVO_CLIENTES = "clientes.txt";
const string ARCHIVO_TEMPORAL = "temporal.txt";
const string ARCHIVO_TEMPORALBILLETE = "temporalBillete.txt";
const string ARCHIVO_BILLETES = "contenedorBilletes.txt";
const string ARCHIVO_MOVIMIENTOS = "movimiento.txt";

struct Cliente
{
	int codigo;
	char nombre[30];
	char dni[30];
	int pin;
	double saldo;
};

struct Billete
{
	int codigo;
	char nombre[30];
	double saldo10;
	double saldo20;
	double saldo50;
	double saldo100;
	double saldo200;
};

//funciones administrador
void registrarCliente();
void listarCliente();
Cliente buscarCliente(int id);
void ModificarCliente(int id);
vector<Cliente> ObtenerListaCliente();
void ordenarSEL(vector<Cliente>& lista);
void MostrarListaCliente(vector<Cliente>& lista);
void listarBilletes();
void modificarBilletes(int id);
Billete buscarBillete(int id);
Cliente buscarClienteDni(string dni);
void registrarCajero();

//funcione cliente
void depositar();
void depositarBilletesCajero(Billete modBillete);
void retirarBilletes();
void retirarBilletesCajero(Billete modBillete);
void registrarMovimientos(int codigoCliente, int monto, int codigoCajero, string tipo);
void listarMovimiento();
void pagarServicio();
void transferirSaldo();

//variables globales
Cliente clienteValidado;
//menus
void Principal();
void menuPrincipal();
void menuCliente();
void menuAdministrador();


int main() {
	Principal();
	menuPrincipal();
}

void Principal() {

	cout << "		        |---------------------------------------------------|" << endl;
	cout << "	                |       ______________________                      |" << endl;
	cout << "		        | ____  |                    |  ____                |" << endl;
	cout << "		        | |__|  |     BIENVENIDO     |  |__|                |" << endl;
	cout << "		        | ____  |         AL         |  ____                |" << endl;
	cout << "    			| |__|  |       CAJERO       |  |__|     -------    |" << endl;
	cout << "	                | ____  |     AUTOMATICO     |  ____    | ----- |   |" << endl;
	cout << "	                | |__|  |                    |  |__|     -------    |" << endl;
	cout << "			|       |____________________|                      |" << endl;
	cout << "			|                                                   |" << endl;
	cout << "			|           --------------                          |" << endl;
	cout << "			|          |	    	  |                         |" << endl;
	cout << "			|           --------------                          |" << endl;
	cout << "			|         ___  ___  ___   _____                     |" << endl;
	cout << "			|         |1|  |2|  |3|   |___|                     |" << endl;
	cout << "			|         ___  ___  ___   _____                     |" << endl;
	cout << "			|         |4|  |5|  |6|   |___|                     |" << endl;
	cout << "			|         ___  ___  ___   _____                     |" << endl;
	cout << "			|         |7|  |8|  |9|   |___|                     |" << endl;
	cout << "			|         ___  ___  ___   _____                     |" << endl;
	cout << "			|         |*|  |0|  |.|   |___|                     |" << endl;
	cout << "			|                                                   |" << endl;
	cout << "			|---------------------------------------------------|" << endl;
	cout << "                                                                BIENVENIDO..." << endl;
	system("color 0E");
	Sleep(3000);
	system("cls");
}

void menuPrincipal() {
	system("color 5");
	string usuario;
	string contrasena;
	char op;
	do {

		setlocale(LC_ALL, "spanish");

		cout << "------------------ " << endl;
		cout << "| Menú Principal | " << endl;
		cout << "------------------ " << endl;
		cout << " 1 .- Usuario Cliente (UC) " << endl;
		cout << " 2 .- Usuario Administrador (UA) " << endl;
		cout << " 3 .- Salir del cajero " << endl;
		cout << " Elija una opcion: ";
		cin >> op;

		switch (op) {
		case '1': {
			system("cls");
			string dni;
			int pin;
			cout << "Ingrese su DNI: ";
			cin >> dni;
			Cliente cliente = buscarClienteDni(dni);
			if (cliente.codigo > 0) {
				cout << "Ingrese su pin: " ;
				cin >> pin;
				if (cliente.pin == pin) {
					system("cls");
					clienteValidado = cliente;
					menuCliente();
				}
				else {
					cout << "Pin incorrecto" << endl;
					system("pause");
					system("cls");
					menuPrincipal();
				}
			}
			else {
				cout << "No se encontro el cliente" << endl;
				system("pause");
				system("cls");
				menuPrincipal();
			}
			break; }

		case '2': {
			system("cls");
			cout << "Ingrese su usuario" << endl;
			cin >> usuario;
			//getline(cin, usuario);
			cout << "Ingrese su pass" << endl;
			cin >> contrasena;
			if (usuario == "admin" && contrasena == "1234") {
				cout << "Inicio de sesion exitoso!" << endl;
				system("cls");
				menuAdministrador();
			}
			else {
				cout << "Usuario o contraseña incorrectos" << endl;
				system("pause");
				system("cls");
			}
			//menuAdministrador();
			break; }
		}
	} while (op != '3');
}

// Usuario Cliente

void menuCliente() {
	system("color 2");
	system("cls");
	char mc;
	do {

		setlocale(LC_ALL, "spanish");
		cout << endl << endl;

		cout << "------------------ " << endl;
		cout << "|  Menú Cliente  | " << endl;
		cout << "------------------ " << endl;
		cout << " [1] Deposito " << endl;
		cout << " [2] Retiro " << endl;
		cout << " [3] Transferencia " << endl;
		cout << " [4] Pago Servicio " << endl;
		cout << " [5] Consulta Saldo " << endl;
		cout << " [6] Consulta Movimiento " << endl;
		cout << " [7] Salir " << endl;
		cout << " Elija a donde desea ir: ";
		cin >> mc;

		switch (mc) {
		case '1': {
			system("cls");
			depositar();
			break; }

		case '2': {
			system("cls");
			retirarBilletes();		
			break; }
		case '3': {
			system("cls");
			transferirSaldo();
			break;
		}
		case '4': {
			system("cls");
			pagarServicio();
			break; }

		case '5': {
			system("cls");
			cout << "Su saldo actual es: " << clienteValidado.saldo << endl;
			system("pause");
			menuCliente();
			break; }
		case '6': {
			system("cls");
			listarMovimiento();
			break; }
		}

	} while (mc != '7');
	system("cls");
	menuPrincipal();
}


// Menu Administrador

void menuAdministrador() {
	system("cls");
	system("color 0C");
	char mc;
	do {

		setlocale(LC_ALL, "spanish");
		cout << endl << endl;

		cout << "---------------------- " << endl;
		cout << "| Menú Administrador | " << endl;
		cout << "---------------------- " << endl;
		cout << " [1] Registro Clientes " << endl;
		cout << " [2] Listar Clientes " << endl;
		cout << " [3] Buscar Clientes " << endl;
		cout << " [4] Modificar Clientes " << endl;
		cout << " [5] Listar Dispensador " << endl;
		cout << " [6] Modificar Dispensador " << endl;
		cout << " [7] Registrar Cajero " << endl;
		cout << " [8] Salir " << endl;
		cout << " Elija a donde desea ir: ";
		cin >> mc;

		switch (mc) {
		case '1': {
			system("cls");
			registrarCliente();
			break; }

		case '2': {
			system("cls");
			listarCliente();
			cout << endl;
			vector<Cliente> lisClientes = ObtenerListaCliente();
			ordenarSEL(lisClientes);
			MostrarListaCliente(lisClientes);
			system("pause");
			menuAdministrador();
			break; }
		case '3': {
			system("cls");
			int id;
			cout << "Ingrese el id del cliente que desea buscar: ";
			cin >> id;
			Cliente  cli = buscarCliente(id);
			if (cli.codigo == -1) {
				cout << "No se encontro el cliente" << endl;
			}
			else {
				cout << "Codigo: " << cli.codigo << endl;
				cout << "Nombre: " << cli.nombre << endl;
				cout << "Saldo: " << cli.saldo << endl;
			}
			system("pause");
			break; }
		case '4': {
			system("cls");
			int id;
			cout << "Ingrese el id del cliente que desea modificar: ";
			cin >> id;
			ModificarCliente(id);
			break; }
		case '5': {
			listarBilletes();
			system("pause");
			menuAdministrador();
			break; }
		case '6': {
			int codigo;
			cout << "Ingrese el codigo del billete: ";
			cin >> codigo;

			modificarBilletes(codigo);

			menuPrincipal();
			break; }
		case '7': {
			system("cls");
			registrarCajero();
			break; }
		case '8': {
			menuPrincipal();
			break; }
		}


	} while (mc != '3');
	system("cls");
}


void registrarCliente() {
	cout << endl << "Registro de clientes" << endl;
	Cliente c;
	cout << "Codigo: ";
	cin >> c.codigo;

	Cliente caux = buscarCliente(c.codigo);

	if (caux.codigo == -1)
	{
		/*
			int codigo;
			char nombre[30];
			char dni[8];
			char pin[4];
			double saldo;
		*/
		cin.ignore();
		cout << "Nombre: ";
		cin.getline(c.nombre, 30);
		cout << "dni: ";
		cin.getline(c.dni, 30);
		c.pin = 1000+rand()%(9999-1000);
		cout << "Saldo: ";
		cin >> c.saldo;

		ofstream fescribir;
		fescribir.open(ARCHIVO_CLIENTES.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << c.codigo << ";";
		fescribir << c.nombre << ";";
		fescribir << c.dni << ";";
		fescribir << c.pin << ";";
		fescribir << c.saldo << "\n";
		fescribir.close();
	}
	else
	{
		cout << endl << "Ya se encuentra registrado" << endl;
		cout << endl << caux.codigo << ";" << caux.nombre << ";" << caux.saldo << "\n";

	}
	system("pause");
	menuAdministrador();
}

void registrarCajero() {
	cout << endl << "Registro de cajero" << endl;
	Billete b;
	cout << "Codigo: ";
	cin >> b.codigo;

	Billete baux = buscarBillete(b.codigo);

	if (baux.codigo == -1)
	{

		cin.ignore();
		cout << "Nombre: ";
		cin.getline(b.nombre, 30);
		cout << "Cantidad billetes de 10: ";
		cin >> b.saldo10;
		cout << "Cantidad billetes de 20: ";
		cin >> b.saldo20;
		cout << "Cantidad billetes de 50: ";
		cin >> b.saldo50;
		cout << "Cantidad billetes de 100: ";
		cin >> b.saldo100;
		cout << "Cantidad billetes de 200: ";
		cin >> b.saldo200;

		ofstream fescribir;
		fescribir.open(ARCHIVO_BILLETES.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << b.codigo << ";";
		fescribir << b.nombre << ";";
		fescribir << b.saldo10 << ";";
		fescribir << b.saldo20 << ";";
		fescribir << b.saldo50 << ";";
		fescribir << b.saldo100 << ";";
		fescribir << b.saldo200 << "\n";
		fescribir.close();
	}
	else
	{
		cout << endl << "Ya se encuentra registrado" << endl;
		//cout << endl << baux.codigo << ";" << baux.nombre << ";" << baux.saldo << "\n";
		cout << endl << baux.codigo << ";" << baux.nombre << ";" << baux.saldo10 << ";" << baux.saldo20 << ";" << baux.saldo50 << ";" << baux.saldo100 << ";" << baux.saldo200 << "\n";
	}
	system("pause");
	menuAdministrador();
}
void registrarMovimientos(int codigoCliente, int monto, int codigoCajero, string tipo, string descripcion) {

	/*
		int codigo;
		char nombre[30];
		char dni[8];
		char pin[4];
		double saldo;
	*/
	//obetener fecha actual y convertirlo a cadena en el formate d/m/yyyy
	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    auto strFecha = oss.str();

	ofstream fescribir;
	fescribir.open(ARCHIVO_MOVIMIENTOS.c_str(), ios::out | ios::app); // crear y agregar
	fescribir << codigoCliente << ";";
	fescribir << codigoCajero << ";";
	fescribir << tipo << ";";
	fescribir << monto << ";";
	fescribir << descripcion << ";";
	fescribir << strFecha << "\n";
	fescribir.close();
}
void listarCliente() {
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	cout << endl << "Listado de clientes" << endl;
	string codigo, nombre, dni,pin, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			cout.width(8);
			cout << left << codigo;
			cout.width(12);
			cout << left << nombre;
			cout.width(12);
			cout << left << dni;
			cout.width(12);
			cout << left << pin;
			cout.width(12);
			cout << right << saldo;
			cout << endl;

		}

	}
	leer_archivo.close();

}


void listarBilletes() {
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_BILLETES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	cout << endl << "Listado de billetes" << endl;
	string codigo, nombre,saldo10, saldo20, saldo50, saldo100, saldo200;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo10, ';');
		getline(leer_archivo, saldo20, ';');
		getline(leer_archivo, saldo50, ';');
		getline(leer_archivo, saldo100, ';');
		getline(leer_archivo, saldo200, '\n');

		if (codigo.length() > 0)
		{
			cout.width(8);
			cout << left << codigo;
			cout.width(12);
			cout << left << nombre;
			cout.width(12);
			cout << left << saldo10;
			cout.width(12);
			cout << left << saldo20;
			cout.width(12);
			cout << left << saldo50;
			cout.width(12);
			cout << left << saldo100;
			cout.width(12);
			cout << left << saldo200;
			cout << endl;

		}

	}
	leer_archivo.close();

}

void listarMovimiento() {
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_MOVIMIENTOS, ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	cout << endl << "Listado de Movimientos" << endl;
	string cajero, cliente, tipo, monto, descripcion, fecha;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, cliente, ';');
		getline(leer_archivo, cajero, ';');
		getline(leer_archivo, tipo, ';');
		getline(leer_archivo, monto, ';');
		getline(leer_archivo, descripcion, ';');
		getline(leer_archivo, fecha, '\n');

		if (cliente.length() > 0 && stoi(cliente) == clienteValidado.codigo)
		{
			Billete tempB = buscarBillete(stoi(cajero));
			cout.width(8);
			cout << left << tempB.nombre;
			cout.width(12);
			cout << left << tipo;
			cout.width(12);
			cout << left << monto;
			cout.width(12);
			cout << left << descripcion;
			cout.width(12);
			cout << left << fecha;
			cout << endl;

		}

	}
	leer_archivo.close();
	system("pause");
	system("cls");
	menuCliente();
}


Cliente buscarCliente(int id)
{

	Cliente c;
	c.codigo = -1;

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return c;
	}

	string codigo, nombre, dni, pin, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0 && atoi(codigo.c_str()) == id)
		{
			c.codigo = atoi(codigo.c_str());
			strcpy_s(c.nombre, nombre.c_str());
			strcpy_s(c.dni, dni.c_str());
			c.pin = atoi(pin.c_str());
			c.saldo = atoi(saldo.c_str());
			break;
		}

	}
	leer_archivo.close();
	return c;

}

Cliente buscarClienteDni(string dniBuscar)
{

	Cliente c;
	c.codigo = -1;

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return c;
	}

	string codigo, nombre, dni, pin, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (dni.length() > 0 && dni == dniBuscar)
		{
			c.codigo = atoi(codigo.c_str());
			strcpy_s(c.nombre, nombre.c_str());
			strcpy_s(c.dni, dni.c_str());
			c.pin = atoi(pin.c_str());
			c.saldo = atoi(saldo.c_str());
			break;
		}

	}
	leer_archivo.close();
	return c;

}

Billete buscarBillete(int id)
{

	Billete b;
	b.codigo = -1;

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_BILLETES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return b;
	}

	string codigo, nombre,saldo10, saldo20, saldo50, saldo100, saldo200;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo10, ';');
		getline(leer_archivo, saldo20, ';');
		getline(leer_archivo, saldo50, ';');
		getline(leer_archivo, saldo100, ';');
		getline(leer_archivo, saldo200, '\n');

		if (codigo.length() > 0 && atoi(codigo.c_str()) == id)
		{
			b.codigo = atoi(codigo.c_str());
			strcpy_s(b.nombre, nombre.c_str());
			b.saldo10 = atoi(saldo10.c_str());
			b.saldo20 = atoi(saldo20.c_str());
			b.saldo50 = atoi(saldo50.c_str());
			b.saldo100 = atoi(saldo100.c_str());
			b.saldo200 = atoi(saldo200.c_str());
			break;
		}

	}
	leer_archivo.close();
	return b;

}

void ModificarCliente(int id)
{

	Cliente modCliente = buscarCliente(id);
	if (modCliente.codigo == -1)
	{
		cout << endl << "No encontrado" << endl;
		return;
	}

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}


	cin.ignore();
	cout << "Nombre ";
	cin.getline(modCliente.nombre, 30);
	//cin >> modCliente.nombre;
	cout << "Saldo ";
	cin >> modCliente.saldo;


	ofstream tmpArchivo;
	tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out | ios::app);

	string codigo, nombre, dni,pin,saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			if (atoi(codigo.c_str()) == id)
			{
				// double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivo << modCliente.codigo << ";" << modCliente.nombre << ";" << modCliente.dni << ";" << modCliente.pin << ";"<< modCliente.saldo << "\n";

			}
			else
			{
				tmpArchivo << codigo << ";" << nombre << ";" << dni << ";" << pin << ";" << saldo << "\n";
			}
		}

	}
	leer_archivo.close();
	tmpArchivo.close();
	remove(ARCHIVO_CLIENTES.c_str());
	rename(ARCHIVO_TEMPORAL.c_str(), ARCHIVO_CLIENTES.c_str());
	system("pause");
	menuAdministrador();
}

void modificarBilletes(int id)
{

	Billete modBillete = buscarBillete(id);
	if (modBillete.codigo == -1)
	{
		cout << endl << "No encontrado" << endl;
		menuAdministrador();
		return;
	}

	

	ifstream leer_archivoBillete;
	leer_archivoBillete.open(ARCHIVO_BILLETES.c_str(), ios::in);
	if (leer_archivoBillete.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		menuAdministrador();
		return;
	}
	
	cin.ignore();
	cout << "Ingrese el nombre del cajero: ";
	cin.getline(modBillete.nombre, 30);
	cout << "Ingrese cantidad de billete de 10: ";
	cin >> modBillete.saldo10;
	cout << "Ingrese cantidad de billete de 20: ";
	cin >> modBillete.saldo20;
	cout << "Ingrese cantidad de billete de 50: ";
	cin >> modBillete.saldo50;
	cout << "Ingrese cantidad de billete de 100: ";
	cin >> modBillete.saldo100;
	cout << "Ingrese cantidad de billete de 200: ";
	cin >> modBillete.saldo200;
	
	ofstream tmpArchivoBillete;
	tmpArchivoBillete.open(ARCHIVO_TEMPORALBILLETE.c_str(), ios::out);
	string codigo, nombre,saldo10, saldo20, saldo50, saldo100, saldo200;
	while (!leer_archivoBillete.eof()) {

		getline(leer_archivoBillete, codigo, ';');
		getline(leer_archivoBillete, nombre, ';');
		getline(leer_archivoBillete, saldo10, ';');
		getline(leer_archivoBillete, saldo20, ';');
		getline(leer_archivoBillete, saldo50, ';');
		getline(leer_archivoBillete, saldo100, ';');
		getline(leer_archivoBillete, saldo200, '\n');

		if (codigo.length() > 0)
		{
			if (atoi(codigo.c_str()) == id)
			{
				
				//double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivoBillete << modBillete.codigo << ";" <<modBillete.nombre << ";" << modBillete.saldo10 << ";" << modBillete.saldo20 << ";" << modBillete.saldo50 << ";" << modBillete.saldo100 << ";" << modBillete.saldo200 << "\n";
				//tmpArchivoBillete << modBillete.billete << ";" << modBillete.saldo << "\n";

			}
			else
			{
				//tmpArchivoBillete << billete << ";" << cantidad << "\n";
				tmpArchivoBillete << codigo << ";" << nombre << ";" << saldo10 << ";" << saldo20 << ";" << saldo50 << ";" << saldo100 << ";" << saldo200 << "\n";
			}
		}

	}
	leer_archivoBillete.close();
	tmpArchivoBillete.close();
	remove(ARCHIVO_BILLETES.c_str());
	rename(ARCHIVO_TEMPORALBILLETE.c_str(), ARCHIVO_BILLETES.c_str());
	system("pause");


	menuAdministrador();
}
void depositarBilletesCajero(Billete modBillete)
{

	ifstream leer_archivoBillete;
	leer_archivoBillete.open(ARCHIVO_BILLETES.c_str(), ios::in);
	if (leer_archivoBillete.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		menuAdministrador();
		return;
	}
	
	
	ofstream tmpArchivoBillete;
	tmpArchivoBillete.open(ARCHIVO_TEMPORALBILLETE.c_str(), ios::out);
	string codigo, nombre,saldo10, saldo20, saldo50, saldo100, saldo200;
	while (!leer_archivoBillete.eof()) {

		getline(leer_archivoBillete, codigo, ';');
		getline(leer_archivoBillete, nombre, ';');
		getline(leer_archivoBillete, saldo10, ';');
		getline(leer_archivoBillete, saldo20, ';');
		getline(leer_archivoBillete, saldo50, ';');
		getline(leer_archivoBillete, saldo100, ';');
		getline(leer_archivoBillete, saldo200, '\n');

		if (codigo.length() > 0)
		{
			if (atoi(codigo.c_str()) == modBillete.codigo)
			{
				
				//double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivoBillete << modBillete.codigo << ";" <<modBillete.nombre << ";" << modBillete.saldo10 << ";" << modBillete.saldo20 << ";" << modBillete.saldo50 << ";" << modBillete.saldo100 << ";" << modBillete.saldo200 << "\n";
				//tmpArchivoBillete << modBillete.billete << ";" << modBillete.saldo << "\n";

			}
			else
			{
				//tmpArchivoBillete << billete << ";" << cantidad << "\n";
				tmpArchivoBillete << codigo << ";" << nombre << ";" << saldo10 << ";" << saldo20 << ";" << saldo50 << ";" << saldo100 << ";" << saldo200 << "\n";
			}
		}

	}
	leer_archivoBillete.close();
	tmpArchivoBillete.close();
	remove(ARCHIVO_BILLETES.c_str());
	rename(ARCHIVO_TEMPORALBILLETE.c_str(), ARCHIVO_BILLETES.c_str());
}
vector<Cliente> ObtenerListaCliente()
{
	vector<Cliente> lista;

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return lista;
	}

	string codigo, nombre, dni,pin,saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			Cliente c;
			c.codigo = atoi(codigo.c_str());
			strcpy_s(c.nombre, nombre.c_str());
			strcpy_s(c.dni, dni.c_str());
			c.pin = atoi(pin.c_str());
			c.saldo = atoi(saldo.c_str());
			lista.push_back(c);

		}

	}
	leer_archivo.close();


	return lista;

}
void ordenarSEL(vector<Cliente>& lista) {
	int idx;
	int n = lista.size();
	for (int i = 0; i < n - 1; i++) {
		idx = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(lista[j].nombre, lista[idx].nombre) < 0)
			{
				idx = j;
			}
		}

		Cliente aux = lista[i];
		lista[i] = lista[idx];
		lista[idx] = aux;

	}

}
void MostrarListaCliente(vector<Cliente>& lista)
{
	cout << endl << "Lista De Clientes Ordenada" << endl;
	for (int i = 0; i < lista.size(); i++)
	{
		Cliente c = lista[i];
		cout << c.codigo << "\t" << c.nombre << "\t"<< c.dni << "\t"<< c.pin << "\t" << c.saldo << endl;
	}
}

void depositar(){
	int idCajero;
	cout << "Ingrese el codigo del cajero: ";
	cin >> idCajero;
	Billete b = buscarBillete(idCajero);
	if (b.codigo == -1)
	{
		cout << "No se encontro el cajero" << endl;
		system("pause");
		menuCliente();
		return;
	}
	cout << "Bienvenido al cajero " << b.nombre << endl;
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}
	cout << "Ingrese cantidad de billetes a depositar, escriba 0 si no desea depositar ese billete: " << endl;
	int cantidadBilletes10, cantidadBilletes20, cantidadBilletes50, cantidadBilletes100, cantidadBilletes200,totalDeposito;
	cin.ignore();

	cout << "Ingrese la cantidad de billetes de 10: ";
	cin >> cantidadBilletes10;
	clienteValidado.saldo += cantidadBilletes10 * 10;
	b.saldo10 += cantidadBilletes10;

	cout << "Ingrese la cantidad de billetes de 20: ";
	cin >> cantidadBilletes20;
	clienteValidado.saldo += cantidadBilletes20 * 20;
	b.saldo20 += cantidadBilletes20;

	cout << "Ingrese la cantidad de billetes de 50: ";
	cin >> cantidadBilletes50;
	clienteValidado.saldo += cantidadBilletes50 * 50;
	b.saldo50 += cantidadBilletes50;

	cout << "Ingrese la cantidad de billetes de 100: ";
	cin >> cantidadBilletes100;
	clienteValidado.saldo += cantidadBilletes100 * 100;
	b.saldo100 += cantidadBilletes100;

	cout << "Ingrese la cantidad de billetes de 200: ";
	cin >> cantidadBilletes200;
	clienteValidado.saldo += cantidadBilletes200 * 200;
	b.saldo200 += cantidadBilletes200;
	totalDeposito = cantidadBilletes10 * 10 + cantidadBilletes20 * 20 + cantidadBilletes50 * 50 + cantidadBilletes100 * 100 + cantidadBilletes200 * 200;
	cout << "El total depositado es: " << totalDeposito << endl;
	//depositando billetes en el archivo de billetes
	depositarBilletesCajero(b);
	ofstream tmpArchivo;
	tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out | ios::app);

	string codigo, nombre, dni,pin,saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, dni, ';');
		getline(leer_archivo, pin, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			if (atoi(codigo.c_str()) == clienteValidado.codigo)
			{
				// double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivo << clienteValidado.codigo << ";" << clienteValidado.nombre << ";" << clienteValidado.dni << ";" << clienteValidado.pin << ";"<< clienteValidado.saldo << "\n";
				registrarMovimientos(clienteValidado.codigo,totalDeposito, b.codigo, "D","Deposito");
			}
			else
			{
				tmpArchivo << codigo << ";" << nombre << ";" << dni << ";" << pin << ";" << saldo << "\n";
			}
		}

	}
	leer_archivo.close();
	tmpArchivo.close();
	remove(ARCHIVO_CLIENTES.c_str());
	rename(ARCHIVO_TEMPORAL.c_str(), ARCHIVO_CLIENTES.c_str());
	system("pause");
	menuCliente();

}

void retirarBilletes(){
	int idCajero;
	cout << "Ingrese el codigo del cajero: ";
	cin >> idCajero;
	Billete b = buscarBillete(idCajero);
	if (b.codigo == -1)
	{
		cout << "No se encontro el cajero" << endl;
		system("pause");
		menuCliente();
		return;
	}


	cout << "Bienvenido al cajero " << b.nombre << endl;
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}
	int montoRetirar = 0,cantidadDescontar = 0;
	cout << "Ingrese el monto a retirar: " << endl;
	cin >> montoRetirar;
	if(montoRetirar % 10 != 0){
		cout << "El monto a retirar debe ser multiplo de 10" << endl;
		system("pause");
		menuCliente();
		return;
	}
	else{
		if (montoRetirar >= clienteValidado.saldo)
		{
			cout << "No tiene suficiente saldo" << endl;
			system("pause");
			menuCliente();
			return;
		}
		else{
			int billete10 = 0, billete20 = 0, billete50 = 0, billete100 = 0, billete200 = 0;
			while(montoRetirar > 0){
				if(montoRetirar >= 200){
					montoRetirar -= 200;
					cantidadDescontar += 200;
					billete200++;
				}
				else if(montoRetirar >= 100){
					montoRetirar -= 100;
					cantidadDescontar += 100;
					billete100++;
				}
				else if(montoRetirar >= 50){
					montoRetirar -= 50;
					cantidadDescontar += 50;
					billete50++;
				}
				else if(montoRetirar >= 20){
					montoRetirar -= 20;
					cantidadDescontar += 20;
					billete20++;
				}
				else if(montoRetirar >= 10){
					montoRetirar -= 10;
					cantidadDescontar += 10;
					billete10++;
				}
			}
			if(b.saldo10 >= billete10 && b.saldo20 >= billete20 && b.saldo50 >= billete50 && b.saldo100 >= billete100 && b.saldo200 >= billete200){
				b.saldo10 -= billete10;
				b.saldo20 -= billete20;
				b.saldo50 -= billete50;
				b.saldo100 -= billete100;
				b.saldo200 -= billete200;
				clienteValidado.saldo -= cantidadDescontar;
				cout << "Retiro realizado con exito: " << endl;
				cout << "Billetes de 10: " << billete10 << endl;
				cout << "Billetes de 20: " << billete20 << endl;
				cout << "Billetes de 50: " << billete50 << endl;
				cout << "Billetes de 100: " << billete100 << endl;
				cout << "Billetes de 200: " << billete200 << endl;
				cout << "Monto retirado: " << cantidadDescontar << endl;
				//cout << "Saldo actual: " << clienteValidado.saldo << endl;

				depositarBilletesCajero(b);
				ofstream tmpArchivo;
				tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out | ios::app);

				string codigo, nombre, dni,pin,saldo;
				while (!leer_archivo.eof()) {
					getline(leer_archivo, codigo, ';');
					getline(leer_archivo, nombre, ';');
					getline(leer_archivo, dni, ';');
					getline(leer_archivo, pin, ';');
					getline(leer_archivo, saldo, '\n');

					if (codigo.length() > 0)
					{
						if (atoi(codigo.c_str()) == clienteValidado.codigo)
						{
							// double saldotmp = atof(saldo.c_str())+monto;
							tmpArchivo << clienteValidado.codigo << ";" << clienteValidado.nombre << ";" << clienteValidado.dni << ";" << clienteValidado.pin << ";"<< clienteValidado.saldo << "\n";
							registrarMovimientos(clienteValidado.codigo,cantidadDescontar, b.codigo, "R","Retiro");

						}
						else
						{
							tmpArchivo << codigo << ";" << nombre << ";" << dni << ";" << pin << ";" << saldo << "\n";
						}
					}

				}
				leer_archivo.close();
				tmpArchivo.close();
				remove(ARCHIVO_CLIENTES.c_str());
				rename(ARCHIVO_TEMPORAL.c_str(), ARCHIVO_CLIENTES.c_str());
				system("pause");
				menuCliente();
			}
			else{
				cout << "No tiene suficientes billetes" << endl;
			}
		}	
	}
}

void pagarServicio(){

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	int idCajero;
	cout << "Ingrese el codigo del cajero: ";
	cin >> idCajero;
	Billete b = buscarBillete(idCajero);
	if (b.codigo == -1)
	{
		cout << "No se encontro el cajero" << endl;
		system("pause");
		menuCliente();
		return;
	}
	cout << "Bienvenido al cajero " << b.nombre << endl;

	string descripcion;
	double montoPago;
	cin.ignore();
	cout << "Servicio a pagar[Luz,agua,telefono,internet]: ";
	cin >> descripcion;
	//cin >> modCliente.nombre;
	cout << "Monto a pagar: ";
	cin >> montoPago;
	if(montoPago > clienteValidado.saldo){
		cout << "No tiene suficiente saldo" << endl;
		system("pause");
		menuCliente();
		return;
	}
	else{
		ofstream tmpArchivo;
		tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out | ios::app);

		string codigo, nombre, dni,pin,saldo;
		while (!leer_archivo.eof()) {
			getline(leer_archivo, codigo, ';');
			getline(leer_archivo, nombre, ';');
			getline(leer_archivo, dni, ';');
			getline(leer_archivo, pin, ';');
			getline(leer_archivo, saldo, '\n');

			if (codigo.length() > 0)
			{
				if (atoi(codigo.c_str()) == clienteValidado.codigo)
				{
					// registrarMovimientos(int codigoCliente, int monto, int codigoCajero, string tipo, string descripcion)
					clienteValidado.saldo -= montoPago;
					tmpArchivo << clienteValidado.codigo << ";" << clienteValidado.nombre << ";" << clienteValidado.dni << ";" << clienteValidado.pin << ";"<< clienteValidado.saldo << "\n";
					registrarMovimientos(clienteValidado.codigo,montoPago, b.codigo, "P",descripcion);
				}
				else
				{
					tmpArchivo << codigo << ";" << nombre << ";" << dni << ";" << pin << ";" << saldo << "\n";
				}
			}

		}
		leer_archivo.close();
		tmpArchivo.close();
		remove(ARCHIVO_CLIENTES.c_str());
		rename(ARCHIVO_TEMPORAL.c_str(), ARCHIVO_CLIENTES.c_str());
		cout << "Pago realizado con exito!" << endl;
		system("pause");
		menuCliente();	

	}
	
}

void transferirSaldo(){
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	int idCajero;
	cout << "Ingrese el codigo del cajero: ";
	cin >> idCajero;
	Billete b = buscarBillete(idCajero);
	if (b.codigo == -1)
	{
		cout << "No se encontro el cajero" << endl;
		system("pause");
		menuCliente();
		return;
	}
	cout << "Bienvenido al cajero " << b.nombre << endl;

	string dni;
	double montoTransferir;
	cin.ignore();
	cout << "Ingrese el dni a transferir: ";
	cin >> dni;
	Cliente clientDestino = buscarClienteDni(dni);
	if(clientDestino.codigo == -1){
		cout << "No se encontro el cliente" << endl;
		system("pause");
		menuCliente();
		return;
	}

	cout << "Monto a transferir: ";
	cin >> montoTransferir;
	if(montoTransferir > clienteValidado.saldo){
		cout << "No tiene suficiente saldo para transefir" << endl;
		system("pause");
		menuCliente();
		return;
	}
	else{
		ofstream tmpArchivo;
		tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out | ios::app);

		string codigo, nombre, dni,pin,saldo;
		while (!leer_archivo.eof()) {
			getline(leer_archivo, codigo, ';');
			getline(leer_archivo, nombre, ';');
			getline(leer_archivo, dni, ';');
			getline(leer_archivo, pin, ';');
			getline(leer_archivo, saldo, '\n');

			if (codigo.length() > 0)
			{
				if (atoi(codigo.c_str()) == clienteValidado.codigo)
				{
					// registrarMovimientos(int codigoCliente, int monto, int codigoCajero, string tipo, string descripcion)
					clienteValidado.saldo -= montoTransferir;
					tmpArchivo << clienteValidado.codigo << ";" << clienteValidado.nombre << ";" << clienteValidado.dni << ";" << clienteValidado.pin << ";"<< clienteValidado.saldo << "\n";
					registrarMovimientos(clienteValidado.codigo,montoTransferir, b.codigo, "T","Transferencia");
				}
				else if (atoi(codigo.c_str()) == clientDestino.codigo){
					clientDestino.saldo += montoTransferir;
					tmpArchivo << clientDestino.codigo << ";" << clientDestino.nombre << ";" << clientDestino.dni << ";" << clientDestino.pin << ";"<< clientDestino.saldo << "\n";
					registrarMovimientos(clientDestino.codigo,montoTransferir, b.codigo, "R","Recibido");
				}
				else
				{
					tmpArchivo << codigo << ";" << nombre << ";" << dni << ";" << pin << ";" << saldo << "\n";
				}
			}

		}
		leer_archivo.close();
		tmpArchivo.close();
		remove(ARCHIVO_CLIENTES.c_str());
		rename(ARCHIVO_TEMPORAL.c_str(), ARCHIVO_CLIENTES.c_str());
		cout << "Transferencia realizada correctamente!" << endl;
		system("pause");
		menuCliente();	

	}

}