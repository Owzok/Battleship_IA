#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdio>
#include <exception>
#include <string> 
#include <fstream>
#include "CNave.h"
#include "CTablero.h"
#include <chrono>
#include <ctime>  

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif 
/*arreglo para eliminar archivos*/
namespace aplicacion {
	int remove(std::string const& filename)
	{
		return std::remove(filename.c_str());
	}
}

const int filas = 10;
const int columnas = 10;
char matriz[filas][columnas];
char matriz_contraria[filas][columnas];

std::string jugador = "";
std::string equipo = "";
std::string ubicacion_combate = "G:\\Unidades compartidas\\Campo_de_Batalla\\";
int estado_juego = 1;

void IngresarNave(int x, int y, int largo, char horientacion, char letra) {
	if (horientacion == 'V') {
		for (int i = x; i < x+largo; i++)
		{
			matriz[i][y] = letra;
		}
	}
	else if(horientacion == 'H') {
		for (int i = y; i < y + largo; i++)
		{
			matriz[x][i] = letra;
		}
	}
}

int Crear_Nave(int x, int y, char tipo_nave, char horientacion) {
	int largo = 0;
	int bandera1 = 1;
	if (tipo_nave == 'A') {
		largo = 4;
	}else if (tipo_nave == 'B') {
		largo = 3;
	}else if (tipo_nave == 'S') {
		largo = 2;
	}else if (tipo_nave == 'T') {
		largo = 1;
	}

	if (horientacion=='V') {
		for (int i=x;(i<x+largo);i++)
		{
			if (matriz[i][y] != '.') {
				bandera1=0;
			}
		} 
	}else if (horientacion == 'H') {
		for (int i=y;i<(y+largo);i++)
		{
			if (matriz[x][i] != '.') {
				bandera1 = 0;
			}
		}
	}

	if (bandera1 == 1) {
		IngresarNave(x, y, largo, horientacion, tipo_nave);
	}
	return bandera1;
}

int Letra_a_Numero(char a) {
	int aux = 0;
	int ia = (int)a;
	int iaa = (int)'a';
	int iA = (int)'A';

	if (a >= 'a' and a <= 'z') {
		aux= 1 + (int)a - (int)'a';
	}else if (a >= 'A' and a <= 'Z') {
		aux= 1 + (int)a - (int)'A';
	}
	return aux;
} 
 
void CrearArchivos() {
	std::ofstream archivo;
	archivo.open(ubicacion_combate + "FirstPlayer.in");
	archivo.close();
	archivo.open(ubicacion_combate + "SecondPlayer.in");
	archivo.close();
	archivo.open(ubicacion_combate + "FirstPlayer.out");
	archivo.close();
	archivo.open(ubicacion_combate + "SecondPlayer.out");
	archivo.close();
}

void GuardarJugada(std::string token_, std::string jugada, std::string extension) {
	std::ofstream archivo1; 
	std::string ruta = ubicacion_combate + jugador + "." + extension;
	archivo1.open(ruta);
	if (token_ == ("")) {
		archivo1 << token_;
	}
	archivo1 << jugada;
	while (archivo1.is_open()) {
		archivo1.close();
	}
}

 
void GuardarJugada2(std::string token_, std::string jugada, std::string extension) {
	std::ofstream archivo1;
	archivo1.open(ubicacion_combate + jugador + "." + extension);
	archivo1 << token_ + "\n";
	archivo1 << jugada;
	while (archivo1.is_open()) {
		archivo1.close();
	}
}

