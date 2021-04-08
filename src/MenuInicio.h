#ifndef MENUINICIO_H_
#define MENUINICIO_H_

#include "Menu.h"
#include "Usuario.h"

class MenuInicio : public Menu
{
	public:
		MenuInicio(){}
		virtual ~MenuInicio(){}
		int menuInicio();
		void liberarMemoriaMenuInicio(const char** opciones, WINDOW* inicio);
};

#endif