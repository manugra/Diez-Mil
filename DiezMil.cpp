// DiezMil.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>

#include <cstring>

#include <stdio.h>

#include <cstdlib>

#include <time.h>

#include <stdio.h>

#include <string>

#include <Windows.h>

using namespace std;

//DECLARACION DE FUNCIONES
void gotoxy(int x, int y);

int menu();

int numeroRandom();


void formaDeDado(int b);//El cuadrado

void dadito1(int a);
void dadito2(int a);
void dadito3(int a);
void dadito4(int a);
void dadito5(int a);
void dadito6(int a);

int jugadas(int tirada[6]);//Busca las jugadas que se formaron y devuelve la de mayor puntaje.
int indiceJugadas(int tirada[6]);

void game_over(string ganador, int rondas);

//FUNCION PRINCIPAL

int main() {

	srand(time(NULL));

	int menuMain;

	menuMain = menu();

	std::system("cls");


	int tirada[6];//Contiene los dados que salieron.
	string nombres[] = { "Juego de 1", "Juego de 5", "Trio 1", "Trio X", "Trio X++", "Trio 1 Ampliado", "Tres pares", "Escalera larga", "Sexteto" ,"Nula" };

	char jugador[25];



	int cr = 1;//Contador de rondas
	int puntos = 0;//Puntos de la ronda
	int puntos_totales = 0;



	int opcion1=1;//Si se lanza de nuevo o se termina la ronda.
	int menu_final = 1; //Si se juega de nuevo o se cierra el programa en el menu "game_over"

	while (menu_final == 1) {


		if (menuMain == 0) {
			std::system("cls");
			return 0; //Si elige salir se termina el programa
		}


		std::system("cls");

		std::cout << "----------------------------------------------------------------------------------\n";
		std::cout << "Ingrese su nombre(sin espacios): ";//SOLO PERMITE NOMBRES SIN ESPACIOS
		std::cin >> jugador;

		std::system("pause");
		std::system("cls");


		while (puntos_totales != 10000) {


			while (opcion1 == 1) {


				std::cout << "TURNO DE " << jugador; std::cout << "      |   RONDA N " << cr << "     " << endl; //POR ACA SE MUESTRA EL PUNTAJE(LINEA 138)
				std::cout << "-----------------------------------------------------------------------------------------------------------------";

				for (int i = 0; i < 6; i++)//TIRO LOS 6 DADOS
				{
					

					tirada[i] = numeroRandom();

					switch (tirada[i])
					{
					case(1): dadito1(i); break;//En la primer vuelta se imprimen en la primer posicion(i=0), en la segunda vuelta en la segunda posicion(i=1),etc.

					case(2): dadito2(i); break;

					case(3): dadito3(i); break;

					case(4): dadito4(i); break;

					case(5): dadito5(i); break;

					case(6): dadito6(i); break;

					default: std::cout << "ERROR";  return 0;
						break;
					}
				}
				std::cout << endl;
				puntos = jugadas(tirada);

				if (puntos == 0) {

					puntos_totales = 0; //Si no hay combinacion ganadora, el jugador pierde todos los puntos.
					std::cout << "\nJugada nula. Perdiste tus puntos acumulados. Lo siento campeon!";
				}
				puntos_totales += puntos;
				//std::cout << jugadas(tirada) << endl;
				//std::cout << puntos << endl;

				if (puntos_totales > 10000) puntos_totales -= puntos;

				gotoxy(43, 0); std::cout << "|    PUNTAJE TOTAL " << puntos_totales;

				gotoxy(0, 10); std::cout << "La jugada es " << nombres[indiceJugadas(tirada)] << "!  +" << puntos << "!" << endl;

				//int opcion1;//Si se lanza de nuevo o se termina la ronda.

				std::cout << "Lanzar de nuevo/Finalizar ronda(1/0): "; std::cin >> opcion1;


				if (opcion1 == 1) puntos_totales -= puntos;
				std::system("pause");
				std::system("cls");

			}

			std::system("cls");
			opcion1 = 1;

			cr++;

		}


		game_over(jugador, cr);

		std::cout << "\nJugar de nuevo/Salir del juego(1/0): "; cin >> menu_final;

		puntos_totales = 0;
		opcion1 = 1;
		cr = 1;
		std::system("cls");
	}
}//FIN DEL MAIN

//DEFINICION DE FUNCIONES