std::string BuscarEnArchivo(std::string token, std::string extension) {
	std::string Linea;
	std::ifstream archivo(ubicacion_combate + jugador + "." + extension);
	std::string aux = "";
	// Use a while loop together with the getline() function to read the file line by line
	if (archivo.is_open()) {

		while (std::getline(archivo, Linea)) {
			// Output the text from the file
			if (Linea.rfind(token, 0) == 0) {
				while (archivo.is_open()) {
					archivo.close();
				}
				aux = Linea.replace(0, token.length(), "");
			}
		}
	}
	// Close the file
	while (archivo.is_open()) {
		archivo.close();
	}
	return aux;
}
std::string BuscarEnArchivo2(std::string token, std::string extension) {
	std::string Linea;

	std::ifstream archivo(ubicacion_combate + (jugador == ("FirstPlayer") ? "SecondPlayer":"FirstPlayer") + "." + extension);
	std::string aux = "";
	// Use a while loop together with the getline() function to read the file line by line
	if (archivo.is_open()) {

		while (std::getline(archivo, Linea)) {
			// Output the text from the file
			
			if (Linea.rfind(token, 0) == 0) {
				while (archivo.is_open()) {
					archivo.close();
				}
				aux = Linea.replace(0, token.length(), "");
			}
		}
	}
	// Close the file
	while (archivo.is_open()) {
		archivo.close();
	}
	return aux;
}

std::string BuscarTokenEntrada(std::string ruta,std::string token) {
	std::string Linea;
	std::ifstream archivo(ubicacion_combate+ruta);

	// Use a while loop together with the getline() function to read the file line by line
	if (archivo.is_open()) {

		while (std::getline(archivo, Linea)) {
			// Output the text from the file
			if (Linea.rfind(token, 0) == 0) {
				while (archivo.is_open()) {
					archivo.close();
				}
				return Linea.replace(0, token.length(), "");
			}
		}
	}
	// Close the file
	while (archivo.is_open()) {
		archivo.close();
	}
	return "";
}
void Limpiar_Pantalla() {
	system("cls");
}
 
void EliminarLinea(std::string token, std::string extension) {
	std::string Linea;
	std::string texto = "";
	std::string ubi = ubicacion_combate + jugador + "." + extension;
	std::ifstream archivo(ubi);
	if (archivo.is_open()) {
		while (std::getline(archivo, Linea)) {
			//if (Linea == (token)) {
			if (Linea.rfind(token, 0) == 0) {
				texto = texto;
			}
			else {
				texto = texto + (texto == ("") ? "" : "\n") + Linea;
			}
		}
	}
	while (archivo.is_open()) {
		archivo.close();
	}
	/*reescribir*/
	std::ofstream archivo1;
	archivo1.open(ubi);
	archivo1 << texto;
	while (archivo1.is_open()) {
		archivo1.close();
	}
}
void EliminarLinea2(std::string token, std::string extension) {
	std::string Linea;
	std::string texto = "";
	std::string ubi = ubicacion_combate + (jugador == ("FirstPlayer") ? "SecondPlayer" : "FirstPlayer") + "." + extension;
	std::ifstream archivo(ubi);
	if (archivo.is_open()) {
		while (std::getline(archivo, Linea)) {
			//if (Linea == (token)) {
			if (Linea.rfind(token, 0) == 0) {
				texto = texto;
			}
			else {
				texto = texto + (texto == ("") ? "" : "\n") + Linea;
			}
		}
	}
	while (archivo.is_open()) {
		archivo.close();
	}
	/*reescribir*/
	std::ofstream archivo1;
	archivo1.open(ubi);
	archivo1 << texto;
	while (archivo1.is_open()) {
		archivo1.close();
	}
}

