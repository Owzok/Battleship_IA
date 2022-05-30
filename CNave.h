#pragma once
#include <iostream>
#include <conio.h>
#include <string>
class CNave
{
public:

	std::string nave_coordenada;

	int x;
    int y;
	int largo;
	std::string horientacion;
	std::string tipo_nave;
	CNave() {

	}

	CNave(int x, int y, int largo, std::string horientacion, std::string tipo_nave) {
		this->x = x;
		this->y = y;
		this->largo = largo;
		this->horientacion = horientacion;
		this->tipo_nave = tipo_nave; 
	}
	CNave(std::string nave_coordenada) {
		this->nave_coordenada = nave_coordenada; 
		obtenerDatos(nave_coordenada);
	}

	void obtenerDatos(std::string nave_coordenada) {
	//PLACE_FLEET=A-A10-H 
		//        0123456
	//PLACE_FLEET=A-A1-H 
		//        012345
		if (nave_coordenada.length()==6) {
			set_tipo_nave(nave_coordenada.substr(0, 1));
			set_y(Letra_a_Numero(nave_coordenada.substr(2, 1)));
			set_x (std::stoi(nave_coordenada.substr(3, 1)));
			set_horientacion(nave_coordenada.substr(5, 1));
		}
		else if(nave_coordenada.length() == 7) { 
			set_tipo_nave(nave_coordenada.substr(0, 1));
			set_y(Letra_a_Numero(nave_coordenada.substr(2, 1))); 
			set_x(std::stoi((nave_coordenada.substr(3, 2))));
			set_horientacion(nave_coordenada.substr(6, 1));
		}
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

	int get_x() {
		return this->x;
	}
	int get_y() {
		return this->y;
	}
	int get_largo() {
		return this->largo;
	}
	std::string get_horientacion() {
		return this->horientacion;
	}
	std::string get_tipo_nave() {
		return this->tipo_nave;
	}  

	void set_x(int x) {
		 this->x=x;
	}
	void set_y(int y) {
		this->y = y;
	}
	void set_largo(int largo) {
		this->largo = largo;
	}
	void set_horientacion(std::string horientacion) {
		this->horientacion = horientacion;
	}
	void set_tipo_nave(std::string tipo_nave){
		this->tipo_nave = tipo_nave;
	}

};

