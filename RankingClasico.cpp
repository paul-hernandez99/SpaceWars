#include "RankingClasico.h"
#include <iostream>
using namespace std;

void RankingClasico::mostrarRanking(Usuario* usuarios, int size)
{
	Usuario* arrayUsuarios = new Usuario [size];
    for (int i=0; i<size; i++)
    {
        arrayUsuarios[i] = usuarios[i];
    }

    Usuario* aux = new Usuario ();
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-i-1; j++)
		{
			if (arrayUsuarios[j].getPuntuaciones()[0] < arrayUsuarios[j+1].getPuntuaciones()[0])
			{
				*aux = arrayUsuarios[j];
				arrayUsuarios[j] = arrayUsuarios[j+1];
				arrayUsuarios[j+1] = *aux;
			}
		}
	}
	curs_set(0);
	move(this->getMAX_Y()/2-7, this->getMAX_X()/4+1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("  RANKING CLASICO  ");
    attroff(COLOR_PAIR(1));
    WINDOW* rankingClasico = newwin(12, this->getMAX_X()/2, this->getMAX_Y()/2-6, this->getMAX_X()/4);
  	refresh();
    box(rankingClasico,0,0);
    wrefresh(rankingClasico);

    for (int i=0; i<size && i<10; i++)
    {
    	mvwprintw(rankingClasico, 1+i, 1, "%d.- %s", (i+1), arrayUsuarios[i].getNickname());
    	mvwprintw(rankingClasico, 1+i, this->getMAX_X()/4, "%.2f", arrayUsuarios[i].getPuntuaciones()[0]);
    	mvwprintw(rankingClasico, 1+i, 3*this->getMAX_X()/8, "puntos");
    }

    wrefresh(rankingClasico);

    move(this->getMAX_Y()/2+6, this->getMAX_X()/4+1);
    attron(A_REVERSE);
    printw("pulsa enter para volver...");
    attroff(A_REVERSE);

    while(getch()!= 10);
    liberarMemoriaRankingClasico(arrayUsuarios, aux, rankingClasico);
}
void RankingClasico::liberarMemoriaRankingClasico (Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingClasico)
{
	delete aux;
	delete [] arrayusuarios;

	wclear(rankingClasico);
    wrefresh(rankingClasico);
    delwin(rankingClasico);
    clear();
    refresh();
}