void completar_tablero(CTablero &tablero,std::string &jugadas_inicio) { 
	int inicio_letras = 65;
	int fin_letras = 74;
	int naves_a = 0;
	int naves_b = 0;
	int naves_s = 0;
	int naves_t = 0;
	while (naves_a < tablero.A_maximo) {
		time_t ttNow = time(0);
		tm* ptmNow;
#pragma warning(suppress : 4996)
		ptmNow = localtime(&ttNow);
		int secundo = ptmNow->tm_sec;
		std::string cade = char((secundo + rand()) % (fin_letras - inicio_letras + 1) + inicio_letras) + std::to_string((secundo + rand()) % (10 - 1 + 1) + 1);
		cade = cade + (((secundo + rand()) % (2 - 1 + 1) + 1) == 1 ? "-V" : "-H");

		if (tablero.Crear_Nave(CNave("A-" + cade)) == 1) {
			naves_a++; 
				jugadas_inicio = jugadas_inicio + "PLACE_FLEET="+ "A-" + cade +"\n";
		}
	}

	while (naves_b < tablero.B_maximo) {
		time_t ttNow = time(0);
		tm* ptmNow;
#pragma warning(suppress : 4996)
		ptmNow = localtime(&ttNow);
		int secundo = ptmNow->tm_sec;
		std::string cade = char((secundo + rand()) % (fin_letras - inicio_letras + 1) + inicio_letras) + std::to_string((secundo + rand()) % (10 - 1 + 1) + 1);
		cade = cade + (((secundo + rand()) % (2 - 1 + 1) + 1) == 1 ? "-V" : "-H");

		if (tablero.Crear_Nave(CNave("B-" + cade)) == 1) {
			naves_b++;
			jugadas_inicio = jugadas_inicio + "PLACE_FLEET=" + "B-" + cade + "\n";
		}
	}

	while (naves_s < tablero.S_maximo) {
		time_t ttNow = time(0);
		tm* ptmNow;
#pragma warning(suppress : 4996)
		ptmNow = localtime(&ttNow);
		int secundo = ptmNow->tm_sec;
		std::string cade = char((secundo + rand()) % (fin_letras - inicio_letras + 1) + inicio_letras) + std::to_string((secundo + rand()) % (10 - 1 + 1) + 1);
		cade = cade + (((secundo + rand()) % (2 - 1 + 1) + 1) == 1 ? "-V" : "-H");

		if (tablero.Crear_Nave(CNave("S-" + cade)) == 1) {
			naves_s++;
			jugadas_inicio = jugadas_inicio + "PLACE_FLEET=" + "S-" + cade + "\n";
		}
	}

	while (naves_t < tablero.T_maximo) {
		time_t ttNow = time(0);
		tm* ptmNow;
#pragma warning(suppress : 4996)
		ptmNow = localtime(&ttNow);
		int secundo = ptmNow->tm_sec;
		std::string cade = char((secundo + rand()) % (fin_letras - inicio_letras + 1) + inicio_letras) + std::to_string((secundo + rand()) % (10 - 1 + 1) + 1);
		cade = cade + (((secundo + rand()) % (2 - 1 + 1) + 1) == 1 ? "-V" : "-H");

		if (tablero.Crear_Nave(CNave("T-" + cade)) == 1) {
			naves_t++;
			jugadas_inicio = jugadas_inicio + "PLACE_FLEET=" + "T-" + cade + "\n";
		}
	}	
}

