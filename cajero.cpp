#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include<vector>
#include <cstring>
using namespace std;
using std::stoi;
const string ARCHIVO_CLIENTES = "clientes.txt";
const string ARCHIVO_TEMPORAL = "temporal.txt";
const string ARCHIVO_TEMPORALBILLETE = "temporalBillete.txt";
const string ARCHIVO_BILLETES = "contenedorBilletes.txt";

struct Cliente
{
	int codigo;
	char nombre[30];
	double saldo;
};

struct Billete
{
	int codigo;
	double saldo;
};

//funciones
void registrarCliente();
void listarCliente();
Cliente buscarCliente(int id);
void ModificarCliente(int id);
vector<Cliente> ObtenerListaCliente();
void ordenarSEL(vector<Cliente>& lista);
void MostrarListaCliente(vector<Cliente>& lista);
void listarBilletes();
void modificarBilletes(int id);
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
			menuCliente();
			break; }

		case '2': {
			system("cls");
			cout << "Ingrese su usuario" << endl;
			cin >> usuario;
			//getline(cin, usuario);
			cout << "Ingrese su pass" << endl;
			cin >> contrasena;
			if(usuario == "admin" && contrasena == "1234"){
				cout << "Inicio de sesion exitoso!" << endl;
				system("cls");
				menuAdministrador();
			}
			else{
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

			break; }

		case '2': {

			break; }
		case '3': {

			break;
		}
		case '4': {

			break; }

		case '5': {

			break; }
		case '6': {

			break; }
		}

	} while (mc != '7');
	system("cls");
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
		cout << " [6] Registro Dispensador " << endl;
		cout << " [7] Salir " << endl;
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
			cout << "lista clientes ordenada: " << endl;
			vector<Cliente> lisClientes = ObtenerListaCliente();
			ordenarSEL(lisClientes);
			MostrarListaCliente(lisClientes);
			system("pause");
			menuAdministrador();
			break; }
		case '3': {
			/*
				int codigo;
				char nombre[30];
				double saldo;
			*/

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
			int codigo, cantidad;
			cout << "Ingrese el codigo del billete: ";
			cin >> codigo;
			cout << "Ingrese la cantidad de billetes: ";
			cin >> cantidad;

			modificarBilletes(codigo);

			menuPrincipal();
			break; }
		case '7': {
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

		cin.ignore();
		cout << "Nombre: ";
		cin.getline(c.nombre, 30);

		cout << "Saldo: ";
		cin >> c.saldo;

		ofstream fescribir;
		fescribir.open(ARCHIVO_CLIENTES.c_str(), ios::out | ios::app); // crear y agregar
		fescribir << c.codigo << ";";
		fescribir << c.nombre << ";";
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

void listarCliente() {
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return;
	}

	cout << endl << "Listado de clientes" << endl;
	string codigo, nombre, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			cout.width(8);
			cout << left << codigo;
			cout.width(5);
			cout << left << nombre;
			cout.width(15);
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
	string billete, cantidad;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, billete, ';');
		getline(leer_archivo, cantidad, ';');

		if (billete.length() > 0)
		{
			cout.width(8);
			switch(stoi(billete))
			{
				case 1:{
					cout << left << "Billete de 10 ";
					break;
				}
				case 2:{
					cout << left << "Billete de 20 ";
					break;
				}
				case 3:{
					cout << left << "Billete de 50 ";
					break;
				}
				case 4:{
					cout << left << "Billete de 100 ";
					break;
				}
				case 5:{
					cout << left << "Billete de 200 ";
					break;
				}
			}
			
			cout.width(5);
			cout << left << cantidad;
			cout.width(15);
			cout << endl;

		}

	}
	leer_archivo.close();
	
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

	string codigo, nombre, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0 && atoi(codigo.c_str()) == id)
		{
			c.codigo = atoi(codigo.c_str());
			strcpy_s(c.nombre, nombre.c_str());
			c.saldo = atoi(saldo.c_str());
			break;
		}

	}
	leer_archivo.close();
	return c;

} 

void ModificarCliente(int id) 
{

	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_CLIENTES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return ;
	}

	Cliente modCliente;
	cin.ignore();
	cout << "Nombre ";
	cin.getline(modCliente.nombre, 30);

	cout << "Saldo ";
	cin >> modCliente.saldo;


	ofstream tmpArchivo;
	tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out);



	string codigo, nombre, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 2)
		{
			if (atoi(codigo.c_str()) == id) 
			{
				 //double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivo << codigo << ";" << modCliente.nombre << ";" << modCliente.saldo << "\n";

			}
			else 
			{
				tmpArchivo << codigo << ";" << nombre << ";" << saldo << "\n";
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
	ifstream leer_archivo;
	leer_archivo.open(ARCHIVO_BILLETES.c_str(), ios::in);
	if (leer_archivo.fail()) {
		cout << endl << " No se puede leer el archivo" << endl;
		return ;
	}

	Billete modBillete;
	cin.ignore();
	cout << "Ingrese cantidad de billete ";
	cin >> modBillete.saldo;

	ofstream tmpArchivo;
	tmpArchivo.open(ARCHIVO_TEMPORAL.c_str(), ios::out);
	string billete, cantidad;
	while (!leer_archivo.eof()) {

		getline(leer_archivo, billete, ';');
		getline(leer_archivo, cantidad, ';');

		if (billete.length() > 2)
		{
			if (atoi(billete.c_str()) == id) 
			{
				 //double saldotmp = atof(saldo.c_str())+monto;
				tmpArchivo << id << ";" << modBillete.saldo << ";" << "\n";

			}
			else 
			{
				tmpArchivo << billete << ";" << cantidad << ";" << "\n";
			}
		}

	}
	leer_archivo.close();
	tmpArchivo.close();
	remove(ARCHIVO_BILLETES.c_str());
	rename(ARCHIVO_TEMPORALBILLETE.c_str(), ARCHIVO_BILLETES.c_str());
	system("pause");
	menuAdministrador();
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

	string codigo, nombre, saldo;
	while (!leer_archivo.eof()) {
		getline(leer_archivo, codigo, ';');
		getline(leer_archivo, nombre, ';');
		getline(leer_archivo, saldo, '\n');

		if (codigo.length() > 0)
		{
			Cliente c;
			c.codigo = atoi(codigo.c_str());
			strcpy_s(c.nombre, nombre.c_str());
			c.saldo = atoi(saldo.c_str());
			lista.push_back(c);

		}

	}
	leer_archivo.close();


	return lista;

}
void ordenarSEL(vector<Cliente> &lista) {
	int idx;
	int n = lista.size();
	for (int i = 0; i < n - 1; i++) {
		idx = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(lista[j].nombre, lista[idx].nombre)<0)
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
	cout << endl << "Lista De Clientes" << endl;
	for (int i = 0; i < lista.size(); i++)
	{
		Cliente c = lista[i];
		cout << c.codigo << "\t" << c.nombre << "\t" << c.saldo << endl;
	}
}