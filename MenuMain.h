#ifndef MENUMAIN_H_
#define MENUMAIN_H_

#include "Menu.h"
#include "Usuario.h"
#include "MenuInicio.h"
#include "MenuIniciarSesion.h"
#include "MenuRegistrarse.h"
#include "MenuPlayer.h"
#include "Clasico.h"
#include "Supervivencia.h"
#include "RankingSupervivencia.h"
#include "RankingClasico.h"
#include "LecturaEscrituraFichero.h"

class MenuMain : public Menu
{
	public:
		MenuMain();
		virtual ~MenuMain(){}
		void menuPrincipal ();
		void liberarMemoriaMenuMain (int *size, Usuario* arrayUsers);		
};

#endif