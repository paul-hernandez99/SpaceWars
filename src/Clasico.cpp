#include "Clasico.h"
#include <iostream>
#include <list>
using namespace std;
#ifdef _WIN32
	#include <windows.h>
	void sleepC(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#else
	#include <unistd.h>

	void sleepC(unsigned int milliseconds)
	{
		usleep(milliseconds * 1000);
	}
#endif

const int Clasico::MAX_AST = 20;
const int Clasico::MAX_LENGHT = 15;
const int Clasico::MAX_BALAS = 200;

Clasico::Clasico(): Juego()
{
	this->setAlto(this->getAlturaTerminal()*0.13);
	this->setIzquierda((this->getAnchuraTerminal()*0.074)-1);
	this->setBajo((this->getAlturaTerminal() * 0.83)-3);
	this->setDerecha((this->getAnchuraTerminal() * 0.85)-6);
}
void Clasico::pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<*num_ast; i++)
    {
    	if(asteroides[i].getTipo() == 0)
    		pintarAsteroideVertical(ventana, &asteroides[i]);
    	else
    		pintarAsteroideHorizontal(ventana, &asteroides[i]);
    }
}
void Clasico::subirNivel(Asteroide* asteroides, int* num_ast)
{
	if(*num_ast < MAX_AST)
	{
		crearAsteroidesHorizontales(asteroides,num_ast);
		crearAsteroidesVerticales(asteroides, num_ast);
	}
}
void Clasico::mostrarGameOver()
{
	int alturaVentanaClasico = this->getBajo();
	int anchuraVentanaClasico = this->getDerecha()+6;
	WINDOW* gameOver = newwin(Juego::getAlturaTerminal()/6,Juego::getAnchuraTerminal()/4,alturaVentanaClasico/4.2, anchuraVentanaClasico/2.3);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	wclear(gameOver);
	delwin(gameOver);
}
int Clasico::menuSalida()
{
	WINDOW* salida = newwin(this->getAlturaTerminal()/5,this->getAnchuraTerminal()-20,this->getAlturaTerminal()-(this->getAlturaTerminal()/5)-1, this->getIzquierda()+1);
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
WINDOW* Clasico::mostrarInfo()
{
	WINDOW* info = newwin(this->getAlturaTerminal()/2.7,this->getAnchuraTerminal()/1.7,this->getAlturaTerminal()/2.5, this->getAnchuraTerminal()/4);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las flechas, y para diparar el espacio.");
	mvwprintw(info,3,1,"Tu puntuacion dependera de la duracion de la partida y de los");
	mvwprintw(info,4,1,"asteroides abatidos.");
	mvwprintw(info,5,1,"Para guardar la partida pulsa g.");
	mvwprintw(info,6,1,"Para pausar la partida pulsa p.");
	mvwprintw(info,7,1,"Para salir pulsa s.");
	mvwprintw(info,8,1,"El juego esta a punto de empezar...");
	mvwprintw(info,9,1,"Buena suerte!");
	wrefresh(info);
	return info;
}
WINDOW* Clasico::mostrarJuego()
{
	WINDOW* ventana = newwin(this->getBajo()+3, this->getDerecha()+6, this->getAlto(), this->getIzquierda()+1);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}
void Clasico::nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
	asteroide->setY(this->getAlto()-3);
}

void Clasico::nuevoAsteroideHorizontal(Asteroide* asteroide)
{
	asteroide->setX(this->getIzquierda()-2);
	asteroide->setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
}
void Clasico::pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setY(asteroide->getY()+1);

	if(asteroide->getY() == this->getBajo()+1)
	{
		nuevoAsteroideVertical(asteroide);
	}

}
void Clasico::pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->getY(), asteroide->getX()); wprintw(ventana, "O");

	asteroide->setX(asteroide->getX()+1);

	if(asteroide->getX() == this->getDerecha()+1)
	{
		nuevoAsteroideHorizontal(asteroide);
	}
}