int jugadas(int tirada[6]) {//RECIBE COMO PARAMETRO EL ARRAY CON CADA UNO DE LOS DADOS LANZADOS

	int combinacion[9] = { 0 }; //Todas las jugadas. En cada indice sumo los puntos de su jugada correspondiente para despues buscar el mayor.
	int contador[6] = { 0 };//Cuenta cuantos dados hubo de cada valor.
	int mayorJugada = 0;//Guarda el elemento de mayor valor del array "combinacion".

	for (int i = 0; i < 6; i++)
	{
		if (tirada[i] == 1) contador[0]++;//Se suma uno al dado 1

		if (tirada[i] == 2) contador[1]++;//Se suma uno al dado 2

		if (tirada[i] == 3) contador[2]++;//etc.

		if (tirada[i] == 4) contador[3]++;

		if (tirada[i] == 5) contador[4]++;

		if (tirada[i] == 6) contador[5]++;

	}

	/****************Jugadas con el 1****************/
	if (contador[0] == 6) combinacion[8] = 10000;//Sexteto

	else if (contador[0] == 4 || contador[0] == 5) combinacion[5] = 2000;//Trio 1 ampliado

	else if (contador[0] == 3) combinacion[2] = 1000;//Trio 1


	else if (contador[0] == 2) combinacion[0] = 100 * 2;//Juego de 1

	else if (contador[0] == 1) combinacion[0] = 100;//Juego de 1
	/*************************************************/



	/**************Escalera Real**********************/
																					 
	int nAnt = tirada[0];															
	bool escalera = true; //Si cambia a false es que no hay escalera				
																					
	for (int i = 1; i <=6; i++)														
	{																				
		if (tirada[i] > nAnt && tirada[i] < tirada[i + 1]) nAnt = tirada[i];		
																					
		else escalera = false;																			 
	}																									 
																										 
	if (escalera) combinacion[7] = 1500;																 
	/*************************************************/													 
																										 
																										 
																										 
	/********************Trio X**********************/													 
	for (int i = 1; i < 6; i++)
	{
		if (contador[i] == 3) combinacion[3] = (i+1) * 100;
	}											 
	/************************************************/



	/******************Trio X++*********************/
	for (int i = 1; i < 6; i++)
	{
		if (contador[i] == 4 || contador[i] == 5) combinacion[4] = tirada[i] * 200;
	}
	/***********************************************/


	
	/****************Juego de 5********************/
	if (contador[4] == 1) combinacion[1] = 50;

	else if (contador[4] == 2) combinacion[1] = 50 * 2;
	/**********************************************/



	/****************Tres Pares*********************/
	int cp = 0;//Contador de pares.
	bool seisIguales = false;
	

	for (int i = 0; i < 5; i++)
	{
		if (contador[i] == 2)
		{
			cp++;
			
		}
		else if (contador[i] == 6)
		{
			seisIguales = true;
		}

		if (cp == 3 || seisIguales == true) combinacion[6] = 1000;

	}
	/*************************************************/

	for (int i = 0; i < 9; i++)
	{
		if (combinacion[i] > mayorJugada)
		{
			mayorJugada = combinacion[i];

		}
	}

	return mayorJugada;
}

int indiceJugadas(int tirada[6]) {

	int combinacion[9] = { 0 }; //Todas las jugadas. En cada indice sumo los puntos de su jugada correspondiente para despues buscar el mayor.
	int contador[6] = { 0 };//Cuenta cuantos dados hubo de cada valor.
	int mayorJugada = 0;//Guarda el elemento de mayor valor del array "combinacion".

	for (int i = 0; i < 6; i++)
	{
		if (tirada[i] == 1) contador[0]++;//Se suma uno al dado 1

		if (tirada[i] == 2) contador[1]++;//Se suma uno al dado 2

		if (tirada[i] == 3) contador[2]++;//etc.

		if (tirada[i] == 4) contador[3]++;

		if (tirada[i] == 5) contador[4]++;

		if (tirada[i] == 6) contador[5]++;

	}

	/****************Jugadas con el 1****************/
	if (contador[0] == 6) combinacion[8] = 10000;//Sexteto

	else if (contador[0] == 4 || contador[0] == 5) combinacion[5] = 2000;//Trio 1 ampliado

	else if (contador[0] == 3) combinacion[2] = 1000;//Trio 1


	else if (contador[0] == 2) combinacion[0] = 100 * 2;//Juego de 1

	else if (contador[0] == 1) combinacion[0] = 100;//Juego de 1
	/*************************************************/



	/**************Escalera Real**********************/

	int nAnt = tirada[0];
	bool escalera = true; //Si cambia a false es que no hay escalera

	for (int i = 1; i < 5; i++)
	{
		if (tirada[i] > nAnt && tirada[i] < tirada[i + 1]) nAnt = tirada[i];

		else escalera = false;
	}

	if (escalera) combinacion[7] = 1500;
	/*************************************************/



	/********************Trio X**********************/
	for (int i = 1; i < 6; i++)
	{
		if (contador[i] == 3) combinacion[3] = tirada[i] * 100;
	}
	/************************************************/



	/******************Trio X++*********************/
	for (int i = 1; i < 6; i++)
	{
		if (contador[i] == 4 || contador[i] == 5) combinacion[4] = tirada[i] * 200;
	}
	/***********************************************/



	/****************Juego de 5********************/
	if (contador[4] == 1) combinacion[1] = 50;

	else if (contador[4] == 2) combinacion[1] = 50 * 2;
	/**********************************************/



	/****************Tres Pares*********************/
	int cp = 0;//Contador de pares.
	bool seisIguales = false;


	for (int i = 0; i < 5; i++)
	{
		if (contador[i] == 2)
		{
			cp++;

		}
		else if (contador[i] == 6)
		{
			seisIguales = true;
		}

		if (cp == 3 || seisIguales == true) combinacion[6] = 1000;

	}
	/*************************************************/
	int indiceMayor=9;//Guarda el indice de la combinacion con valor mas alto.

	for (int i = 0; i < 9; i++)
	{
		if (combinacion[i] > mayorJugada)
		{
			mayorJugada = combinacion[i];
			indiceMayor = i;

		}
	}


	return indiceMayor;
}


