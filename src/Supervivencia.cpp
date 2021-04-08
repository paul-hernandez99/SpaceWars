#ifdef _WIN32
	#include <windows.h>

	void sleepS(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#else
	#include <unistd.h>

	void sleepS(unsigned int milliseconds)
	{
		usleep(milliseconds * 1000);
	}
#endif

#include "Supervivencia.h"
#include <stdlib.h>

const int Supervivencia::MAX_AST = 15;
const int Supervivencia::MAX_EXTRA = 5;
const int Supervivencia::MAX_LENGHT = 20;

void Supervivencia::pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<*num_ast; i++)
    {
    	if(asteroides[i].getTipo() == 0)
    		pintarAsteroideVertical(ventana, &asteroides[i]);
    	else
    		pintarAsteroideHorizontal(ventana, &asteroides[i]);
    }
}

void Supervivencia::subirNivel(Asteroide* asteroides, int* num_ast)
{
	if(*num_ast < MAX_AST)
	{
		asteroides[*num_ast].setX(this->getIzquierda());
		asteroides[*num_ast].setY(rand()%(this->getBajo()-this->getAlto()+1) + this->getAlto());
		asteroides[*num_ast].setTipo(1);
		(*num_ast)++;

		mostrarNivel(num_ast);
	}
}

void Supervivencia::mostrarGameOver()
{
	WINDOW* gameOver = newwin(3, 11,this->getAlturaTerminal()/2-1.5,this->getAnchuraTerminal()/2-5.5);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,1, 1);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	wclear(gameOver);
	delwin(gameOver);
}

int Supervivencia::menuSalida()
{
	WINDOW* salida = newwin(this->getAlturaTerminal()/5,this->getDerecha()+6, this->getBajo()+5, this->getIzquierda()+3 );
    refresh();
    box(salida,0,0);
    keypad(salida, TRUE);

    const char** opciones = new const char*[2];
    for(int i=0; i<2; i++)
    {
    	opciones[i] = new char[MAX_LENGHT];
    }
    opciones[0] = "Jugar otra vez";
    opciones[1] = "Menu";

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
	wclear(salida);
	wrefresh(salida);
	delwin(salida);
	return seleccion;
}

WINDOW* Supervivencia::mostrarInfo()
{
	WINDOW* info = newwin(this->getAlturaTerminal()/3,this->getAnchuraTerminal()/1.7,this->getAlturaTerminal()/2-this->getAlturaTerminal()/7.4,this->getAnchuraTerminal()/2 - this->getAnchuraTerminal()/3.4);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides (O) no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las fleclas");;
	mvwprintw(info,3,1,"Hay 15 niveles distintos");
	mvwprintw(info,4,1,"Existen vidas Extras (X)");
	mvwprintw(info,5,1,"Para guardar la partida pulsa g.");
	mvwprintw(info,6,1,"Para pausar la partida pulsa p.");
	mvwprintw(info,7,1,"Para salir pulsa s.");
	mvwprintw(info,8,1,"El juego esta a punto de empezar...");
	wrefresh(info);
	return info;
}

WINDOW* Supervivencia::mostrarJuego()
{
	WINDOW* ventana = newwin(this->getBajo()+3, this->getDerecha()+6, this->getAlto(), this->getIzquierda()+3);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}
void Supervivencia::nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
	asteroide->setY(this->getAlto()-3);
}

void Supervivencia::nuevoAsteroideHorizontal(Asteroide* asteroide)
{
	asteroide->setX(this->getIzquierda()-2);
	asteroide->setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
}

