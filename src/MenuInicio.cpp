#include "MenuInicio.h"


int MenuInicio::menuInicio()
{
	cbreak();
    noecho();
    curs_set(0);
    WINDOW* inicio = newwin(5,getMAX_X()/2,(getMAX_Y()/2)-2.5, getMAX_X()/4);
    move((getMAX_Y()/2)-3.5, getMAX_X()/4+1);
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(3));
    printw("    BIENVENIDO A MULTIJUEGOS    ");
    attroff(COLOR_PAIR(3));

    refresh();
    box(inicio,0,0);
    keypad(inicio, TRUE);

    const char** opciones = new const char*[3];

    for(int i=0; i<3; i++)
    {
    	opciones[i] = new char[getMAX()];
    }
    opciones[0] = "INICIAR SESION";
    opciones[1] = "REGISTRARSE";
    opciones[2] = "CERRAR JUEGO";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
        for(int i=0; i<3; i++)
        {
            if(i==seleccion)
                wattron(inicio, A_REVERSE);
            mvwprintw(inicio, i+1, 1, "%s", opciones[i]);
            wattroff(inicio, A_REVERSE);
        }
        wrefresh(inicio);

        eleccion = wgetch(inicio);

        switch(eleccion)
        {
            case KEY_UP:
                seleccion--;
                if(seleccion == -1)
                    seleccion = 0;
                break;
            case KEY_DOWN:
                seleccion++;
                if(seleccion == 3)
                    seleccion = 2;
                break;
            default:
                break;
        }
        if(eleccion == 10)
            break;
    }

    liberarMemoriaMenuInicio(opciones, inicio);

    return seleccion;
}
void MenuInicio::liberarMemoriaMenuInicio(const char** opciones, WINDOW* inicio)
{
		wclear(inicio);
		werase(inicio);
		delwin(inicio);
		erase();
		clear();
		wrefresh(inicio);
		refresh();
}