void Clasico::crearBalas (Bala* balas, NaveClasico* nave, int* num_balas)
{
	if(*num_balas < MAX_BALAS)
	{
		balas[*num_balas].setX(nave->getX()+1);
		balas[*num_balas].setY(nave->getY()-2);
		balas[*num_balas+1].setX(nave->getX()+2);
		balas[*num_balas+1].setY(nave->getY()-2);

		*num_balas += 2;
	}
}
void Clasico::mostrarPuntuacion (Usuario* usuarios, int player, float tiempo, int* disparosAcertados)
{
	float puntuacionTotal = tiempo*10 + *disparosAcertados;

	if(puntuacionTotal > usuarios[player].getPuntuaciones()[0])
		usuarios[player].setPuntuacionClasico(puntuacionTotal);

	WINDOW* puntuacion = newwin(7, 45, this->getAlturaTerminal()/2-3.5, this->getAnchuraTerminal()/2-22.5);
	refresh();
	box(puntuacion,0,0);
	wmove(puntuacion,1,2);
	wprintw(puntuacion, "Duracion: %0.2f",tiempo);
	wmove(puntuacion,2,2);
	wprintw(puntuacion,"Puntos por Duracion: %0.2f * 10 = %0.2f",tiempo, tiempo*10);
	wmove(puntuacion,3,2);
	wprintw(puntuacion, "Puntos por Disparos: %d",*disparosAcertados);
	wmove(puntuacion,4,2);
	wprintw(puntuacion,"----------------------------------");
	wmove(puntuacion,5,2);
	wprintw(puntuacion,"TOTAL: %0.2f", puntuacionTotal);
	wrefresh(puntuacion);
	wclear(puntuacion);
	delwin(puntuacion);
}
void Clasico::pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala, int* disparosConsumidos)
{
	wmove(ventana, bala->getY(), bala->getX()); wprintw(ventana, "#");
	bala->setX(-1);
	bala->setY(-1);
	(*disparosConsumidos)++;
}
int Clasico::choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados, int* disparosConsumidos)
{
	if((bala->getX() == asteroide->getX()) && ((bala->getY() == asteroide->getY()+1) || (bala->getY() == asteroide->getY())) || (bala->getX()+1 == asteroide->getX()) && ((bala->getY() == asteroide->getY()+1) || (bala->getY() == asteroide->getY())))
	{
		if(asteroide->getTipo() == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		pintarChoqueAsteroideBala(ventana, bala, disparosConsumidos);
		(*disparosAcertados)++;
		return 1;
	}
	else
		return 0;
}
int Clasico::choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	NaveClasico* aux = (NaveClasico*)nave;
	if((asteroide->getX() >= nave->getX()) && (asteroide->getX() <= nave->getX()+3) && (asteroide->getY() >= nave->getY()-1) && (asteroide->getY() <= nave->getY()))
	{
		aux->setCorazones(aux->getCorazones()-1);
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

void Clasico::pintarBala(WINDOW* ventana, Bala* bala, int* disparosConsumidos)
{
	mvwprintw(ventana, bala->getY(), bala->getX(), "^");

	bala->setY(bala->getY()-1);

	if (bala->getY() == this->getAlto()-2)
	{
		bala->setX(-1);
		bala->setY(-1);
		(*disparosConsumidos)++;
	}
}
void Clasico::actualizarDisparosAcertados (int* disparosAcertados, int* num_balas)
{
	mvprintw(2, 45, "   ");
	mvprintw(2, 25, "Disparos Acertados: %d", *disparosAcertados);

	mvprintw(2, 62, "   ");
	mvprintw(2, 51, "Restantes: %d", (MAX_BALAS-*num_balas));
	refresh();
}
void Clasico::actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* num_balas)
{
	nave->pintarVidas(0);
    actualizarDisparosAcertados(disparosAcertados, num_balas);
	werase(ventana);
	box(ventana, 0,0);
}
void Clasico::crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<2; i++)
	{
		asteroides[*num_ast].setX(this->getIzquierda()-2);
		asteroides[*num_ast].setY((rand()%(this->getBajo()-this->getAlto()+1)) + this->getAlto());
		asteroides[*num_ast].setTipo(1);
		(*num_ast)++;
	}
}
void Clasico::crearAsteroidesVerticales(Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<3; i++)
	{
		asteroides[*num_ast].setX((rand()%(this->getDerecha()-this->getIzquierda()+1)) + this->getIzquierda());
		asteroides[*num_ast].setY(this->getAlto()-3);
		asteroides[*num_ast].setTipo(0);
		(*num_ast)++;
	}
}


void Clasico::inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados, int* disparosConsumidos)
{
	nave->setX((this->getDerecha()+6)/2);
    nave->setY(3*(this->getBajo()+3)/4);
    nave->setCorazones(3);
    nave->setVidas(3);

    for(int i=0; i<5; i++)
    {
    	nuevoAsteroideVertical(&asteroides[i]);
    	asteroides[i].setTipo(0);
    }

	*num_ast = 5;
	*num_balas = 0;
	*disparosAcertados = 0;
	*disparosConsumidos = 0;
}

