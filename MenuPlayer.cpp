#include "MenuPlayer.h"

int MenuPlayer::menuPlayer()
{
	curs_set(0);
    noecho();
    WINDOW* player = newwin(7, getMAX_X()/2, (getMAX_Y()/2)-3.5, getMAX_X()/4);
    move((getMAX_Y()/2)-4.5, getMAX_X()/4);
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(3));
    printw("    BIENVENIDO    ");
    attroff(COLOR_PAIR(3));

    refresh();
    box(player,0,0);
    keypad(player, TRUE);

    const char** opciones = new const char* [5];

    for(int i=0; i<5; i++)
    {
    	opciones[i] = new char[getMAX()];
    }
    opciones[0] = "JUGAR CLASICO";
    opciones[1] = "JUGAR SUPERVIVENCIA";
    opciones[2] = "RANKING CLASICO";
    opciones[3] = "RANKING SUPERVIVENCIA";
    opciones[4] = "SALIR";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
        for(int i=0; i<5; i++)
        {
            if(i==seleccion)
                wattron(player, A_REVERSE);
            mvwprintw(player, i+1, 1, "%s", opciones[i]);
            wattroff(player, A_REVERSE);
        }
        wrefresh(player);

        eleccion = wgetch(player);

        switch(eleccion)
        {
            case KEY_UP:
                seleccion--;
                if(seleccion == -1)
                    seleccion = 0;
                break;
            case KEY_DOWN:
                seleccion++;
                if(seleccion == 5)
                    seleccion = 4;
                break;
            default:
                break;
        }
        if(eleccion == 10)
            break;
    }

    liberarMemoriaMenuPlayer(player, opciones);

    return seleccion;
}
void MenuPlayer::liberarMemoriaMenuPlayer(WINDOW* player, const char** opciones)
{
		werase(player);
    erase();
    refresh();
    wrefresh(player);
}