int Supervivencia::choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	if((asteroide->getX() >= nave->getX()) && (asteroide->getX() <= nave->getX()+3) && (asteroide->getY() >= nave->getY()-1) && (asteroide->getY() <= nave->getY()))
	{
		nave->setVidas(nave->getVidas()-1);
		if(asteroide->getTipo() == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		return 1;
	}
	else
		return 0;
}
void Supervivencia::pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setY(asteroide->getY()+1);

	if(asteroide->getY() == this->getBajo()+2)
	{
		nuevoAsteroideVertical(asteroide);
	}
}
void Supervivencia::pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setX(asteroide->getX()+1);

	if(asteroide->getX() == this->getDerecha()+2)
	{
		nuevoAsteroideHorizontal(asteroide);
	}
}
Supervivencia::Supervivencia(): Juego()
{
	this->setAlto(this->getAlturaTerminal()*0.13);
	this->setIzquierda((this->getAnchuraTerminal()*0.074)-3);
	this->setBajo((this->getAlturaTerminal() * 0.5)+3);
	this->setDerecha((this->getAnchuraTerminal() * 0.85)-6);
}
void Supervivencia::mostrarNivel(int* num_ast)
{
	WINDOW* nivel = newwin(3, 12,this->getAlturaTerminal()/2-1.5,this->getAnchuraTerminal()/2-5.5);
	refresh();
	box(nivel,0,0);
	wmove(nivel, 1,1);
	wprintw(nivel, "NIVEL: %d", *num_ast);
	wrefresh(nivel);
	sleepS(3000);
	wclear(nivel);
	wrefresh(nivel);
	delwin(nivel);
	refresh();
}
void Supervivencia::mostrarVidaExtra()
{
	int alturaVentanaS = this->getBajo()+3;
	int anchuraVentanaS = this->getDerecha()+6;
	WINDOW* vidaExtra = newwin(3, 15,this->getAlturaTerminal()/2-1.5,this->getAnchuraTerminal()/2-7.5);
	refresh();
	box(vidaExtra,0,0);
	mvwprintw(vidaExtra,1,1, "VIDA EXTRA +1");
	wrefresh(vidaExtra);
	sleepS(1000);
	wclear(vidaExtra);
	wrefresh(vidaExtra);
	delwin(vidaExtra);
}

void Supervivencia::nuevaVidaExtra(VidaExtra* vidasExtra, int* num_vidasExtra)
{
	if(*num_vidasExtra < MAX_EXTRA)
	{
		vidasExtra[*num_vidasExtra].setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
		vidasExtra[*num_vidasExtra].setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
		(*num_vidasExtra)++;
	}
}
void Supervivencia::pintarVidasExtra(WINDOW* ventana, VidaExtra* vidasExtra, int* num_vidasExtra)
{
	for(int i=0; i<*num_vidasExtra; i++)
	{
		if(vidasExtra[i].getX() > 0)
			mvwprintw(ventana, vidasExtra[i].getY(), vidasExtra[i].getX(), "X");
	}
}
int Supervivencia::choqueVidasExtra(WINDOW* ventana, NaveSupervivencia* nave, VidaExtra* vidasExtra, int* num_vidasExtra, int* vidasExtraConsumidas)
{
	for(int i=0; i<*num_vidasExtra; i++)
	{
		if(vidasExtra[i].getX() > 0 && ((vidasExtra[i].getX() >= nave->getX()) && (vidasExtra[i].getX() <= nave->getX()+3) && (vidasExtra[i].getY() >= nave->getY()-1) && (vidasExtra[i].getY() <= nave->getY())))
		{
			nave->setVidas(nave->getVidas()+1);
			vidasExtra[i].setX(-1);
			vidasExtra[i].setY(-1);
			(*vidasExtraConsumidas)++;
			return 1;
		}
	}
	return 0;
}