void Clasico::reanudarPartida(int* objects, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosConsumidos, float* segundos, float* tiempo, int* disparosAcertados)
{
	nave->setX(objects[0]);
	nave->setY(objects[1]);
	nave->setVidas(objects[2]);
	nave->setCorazones(objects[3]);

	*num_ast = objects[4]/3;

	int contador = 5;
    for(int i=0; i<*num_ast;i++)
    {
    	asteroides[i].setX(objects[contador]);
    	asteroides[i].setY(objects[contador+1]);
    	asteroides[i].setTipo(objects[contador+2]);
    	contador += 3;
    }

    *disparosConsumidos = objects[5+objects[4]];
    contador++;
    *num_balas = objects[6+objects[4]];
    contador++;

    for(int i=*disparosConsumidos; i<*num_balas; i++)
    {
    	balas[i].setX(objects[contador]);
    	balas[i].setY(objects[contador+1]);
    	contador += 2;
    }

	*segundos = (float)objects[contador];
	*tiempo = (float)objects[contador+1];
	*disparosAcertados = objects[contador+2];
}

void Clasico::liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, WINDOW* ventana, float* segundos, float* tiempo, int* nuevaPartida)
{
		delete nave;
    delete[] asteroides;
    delete num_ast;
    delete[] balas;
    delete num_balas;
    delete disparosAcertados;
    delete disparosConsumidos;
    delete segundos;
    delete tiempo;
    delete nuevaPartida;
    wclear(ventana);
    wrefresh(ventana);
    delwin(ventana);
    clear();
    refresh();
}
void Clasico::reestablecerValoresC(Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int* disparosConsumidos, int* nuevaPartida)
{
	for(int i=0; i<*num_ast; i++)
	{
		asteroides[i].setX(0);
		asteroides[i].setY(0);
	}
	for(int i=0; i<*num_balas; i++)
	{
		balas[i].setX(0);
		balas[i].setY(0);
	}
	*num_ast = 0;
	*num_balas = 0;
	*disparosAcertados = 0;
	*disparosConsumidos = 0;

	*nuevaPartida = 1;
}
void Clasico::movimientosJugadorC(int tecla, NaveClasico* nave, Bala* balas, int* num_balas)
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

        	if(nave->getX() < this->getDerecha()-1)
            	nave->setX(nave->getX()+2);
            break;

        case KEY_LEFT:

        	if(nave->getX() > this->getIzquierda())
            	nave->setX(nave->getX()-2);
            break;
        case 32:
        	crearBalas(balas, nave, num_balas);
        	break;

        default:
        	break;
    }
}


void Clasico::guardarPartida(Usuario* usuarios, int player, NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int segundos, int tiempo, int* disparosAcertados, int* disparosConsumidos)
{
	usuarios[player].setGuardadoC(1);
	usuarios[player].setObjectsC();
	int* objects = usuarios[player].getObjectsC();
	int contador = 0;

	objects[0] = nave->getX();
	objects[1] = nave->getY();
	objects[2] = nave->getVidas();
	objects[3] = nave->getCorazones();

	objects[4] = (*num_ast)*3;

	contador = 5;
	if(*num_ast > 0)
	{
		for(int i=0; i<*num_ast; i++)
		{
			objects[contador] = asteroides[i].getX();
			objects[contador+1] = asteroides[i].getY();
			objects[contador+2] = asteroides[i].getTipo();
			contador+=3;
		}
	}

	objects[contador] = *disparosConsumidos;
	contador++;
	objects[contador] = *num_balas;
	contador++;
	if(*num_balas > 0)
	{
		for(int i=*disparosConsumidos; i<*num_balas; i++)
		{
			objects[contador] = balas[i].getX();
			objects[contador+1] = balas[i].getY();
			contador+=2;
		}
	}

	objects[contador] = segundos;
	contador++;
	objects[contador] = tiempo;
	contador++;
	objects[contador] = *disparosAcertados;
	contador++;
	objects[contador] = -1;
	contador++;
}

