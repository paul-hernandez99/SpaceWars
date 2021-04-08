#ifdef _WIN32
	#include <windows.h>

	void sleepp(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#else
	#include <unistd.h>

	void sleepp(unsigned int milliseconds)
	{
		usleep(milliseconds * 1000);
	}
#endif


#include "MenuIniciarSesion.h"
#include <iostream>
#include <string.h>
using namespace std;

int MenuIniciarSesion::menuIniciarSesion(Usuario *usuarios, int size)
{
	echo();
    move((getMAX_Y()/2)-3, getMAX_X()/4+1);
    attron(A_REVERSE);
    printw("  LOGIN  ");
    attroff(A_REVERSE);
    WINDOW* inicioSesion = newwin(4,getMAX_X()/2,(getMAX_Y()/2)-2, getMAX_X()/4);
    refresh();
    box(inicioSesion,0,0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);

    wmove(inicioSesion, 1,1);
    wattron(inicioSesion, COLOR_PAIR(1));
    wprintw(inicioSesion, "NICKNAME:");

    wmove(inicioSesion, 2,1);
    wprintw(inicioSesion, "PASSWORD:");

    wattroff(inicioSesion, COLOR_PAIR(1));
    wrefresh(inicioSesion);

    char aux[getMAX()];
    curs_set(1);
    wmove(inicioSesion, 1, 11);
    wgetnstr(inicioSesion, aux, getMAX());

    char* userIntroduced = new char [strlen(aux)+1];
    sscanf(aux, "%s", userIntroduced);

    wmove(inicioSesion, 2, 11);
    wgetnstr(inicioSesion, aux, getMAX());

    char* passIntroduced = new char [strlen(aux)+1];
    sscanf(aux, "%s", passIntroduced);

    int boolean = 0;
    int player;

    for (int i=0; i<size; i++)
    {
        if ((strcmp(usuarios[i].getNickname(), userIntroduced) == 0))
        {
            boolean = -1;
            if ((strcmp(usuarios[i].getContrasenya(), passIntroduced) == 0))
            {
                boolean = 1;
                player = i;
                break;
            }
        }
    }

    if (boolean == 1)
    {
    	setContadorSalida(0);
        curs_set(1);
        liberarMemoriaMenuInicioSesion(userIntroduced, passIntroduced, inicioSesion);
        return player;
    }

    if (getContadorSalida() == 2)
    {
        start_color();
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
        wattron(stdscr, COLOR_PAIR(2));
        move((getMAX_Y()/2)+4, getMAX_X()/4);
        wprintw(stdscr, "YOU HAVE ENTERED WRONGLY 3 TIMES. TRY NEXT TIME...");
        wattroff(stdscr, COLOR_PAIR(2));
        refresh();

        sleepp(3000);

        liberarMemoriaMenuInicioSesion(userIntroduced, passIntroduced, inicioSesion);

        exit(0);
    }

    if(boolean == -1)
    {
        move((getMAX_Y()/2)+3, getMAX_X()/4);
        printw("INCORRECT PASSWORD! TRY AGAIN");
        setContadorSalida(getContadorSalida()+1);
        menuIniciarSesion(usuarios, size);
    }

    if (boolean == 0)
    {
        move((getMAX_Y()/2)+3, getMAX_X()/4);
        wprintw(stdscr, "INCORRECT NICKNAME! TRY AGAIN");
        setContadorSalida(getContadorSalida()+1);
        menuIniciarSesion(usuarios, size);
    }
}

void MenuIniciarSesion::liberarMemoriaMenuInicioSesion(char* userIntroduced, char* passIntroduced, WINDOW* inicioSesion)
{
    delete [] userIntroduced;
    delete passIntroduced;

    werase(inicioSesion);
    erase();
    refresh();
    wrefresh(inicioSesion);
}