void Supervivencia::actualizarS(WINDOW* ventana, NaveSupervivencia* nave)
{
	werase(ventana);
	nave->pintarVidas(this->getAnchuraTerminal());
   	box(ventana, 0,0);
}
void Supervivencia::liberarMemoriaS(NaveSupervivencia* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra, WINDOW* ventana, float* segundos, int* nuevaPartida)
{
	delete nave;
	delete[] asteroides;
	delete[] vidasExtra;
	delete num_ast;
	delete num_vidasExtra;
	delete segundos;
	delete nuevaPartida;
    wclear(ventana);
    wrefresh(ventana);
    delwin(ventana);
    clear();
    refresh();
}
void Supervivencia::inicializarParametrosS(Asteroide* asteroides, NaveSupervivencia* nave, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra)
{
	nave->setX((this->getDerecha()+6)/2);
	nave->setY(3*(this->getBajo()+3)/4);
	nave->setVidas(3);

	asteroides[0].setX((this->getDerecha()+6)/2-3);
	asteroides[0].setY(this->getAlto());
	asteroides[0].setTipo(0);

	*num_ast = 1;

	vidasExtra[0].setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
	vidasExtra[0].setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());

	*num_vidasExtra = 1;
}
void Supervivencia::movimientosJugadorS(int tecla, NaveSupervivencia* nave)
{
	switch(tecla)
    {
        case KEY_UP:

        	if(nave->getY() > this->getAlto())
        		nave->setY(nave->getY()-2);
            break;

        case KEY_DOWN:

        	if(nave->getY() < this->getBajo())
            	nave->setY(nave->getY()+2);
            break;

        case KEY_RIGHT:

        	if(nave->getX() < this->getDerecha())
            	nave->setX(nave->getX()+2);
            break;

        case KEY_LEFT:

        	if(nave->getX() > this->getIzquierda())
            	nave->setX(nave->getX()-2);
            break;

        default:
        	break;
    }
}
void Supervivencia::reestablecerValoresS(Asteroide* asteroides, int* num_ast, int* nuevaPartida)
{
	for(int i=1; i<*num_ast; i++)
	{
		asteroides[i].setX(0);
		asteroides[i].setY(0);
		asteroides[i].setTipo(0);
	}
	*num_ast = 0;
	*nuevaPartida = 1;
}
void Supervivencia::guardarPuntuacion(Usuario* usuarios, int player, int* num_ast)
{
	if(*num_ast > usuarios[player].getPuntuaciones()[1])
		usuarios[player].setPuntuacionSupervivencia(*num_ast);
}

void Supervivencia::reanudarPartida(int* objects, NaveSupervivencia* nave, Asteroide* asteroides, int*num_ast, VidaExtra* vidasExtra, int* vidasExtraConsumidas, int* num_vidasExtra, float* segundos)
{
	nave->setX(objects[0]);
	nave->setY(objects[1]);
	nave->setVidas(objects[2]);

	*num_ast = objects[3]/3;

	int contador = 4;
    for(int i=0; i<*num_ast;i++)
    {
    	asteroides[i].setX(objects[contador]);
    	asteroides[i].setY(objects[contador+1]);
    	asteroides[i].setTipo(objects[contador+2]);
    	contador += 3;
    }

    *vidasExtraConsumidas = objects[contador];
    contador++;
    *num_vidasExtra = objects[contador];
    contador++;

    for(int i=*vidasExtraConsumidas; i<*num_vidasExtra; i++)
    {
    	vidasExtra[i].setX(objects[contador]);
    	vidasExtra[i].setY(objects[contador+1]);
    	contador += 2;
    }

	*segundos = (float)objects[contador];
}

void Supervivencia::guardarPartida(Usuario* usuarios, int player, NaveSupervivencia* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* vidasExtraConsumidas, int* num_vidasExtra, int segundos)
{
	usuarios[player].setGuardadoS(1);
	usuarios[player].setObjectsS();
	int* objects = usuarios[player].getObjectsS();
	int contador = 0;

	objects[0] = nave->getX();
	objects[1] = nave->getY();
	objects[2] = nave->getVidas();

	objects[3] = (*num_ast)*3;

	contador = 4;

	for(int i=0; i<*num_ast; i++)
	{
		objects[contador] = asteroides[i].getX();
		objects[contador+1] = asteroides[i].getY();
		objects[contador+2] = asteroides[i].getTipo();
		contador+=3;
	}

	objects[contador] = *vidasExtraConsumidas;
	contador++;
	objects[contador] = *num_vidasExtra;
	contador++;

	for(int i=0; i<*num_vidasExtra; i++)
	{
		if(vidasExtra[i].getX() >= 0)
		{
			objects[contador] = vidasExtra[i].getX();
			objects[contador+1] = vidasExtra[i].getY();
			contador+=2;
		}
	}

	objects[contador] = segundos;
	contador++;
	objects[contador] = -1;
	contador++;
}

