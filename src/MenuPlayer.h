#ifndef MENUPLAYER_H_
#define MENUPLAYER_H_

#include "Menu.h"

class MenuPlayer : public Menu
{
	public:
		MenuPlayer(){}
		virtual ~MenuPlayer(){}
		int menuPlayer();
		void liberarMemoriaMenuPlayer(WINDOW* player, const char** opciones);
};

#endif