void Clasico::jugar(Usuario* usuarios, int player)
{
	curs_set(0);

	WINDOW* info = mostrarInfo();

	sleepC(5000);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");
	move(2,1);
	printw("Vidas: ");
	move(2,12);
	printw("Salud: ");

    WINDOW* ventana = mostrarJuego();

    NaveClasico* nave = new NaveClasico();
    Asteroide* asteroides = new Asteroide[MAX_AST];
    Bala* balas = new Bala[MAX_BALAS];

    int* num_ast = new int();
    int* num_balas = new int();
    int* disparosConsumidos = new int();
    int* disparosAcertados = new int();

    float* segundos = new float();
    *segundos = 0;
    float* tiempo = new float();
    *tiempo = 0;

    int choqueAsteroide = 0;
    int choqueBala = 0;
    int tecla;

    int salidaSinMenu = 0;
    int* nuevaPartida = new int();
    *nuevaPartida = 1;

    if(usuarios[player].getGuardadoC() == 1)
	{
		WINDOW* infoPartidaGuardada = this->mostrarInfoPartidaGuardada();

		if(!this->menuPartidaGuardada())
		{
			reanudarPartida(usuarios[player].getObjectsC(), nave, asteroides, num_ast, balas, num_balas, disparosConsumidos, segundos, tiempo, disparosAcertados);
			*nuevaPartida = 0;
		}
		wclear(infoPartidaGuardada);
		wrefresh(infoPartidaGuardada);
		delwin(infoPartidaGuardada);
		delete[] usuarios[player].getObjectsC();
		usuarios[player].setGuardadoC(0);
	}
    while(1)
    {
    	if(*nuevaPartida)
	    	 inicializarParametrosC(nave, asteroides, num_ast, num_balas, disparosAcertados, disparosConsumidos);

	    while(1)
	    {
	        actualizarC(ventana, nave, disparosAcertados, num_balas);

	        if(*segundos > 30)
	        {
	        	subirNivel(asteroides, num_ast);
	        	*segundos = 0;
	        }

	        for (int i=0; i<*num_ast; i++)
	        {
	        	for (int j=*disparosConsumidos; j<*num_balas; j++)
	        	{
					if(choqueBalaAsteroide(ventana, &balas[j], &asteroides[i], disparosAcertados, disparosConsumidos))
	        		{
	        			choqueBala = 1;
	        			break;
	        		}
	        	}
	        }
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		choqueAsteroide = 1;
	        		break;
	        	}
	        }
	        for (int i=*disparosConsumidos; i<*num_balas; i++)
	        {
	        	pintarBala(ventana, &balas[i], disparosConsumidos);
	        }

	        pintarAsteroides(ventana, asteroides, num_ast);

	        if(!choqueAsteroide)
	        	nave->pintarNave(ventana);
	        else
	        	nave->pintarNaveChoque(ventana);

	        wrefresh(ventana);

	        if(choqueAsteroide)
	        {
	        	sleepC(500);
	        }
	        if(choqueBala)
	        {
	        	sleepC(50);
	        }

	        if(nave->getCorazones() == 0)
        	{
        		nave->setVidas(nave->getVidas()-1);
        		nave->setCorazones(3);
        	}

	    	tecla = wgetch(ventana);
	    	movimientosJugadorC(tecla, nave, balas, num_balas);

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
	    			sleepC(2000);
	    			wclear(partidaGuardada);
					wrefresh(partidaGuardada);
					delwin(partidaGuardada);
	    			guardarPartida(usuarios, player, nave, asteroides, num_ast, balas, num_balas, *segundos, *tiempo, disparosAcertados, disparosConsumidos);
	    			salidaSinMenu = 1;
	    		}
	    		if(nave->getVidas() == 0)
	    			mostrarGameOver();
	    		mostrarPuntuacion(usuarios, player, *tiempo,disparosAcertados);
	    		choqueAsteroide = 0;
	        	choqueBala = 0;
	        	*segundos = 0;
	        	*tiempo = 0;
	    		break;
        	}

	        sleepC(50);
	        *segundos +=0.050;
	        *tiempo +=0.050;
	        choqueAsteroide = 0;
	        choqueBala = 0;
	    }
	    actualizarC(ventana, nave, disparosAcertados, disparosConsumidos);
	    if(salidaSinMenu || menuSalida())
    		break;
    	reestablecerValoresC(asteroides, num_ast, balas, num_balas, disparosAcertados, disparosConsumidos, nuevaPartida);
    }
    liberarMemoriaC(nave, asteroides, num_ast, balas, num_balas, disparosAcertados, disparosConsumidos, ventana, segundos, tiempo, nuevaPartida);
	endwin();
}