void main() {

	std::string token_ = "";
	int player = 1;

	std::cout << "INGRESE EL NOMBRE DEL EQUIPO: ";
	std::cin >> equipo;

	std::cout << "Player (1 o 2): ";
	std::cin >> player;

	if (player == 1) {
		jugador = "FirstPlayer";
	}
	else {
		jugador = "SecondPlayer";
	}
	/*GUARDAR NOMBRE DE EQUIPO*/
	GuardarJugada("", "HANDSHAKE="+ equipo, "in");
	while (token_ == (""))
	{
		token_ = BuscarEnArchivo("TOKEN=", "out");
	}

	CTablero tableroEnemigo = CTablero();
	CTablero tablero = CTablero();
	//tablero.Crear_Nave(CNave("A-E4-H"));
	//tablero.Crear_Nave(CNave("B-E5-H"));
	//tablero.Crear_Nave(CNave("B-E6-H"));
	//tablero.Crear_Nave(CNave("S-E7-H"));
	//tablero.Crear_Nave(CNave("S-E8-H"));
	//tablero.Crear_Nave(CNave("S-A8-H"));
	//tablero.Crear_Nave(CNave("T-E9-H"));
	//tablero.Crear_Nave(CNave("T-E10-H"));
	//tablero.Crear_Nave(CNave("T-A1-H"));
	//tablero.Crear_Nave(CNave("T-B2-H"));

	std::string jugadas_inicio = "";
	jugadas_inicio=jugadas_inicio +"TOKEN="+ token_ + "\n";
	completar_tablero(tablero, jugadas_inicio);
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=A-E4-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=B-E5-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=B-E6-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=S-E7-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=S-E8-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=S-A8-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=T-E9-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=T-E10-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=T-A1-H\n";
	//jugadas_inicio=jugadas_inicio+"PLACE_FLEET=T-B2-H\n";
	GuardarJugada("", jugadas_inicio, "in");

	std::cout << "- Battleship Game -" << std::endl << std::endl;
	tableroEnemigo.Mostrar_Matriz("ENEMIGO");
	tablero.Mostrar_Matriz(equipo);
	std::string notificacion = "";
	std::string notificacion2 = "";
	std::string ataque_contrario = "";
	std::string aux = "";

	int numero_disparos = 0;
	int pausa = 500;
	int aux_pri_atq = 1;

	while (numero_disparos<100)
	{ 
		std::string ataque; 
		while (notificacion == ("WAIT FOR YOUR TURN") or notificacion == (""))
		{ 
			notificacion = BuscarEnArchivo("NOTIFICATION=", "not");
			//aux=
			ataque_contrario = BuscarEnArchivo("ATTACK=", "not");
			notificacion2 = BuscarEnArchivo2("NOTIFICATION=", "not");
			if (ataque_contrario != ("") and ataque_contrario.substr(ataque_contrario.find("-") + 1) != ("FAILED") and notificacion2 == ("YOUR TURN")) {
				int posicion_i = ataque_contrario.find("-");
				std::string atq = ataque_contrario.substr(0, posicion_i);
				std::string danio = ataque_contrario.substr(posicion_i + 1); 
				tablero.RegistrarAtaque(atq, danio); 
				Limpiar_Pantalla();
				std::cout << "- Battleship Game -" << std::endl << std::endl;
				tableroEnemigo.Mostrar_Matriz("ENEMIGO");
				tablero.Mostrar_Matriz(equipo);
			}
			aux_pri_atq = 1;
			Sleep(pausa);
		}
		 
		if ((notificacion) == ("YOUR TURN")) 
		{  
			ataque_contrario = BuscarEnArchivo2("ATTACK=", "not");
			if (ataque_contrario != ("") and aux_pri_atq==1) {
				int posicion_i = ataque_contrario.find("-");
				std::string atq = ataque_contrario.substr(0, posicion_i);
				std::string danio = ataque_contrario.substr(posicion_i + 1); 
				tablero.RegistrarAtaque(atq, danio); 
				Sleep(pausa);
			}
			ataque = tableroEnemigo.DisparoAutomatico();
			GuardarJugada(("TOKEN=" + token_), "ATTACK=" + ataque, "in");
			Sleep(pausa);Sleep(pausa);
			
			std::string mensaje=BuscarEnArchivo("MESSAGE=", "out");
			if (mensaje != ("FAILED")) { 
				if (mensaje == ("DAMAGED")) {
					tableroEnemigo.RegistrarAtaque(ataque,"Y");
				}
				else if(mensaje == ("DESTROYED")) 
				{
					tableroEnemigo.RegistrarAtaque(ataque, "X");
				}
			}
			else if (mensaje == ("FAILED")) {
				tableroEnemigo.RegistrarAtaque(ataque, "*");
				notificacion = BuscarEnArchivo("NOTIFICATION=", "not");
			}
			aux_pri_atq = 0;
		}
		else if (notificacion == ("WAIT FOR YOUR TURN") or notificacion == (""))
		{
			ataque_contrario = BuscarEnArchivo("ATTACK=", "not");
			if (ataque_contrario != ("")) {
				int posicion_i = ataque_contrario.find("-");
				std::string atq = ataque_contrario.substr(0, posicion_i);
				std::string danio = ataque_contrario.substr(posicion_i + 1);
				tablero.RegistrarAtaque(atq, danio);
			}
			}
		ataque_contrario = "";
		ataque = "";
		Limpiar_Pantalla();
		std::cout << "- Battleship Game -" << std::endl << std::endl;
		tableroEnemigo.Mostrar_Matriz("ENEMIGO");
		tablero.Mostrar_Matriz(equipo);
	}
	std::cout << "";
}