void Supervivencia::jugar(Usuario* usuarios, int player)
{
	initscr();
	curs_set(0);
	//tamanyoTerminal();
	WINDOW* info = mostrarInfo();

	sleepS(5000);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO SUPERVIVENCIA");
	move(2,this->getAnchuraTerminal()/2);
	printw("Vidas: ");

	WINDOW* ventana = mostrarJuego();

	NaveSupervivencia* nave = new NaveSupervivencia();
	Asteroide* asteroides = new Asteroide[MAX_AST];
	VidaExtra* vidasExtra = new VidaExtra[MAX_EXTRA];
	int* num_ast = new int;
	int* num_vidasExtra = new int;
	int* vidasExtraConsumidas = new int();
	*vidasExtraConsumidas = 0;

    float* segundos = new float();
    *segundos = 0;
    int choque_asteroide = 0;
    int choque_vidaExtra = 0;
    int tecla;

    int salirSinMenu = 0;
    int* nuevaPartida = new int();
    *nuevaPartida = 1;

    if(usuarios[player].getGuardadoS() == 1)
	{
		WINDOW* infoPartidaGuardada = this->mostrarInfoPartidaGuardada();

		if(!this->menuPartidaGuardada())
		{
			reanudarPartida(usuarios[player].getObjectsS(), nave, asteroides, num_ast, vidasExtra, vidasExtraConsumidas, num_vidasExtra, segundos);
			*nuevaPartida = 0;
		}
		wclear(infoPartidaGuardada);
		wrefresh(infoPartidaGuardada);
		delwin(infoPartidaGuardada);
		delete[] usuarios[player].getObjectsS();
		usuarios[player].setGuardadoS(0);
	}

    while(1)
    {

    	if(*nuevaPartida)
    	{
	    	inicializarParametrosS(asteroides, nave, num_ast, vidasExtra, num_vidasExtra);
	   		mostrarNivel(num_ast);
	   	}

	    while(1)
	    {
	        actualizarS(ventana, nave);
	        if(*segundos > 15)
	        {
	        	subirNivel(asteroides, num_ast);
	        	if(*num_ast == 5 || *num_ast == 8 || *num_ast == 10 || *num_ast == 13) nuevaVidaExtra(vidasExtra, num_vidasExtra);
	        	*segundos = 0;
	        }

	        if(choqueVidasExtra(ventana, nave, vidasExtra, num_vidasExtra, vidasExtraConsumidas)) choque_vidaExtra = 1;
	        pintarVidasExtra(ventana, vidasExtra, num_vidasExtra);

	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		choque_asteroide = 1;
	        		break;
	        	}
	        }

	        pintarAsteroides(ventana, asteroides, num_ast);

	        if(!choque_asteroide)
	        	nave->pintarNave(ventana);
	        else
				nave->pintarNaveChoque(ventana);

	        wrefresh(ventana);

	        if(choque_asteroide)
	        {
	        	sleepS(100);
			}
			if(choque_vidaExtra) mostrarVidaExtra();

	        tecla = wgetch(ventana);
	        movimientosJugadorS(tecla, nave);

	        if(tecla == 112)
    		{
    			tecla = 0;
    			WINDOW* partidaPausada = this->mostrarPartidaPausada();
    			while (1)
    			{
    				tecla = wgetch(ventana);
    				if(tecla==112 || tecla == 115 || tecla ==103)
    					break;
    			}
    			wclear(partidaPausada);
				wrefresh(partidaPausada);
				delwin(partidaPausada);
    		}

	        if(nave->getVidas() == 0 || tecla==115 || tecla==103)
	        {
        		if(tecla == 103)
        		{
        			WINDOW* partidaGuardada = this->mostrarPartidaGuardada();
        			sleepS(2000);
        			wclear(partidaGuardada);
					wrefresh(partidaGuardada);
					delwin(partidaGuardada);
        			guardarPartida(usuarios, player, nave, asteroides, num_ast, vidasExtra, vidasExtraConsumidas, num_vidasExtra, *segundos);
        			salirSinMenu = 1;
        		}
        		if(nave->getVidas() == 0)
        			mostrarGameOver();
	        	guardarPuntuacion(usuarios, player, num_ast);
	        	choque_asteroide = 0;
	        	choque_vidaExtra = 0;
	        	*segundos = 0;
	        	break;
        	}

	        sleepS(35);
	        *segundos +=0.035;
	        choque_asteroide = 0;
	        choque_vidaExtra = 0;
	    }
	    actualizarS(ventana,nave);
	    if(salirSinMenu || menuSalida())
    		break;
    	wrefresh(ventana);
    	reestablecerValoresS(asteroides, num_ast, nuevaPartida);
    }

    liberarMemoriaS(nave, asteroides, num_ast, vidasExtra, num_vidasExtra, ventana, segundos, nuevaPartida);
	endwin();
}
