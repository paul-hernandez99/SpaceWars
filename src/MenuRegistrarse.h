#ifndef MENUREGISTRARSE_H_
#define MENUREGISTRARSE_H_

#include "Menu.h"
#include "Usuario.h"

class MenuRegistrarse : public Menu
{
	public:
		MenuRegistrarse(){}
		virtual ~MenuRegistrarse(){}
		void menuRegistrarse (Usuario *usuarios, int size);
		void liberarMemoriaMenuRegistrarse(WINDOW* registro, Usuario* usuariosActualizados, int size, char* userIntroduced, char* passIntroduced, char* passConfiIntroduced, float* initializeNull);
};
#endif