int menu() {
	int opcion;
	do {
		gotoxy(50, 2);  std::cout << "DIEZ MIL";
		gotoxy(4, 5); std::cout << "1.Modo un Jugador";
		gotoxy(4, 6); std::cout << "0.Salir";

		for (int y = 1; y < 20; y++)
		{
			gotoxy(0, y); printf("%c", 186);
			gotoxy(115, y); printf("%c", 186);
		}


		for (int x = 1; x < 115; x++) //Lineas Horizontales

		{
			gotoxy(0, 0); printf("%c", 201);//Esquina superior izquierda
			gotoxy(x, 0); printf("%c", 205); //Linea que va a lo largo por arriba
			gotoxy(115, 0); printf("%c", 187);//Esquina superior derecha

			//Hasta aca la linea de arriba

			gotoxy(0, 20); printf("%c", 200);
			gotoxy(x, 20); printf("%c", 205);
			gotoxy(115, 20); printf("%c", 188);
		}

		std::cout << "    Un jugador/salir(1/0): ";
		std::cin >> opcion;

		if (opcion == 1) return 1;
		else return 0;

	}

	while (opcion!=0);
	
	return opcion;
}



void game_over(string jugador, int rondas) {

	gotoxy(48, 4); std::cout << "FIN DEL JUEGO!";

	gotoxy(4, 7); std::cout << "1." << jugador << " : " << rondas << " RONDAS";

	for (int y = 1; y < 20; y++)
	{
		gotoxy(0, y); printf("%c", 186);
		gotoxy(115, y); printf("%c", 186);
	}

	for (int x = 1; x < 115; x++) //Lineas Horizontales

	{
		gotoxy(0, 0); printf("%c", 201);//Esquina superior izquierda
		gotoxy(x, 0); printf("%c", 205); //Linea que va a lo largo por arriba
		gotoxy(115, 0); printf("%c", 187);//Esquina superior derecha

		//Hasta aca la linea de arriba

		gotoxy(0, 20); printf("%c", 200);
		gotoxy(x, 20); printf("%c", 205);
		gotoxy(115, 20); printf("%c", 188);
	}

}



int numeroRandom() {

	return rand() % 6 + 1;;
}



void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}



void formaDeDado(int b) {
	for (int i = 0; i < 10; i++)//Linea Horizontal
	{
		gotoxy(i+12*b, 3); printf("%c", 220);
		gotoxy(i+12*b, 7); printf("%c", 220);

	}


	for (int i = 4; i < 8; i++) //Linea vertical
	{
		gotoxy(0+12*b, i); printf("%c", 219);
		gotoxy(9+12*b, i);  printf("%c", 219);
	}
} 

/// SI TIENE dadito1, dadito2 o dadito3 NO HACE FALTA USAR formaDeDado!!


//EL PARAMETRO int a QUE RECIBEN LOS DADOS ES EN QUE POSICION VAN A MOSTRARSE EN LA PANTALLA
void dadito1(int a) {

	gotoxy(4+12*a, 5); printf("%c", 254);//Puntito del centro

	formaDeDado(a);
}


void dadito2(int a) {

	gotoxy(7+12*a, 6); printf("%c", 254);//Puntito esquina inferior derecha
	gotoxy(2+12*a, 4); printf("%c", 254);//Puntito esquina superior izquierda

	formaDeDado(a);
}


void dadito3(int a) {

	dadito1(a);
	dadito2(a);

}


void dadito4(int a) {

	gotoxy(2+12*a, 6); printf("%c", 254);//Puntito esquina inferior izquierda
	gotoxy(7+12*a, 4); printf("%c", 254);//Puntito esquina superior derecha

	dadito2(a);

}


void dadito5(int a) {
	
	dadito1(a);
	dadito4(a);
}


void dadito6(int a) {

	gotoxy(2+12*a, 5); printf("%c", 254);
	gotoxy(7+12*a, 5); printf("%c", 254);

	dadito4(a);

}
