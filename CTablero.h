#pragma once
#include <string>
#include <iostream> 
#include "CNave.h"
#include <string> 
#include <fstream>

class CTablero
{
public: 
	const int filas = 11;
	const int columnas = 11;
	std::string matriz[11][11];
	CNave NAVES[10];
	int total_naves = 0;
	int A_maximo = 1;
	int B_maximo = 2;
	int S_maximo = 3;
	int T_maximo = 4;

	int A_restantes = 1;
	int B_restantes = 2;
	int S_restantes = 3;
	int T_restantes = 4;
	std::string n_jugador = "";


	int ultimo_disparo_x = 0;
	int ultimo_disparo_y = 0;

	CTablero() {
		Iniciar_Matriz(); 
	}

	void Iniciar_Matriz() {

		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				if (i == 0 and j > 0) {
					matriz[i][j] = ('A' + (j - 1));
				}
				else if (j == 0 and i > 0) {
					matriz[i][j] = std::to_string(i) + (i >= 10 ? "":" ");
				}
				else if (i > 0) {
					matriz[i][j] = ".";
				}
				else if (i == 0 and j == 0) {
					matriz[i][j] = "  ";
				}
			}
		}
	}

	void Mostrar_Matriz() {
		std::cout << "Tablero de Jugador: " << n_jugador<<std::endl;
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				std::cout << matriz[i][j] << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Mostrar_Matriz(std::string NombreZona) { 
		std::cout << "Zona Equipo: " << NombreZona << std::endl;
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				std::cout << matriz[i][j] << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

 
	void IngresarNave(CNave nave) {
		if (nave.horientacion._Equal("V")) {
			for (int i = nave.get_x(); i < nave.get_x() + nave.get_largo(); i++)
			{
				matriz[i][nave.get_y()] = nave.tipo_nave;
			}
		}else 
		if (nave.horientacion._Equal("H")) {
			for (int i = nave.get_y(); i < nave.get_y() + nave.get_largo(); i++)
			{ 
				matriz[nave.get_x()][i] = nave.tipo_nave;
			}
		}
		 
	}

	int Crear_Nave(CNave nave) {
		int largo = 0;
		int bandera1 = 1;
		if (nave.tipo_nave._Equal("A")) {
			nave.largo = 4;
		}
		else if (nave.tipo_nave._Equal("B")) {
			nave.largo = 3;
		}
		else if (nave.tipo_nave._Equal("S")) {
			nave.largo = 2;
		}
		else if (nave.tipo_nave._Equal("T")) {
			nave.largo = 1;
		} 
		if (nave.horientacion._Equal("V")) {
			for (int i = nave.x;i < nave.x + nave.largo;i++)
			{
				if (!matriz[i][nave.y] ._Equal(".")) {
					bandera1 = 0;
				}
			}
		}
		else if (nave.horientacion._Equal("H")) {
			for (int i = nave.y;i < (nave.y + nave.largo);i++)
			{
				if (!matriz[nave.x][i]._Equal(".")) {
					bandera1 = 0;
				}
			}
		}

		if (bandera1 == 1) {
			NAVES[total_naves]= nave;
			total_naves = total_naves + 1;
			IngresarNave(nave);
		}
		return bandera1;
	}
	void RegistrarAtaque(std::string ataque) {
		CNave aux = CNave();
		std::string sy = ataque.substr(0, 1);
		std::string sx = ataque.substr(1);
		int x = stoi(sx);
		int y = aux.Letra_a_Numero(sy);

		matriz[x][y] = "X";
	}
 
	 void RegistrarAtaque(std::string ataque, std::string caracter) {
		 CNave aux = CNave();
		 std::string sy = ataque.substr(0, 1);
		 std::string sx = ataque.substr(1);
		 int x = stoi(sx);
		 int y = aux.Letra_a_Numero(sy);

		 if (caracter._Equal("DESTROYED")) {
			 caracter = "X";
		 }else if (caracter._Equal("DAMAGED")) {
			 caracter = "Y";
		 }else if (caracter._Equal("FAILED")) {
			 caracter = "*";
		 }

		 matriz[x][y] = caracter;
	 } 


	 std::string DisparoAutomatico() {
		 int x = 0;
		 int y = 0;
		 int x_min = 1;
		 int y_min = 1;
		 int x_max = filas-1;
		 int y_max = columnas-1; 
		 time_t ttNow = time(0);
		 tm* ptmNow;
         #pragma warning(suppress : 4996)
		 ptmNow = localtime(&ttNow);
		 int secundo = ptmNow->tm_sec;
		 if (ultimo_disparo_x == 0 and ultimo_disparo_y == 0) {
			 int  aleatorio, DESDE = 1, HASTA = 10;
			 bool prueba = true;
			 while (prueba)
			 {
				 x = (rand()+ secundo) % (HASTA - DESDE + 1) + DESDE;
				 y = (rand()+ secundo) % (HASTA - DESDE + 1) + DESDE;
				 if (matriz[x][y]._Equal(".")) {
					 prueba = false;
				 }
			 } 
		 }
		 if (matriz[ultimo_disparo_x][ultimo_disparo_y]._Equal("*"))
		 {
			 int  aleatorio, DESDE = 1, HASTA = 10;
			 bool prueba = true;
			 while (prueba)
			 {
				 x = (rand() + secundo) % (HASTA - DESDE + 1) + DESDE;
				 y = (rand() + secundo) % (HASTA - DESDE + 1) + DESDE;
				 if (matriz[x][y]._Equal(".")) {
					 prueba = false;
				 }
			 } 
		 }
		 if (matriz[ultimo_disparo_x][ultimo_disparo_y]._Equal("X") or matriz[ultimo_disparo_x][ultimo_disparo_y]._Equal("Y")) {
			 int x_aux = 0;
			 int y_aux = 0;
			 /*
			 Estrategi Buscar Libre al rededor izquierda,derecha,arriba,abajo del ultimo disparo
			 */
			 if (x_aux == 0 and y_aux == 0 and ultimo_disparo_x - 1 >= x_min) {
				 if (matriz[ultimo_disparo_x - 1][ultimo_disparo_y]._Equal(".")) {
					 x_aux = ultimo_disparo_x - 1;
					 y_aux = ultimo_disparo_y;
				 }
			 }
			 if (x_aux == 0 and y_aux == 0 and ultimo_disparo_x + 1 <= x_max) {
				 if (matriz[ultimo_disparo_x + 1][ultimo_disparo_y]._Equal(".")) {
					 x_aux = ultimo_disparo_x + 1;
					 y_aux = ultimo_disparo_y;
				 }
			 }
			 if (x_aux == 0 and y_aux == 0 and ultimo_disparo_y - 1 >= y_min) {
				 if (matriz[ultimo_disparo_x][ultimo_disparo_y + 1]._Equal(".")) {
					 y_aux = ultimo_disparo_y - 1;
					 x_aux = ultimo_disparo_x;
				 }
			 }
			 if (x_aux == 0 and y_aux == 0 and ultimo_disparo_y + 1 <= y_max) {
				 if (matriz[ultimo_disparo_x][ultimo_disparo_y+1]._Equal(".")) {
					 y_aux = ultimo_disparo_y + 1;
					 x_aux = ultimo_disparo_x;
				 }
			 }

			 /*si x aux y aux son 0 se debe buscar nuevamente otro punto al azar*/
			 if (x_aux==0 and y_aux==0)
			 {
				 int  aleatorio, DESDE = 1, HASTA = 10;
				 bool prueba = true;
				 while (prueba)
				 {
					 x = rand() % (HASTA - DESDE + 1) + DESDE;
					 y = rand() % (HASTA - DESDE + 1) + DESDE;
					 if (matriz[x][y]._Equal(".")) {
						 prueba = false;
					 }
				 }
			 }
			 else
			 {
				 x = x_aux;
				 y = y_aux;
			 }
		 }

		 std::cout << Numero_a_Letra(y) + std::to_string(x)<<std::endl;
		 ultimo_disparo_x=x;
		 ultimo_disparo_y=y;

		 return Numero_a_Letra(y) + std::to_string(x);
	 }
	 
	 std::string Numero_a_Letra(int numero) {
		 char letra(64 + numero);		 
		 std::string letra_s = "";
		 letra_s = letra;
		 return letra_s;
	 }

	 int Letra_a_Numero(std::string a) {
		 int aux = 0;
		 int ia = (int)a.at(0);
		 int iaa = (int)'a';
		 int iA = (int)'A';

		 if (a.at(0) >= 'a' and a.at(0) <= 'z') {
			 aux = 1 + (int)a.at(0) - (int)'a';
		 }
		 else if (a.at(0) >= 'A' and a.at(0) <= 'Z') {
			 aux = 1 + (int)a.at(0) - (int)'A';
		 }
		 return aux;
	 }
};