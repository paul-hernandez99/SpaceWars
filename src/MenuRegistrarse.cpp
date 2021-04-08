#ifdef _WIN32
    #include <windows.h>

    void sleeppp(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleeppp(unsigned int milliseconds)
    {
        usleep(milliseconds * 1000);
    }
#endif

#include "MenuRegistrarse.h"
#include "MenuMain.h"
#include <string.h>
    #include <iostream>
using namespace std;


void MenuRegistrarse::menuRegistrarse (Usuario *usuarios, int size)
{
	Usuario *usuariosActualizados;
    echo();
    move((getMAX_Y()/2)-3.5, getMAX_X()/4+1);
    attron(A_REVERSE);
    printw("    REGISTRATE    ");
    attroff(A_REVERSE);
    
    WINDOW* registro = newwin(5,getMAX_X()/2,(getMAX_Y()/2)-2.5, getMAX_X()/4);
    box(registro,0,0);
    refresh();
    

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);

    wmove(registro, 1,1);
    wattron(registro, COLOR_PAIR(1));
    wprintw(registro, "NICKNAME:");

    wmove(registro, 2,1);
    wprintw(registro, "PASSWORD:");

    wmove(registro, 3,1);
    wprintw(registro, "CONFIRM PASSWORD:");

    wattroff(registro, COLOR_PAIR(1));
    wrefresh(registro);


    char aux[getMAX()];
    curs_set(1);
    wmove(registro, 1, 11);

    wgetnstr(registro, aux, getMAX());

    char *userIntroduced = new char [strlen(aux)+1];
    sscanf(aux, "%s", userIntroduced);

    int bl = 0;
    for (int i=0; i<size; i++)
    {
        if ((strcmp(usuarios[i].getNickname(), userIntroduced) == 0))
        {
            bl = 1;
            break;
        }
    }

    while (bl == 1)
    {
        move((getMAX_Y()/2)+3.5, getMAX_X()/4);
        wprintw(stdscr, "THAT NICKNAME ALREADY EXISTS! TRY AGAIN");
        refresh();
        wmove(registro, 1, 11);
        wprintw(registro, "             ");
        wmove(registro, 1, 11);

        wgetnstr(registro, aux, getMAX());
        userIntroduced = new char [strlen(aux)+1];
        sscanf(aux, "%s", userIntroduced);

        bl = 0;
        for (int i=0; i<size; i++)
        {
            if ((strcmp(usuarios[i].getNickname(), userIntroduced) == 0))
            {
                bl = 1;
                break;
            }
        }
    }

    move((getMAX_Y()/2)+3.5, getMAX_X()/4);
    wprintw(stdscr, "                                         ");
    refresh();


    wmove(registro, 2, 11);
    wgetnstr(registro, aux, getMAX());
    char *passIntroduced = new char [strlen(aux)+1];
    sscanf(aux, "%s", passIntroduced);

    wmove(registro, 3, 19);
    wgetnstr(registro, aux, getMAX());
    char *passConfiIntroduced = new char [strlen(aux)+1];
    sscanf(aux, "%s", passConfiIntroduced);

    if (strcmp(userIntroduced, passIntroduced) == 0)
    {
    	move((getMAX_Y()/2)+3.5, getMAX_X()/4);
        wprintw(stdscr, "NICKNAME AND PASSWORD CANNOT BE THE SAME");
        menuRegistrarse(usuarios, size);
    }

    else if (strcmp(passIntroduced, passConfiIntroduced) != 0)
    {
        move((getMAX_Y()/2)+3.5, getMAX_X()/4);
        wprintw(stdscr, "PASSWORDS ARE DIFFERENT! TRY AGAIN");
        menuRegistrarse(usuarios, size);
    }

    else
    {
        move((getMAX_Y()/2)+3.5, getMAX_X()/4);
        wprintw(stdscr, "REGISTRADO!");
        refresh();
        usuariosActualizados = new Usuario [size+1];

        
        for (int i=0; i<size; i++)
        {
            usuariosActualizados[i] = usuarios[i];
        }
 
        usuariosActualizados[size].setNickname(userIntroduced);
    
        usuariosActualizados[size].setContrasenya(passIntroduced);

        float* initializeNull = new float [2];
        initializeNull[0] = 0.0f;
        initializeNull[1] = 0.0f;
        usuariosActualizados[size].setPuntuaciones(initializeNull);

        usuariosActualizados[size].setGuardadoC(0);
        usuariosActualizados[size].setGuardadoS(0);

        usuariosActualizados[size].setObjectsC();
        usuariosActualizados[size].setObjectsS();

        
        size++;

        LecturaEscrituraFichero le;
        le.escribirUsuarios(usuariosActualizados, size);
        sleeppp(1000);

        liberarMemoriaMenuRegistrarse(registro, usuariosActualizados, size, userIntroduced, passIntroduced, passConfiIntroduced, initializeNull);

        MenuMain menMain;
        menMain.menuPrincipal();
    }
}

void MenuRegistrarse::liberarMemoriaMenuRegistrarse(WINDOW* registro, Usuario* usuariosActualizados, int size, char* userIntroduced, char* passIntroduced, char* passConfiIntroduced, float* initializeNull)
{
    delete [] usuariosActualizados;
    delete [] userIntroduced;
    delete [] passIntroduced;
    delete [] passConfiIntroduced;
    delete [] initializeNull;
    
    werase(registro);
    erase();
    wrefresh(registro);
    refresh();
}
