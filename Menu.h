#ifndef MENU_H_
#define MENU_H_
#include <curses.h>

class Menu
{
	private:
		static int MAX_X;
		static int MAX_Y;
		static int contadorSalida;
		static const int MAX;

	public:
		virtual ~Menu(){}
		void setContadorSalida(int a) {contadorSalida = a;}
		static int getMAX_X() {return MAX_X;}
		static int getMAX_Y() {return MAX_Y;}
		static int getContadorSalida() {return contadorSalida;}
		static int getMAX() {return MAX;}

		void tamanyoTerminal();
};


#endif