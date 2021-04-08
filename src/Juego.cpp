#include "Juego.h"

Juego::Juego()
{
	initscr();
	getmaxyx(stdscr, this->alturaTerminal, this->anchuraTerminal);
}

WINDOW* Juego::mostrarPartidaGuardada()
{
	int alturaVentanaS = this->BAJO+3;
	int anchuraVentanaS = this->DERECHA+6;
	WINDOW* partidaGuardada = newwin(3, 20,this->alturaTerminal/2-1.5,this->anchuraTerminal/2-7.5);
	refresh();
	box(partidaGuardada,0,0);
	mvwprintw(partidaGuardada,1,1, "PARTIDA GUARDADA");
	wrefresh(partidaGuardada);
	return partidaGuardada;
}

WINDOW* Juego::mostrarPartidaPausada()
{
    int alturaVentanaS = this->BAJO+3;
    int anchuraVentanaS = this->DERECHA+6;
    WINDOW* partidaPausada = newwin(6, 40,this->alturaTerminal/2-1.5,this->anchuraTerminal/2-20);
    refresh();
    box(partidaPausada,0,0);
    mvwprintw(partidaPausada,1,10, "PARTIDA PAUSADA");
    mvwprintw(partidaPausada,2,7, "Pulse p para continuar...");
    mvwprintw(partidaPausada,3,7, "Pulse g para guardar...");
    mvwprintw(partidaPausada,4,7, "Pulse s para salir...");
    wrefresh(partidaPausada);
    return partidaPausada;
}

WINDOW* Juego::mostrarInfoPartidaGuardada()
{
	int alturaVentanaS = this->BAJO+3;
	int anchuraVentanaS = this->DERECHA+6;
	WINDOW* partidaGuardada = newwin(4, 40,this->alturaTerminal/2-2,this->anchuraTerminal/2-20);
	refresh();
	box(partidaGuardada,0,0);
	mvwprintw(partidaGuardada,1,1, "Se ha detectado una Partida Guardada:");
	mvwprintw(partidaGuardada,2,1,"Que desea hacer?");;
	wrefresh(partidaGuardada);
	wclear(partidaGuardada);
	return partidaGuardada;
}

int Juego::menuPartidaGuardada()
{
	WINDOW* salida = newwin(this->getAlturaTerminal()/5,this->getAnchuraTerminal()-20,this->getAlturaTerminal()-(this->getAlturaTerminal()/5)-1, this->getIzquierda()+1);
    refresh();
    box(salida,0,0);
    keypad(salida, TRUE);

    const char** opciones = new const char*[2];
    for(int i=0; i<2; i++)
    {
    	opciones[i] = new char[20];
    }
    opciones[0] = "Continuar Partida";
    opciones[1] = "Nueva Partida";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
    	for(int i=0; i<2; i++)
    	{
    		if(i==seleccion)
    			wattron(salida, A_REVERSE);
    		mvwprintw(salida, i+1, 1, "%s", opciones[i]);
    		wattroff(salida, A_REVERSE);
    	}
    	wrefresh(salida);

    	eleccion = wgetch(salida);

    	switch(eleccion)
    	{
    		case KEY_UP:
    			seleccion--;
    			if(seleccion == -1)
    				seleccion = 0;
    			break;
    		case KEY_DOWN:
    			seleccion++;
    			if(seleccion == 2)
    				seleccion = 1;
    			break;
    		default:
    			break;
    	}
    	if(eleccion == 10)
    		break;
    }
    for(int i=0; i<2; i++)
    {
    	delete[] opciones[i];
    }
    delete[] opciones;

    wclear(salida);
    wrefresh(salida);
    delwin(salida);

    return seleccion;
}

int Juego::getAlto() const
{
	return this->ALTO;
}
void Juego::setAlto(int alto)
{
	this->ALTO = alto;
}
int Juego::getIzquierda() const
{
	return this->IZQUIERDA;
}
void Juego::setIzquierda(int izquierda)
{
	this->IZQUIERDA = izquierda;
}
int Juego::getBajo() const
{
	return this->BAJO;
}
void Juego::setBajo(int bajo)
{
	this->BAJO = bajo;
}
int Juego::getDerecha() const
{
	return this->DERECHA;
}
void Juego::setDerecha(int derecha)
{
	this->DERECHA = derecha;
}
int Juego::getAlturaTerminal() const
{
	return this->alturaTerminal;
}
void Juego::setAlturaTerminal(int altura)
{
	this->alturaTerminal = altura;
}
int Juego::getAnchuraTerminal() const
{
	return this->anchuraTerminal;
}
void Juego::setAnchuraTerminal(int anchura)
{
	this->anchuraTerminal = anchura;
}