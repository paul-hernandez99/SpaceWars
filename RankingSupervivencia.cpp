#include "RankingSupervivencia.h"

void RankingSupervivencia::mostrarRanking (Usuario* usuarios, int size)
{
	Usuario* arrayUsuarios = new Usuario[size];
	
    for (int i=0; i<size; i++)
    {
        arrayUsuarios[i] = usuarios[i];
    }

    Usuario* aux = new Usuario ();
	
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-i-1; j++)
		{
			if (arrayUsuarios[j].getPuntuaciones()[1] < arrayUsuarios[j+1].getPuntuaciones()[1])
			{
				*aux = arrayUsuarios[j];
				arrayUsuarios[j] = arrayUsuarios[j+1];
				arrayUsuarios[j+1] = *aux;
			}
		}
	}

	noecho();
	move(this->getMAX_Y()/2-7, this->getMAX_X()/4+1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("  RANKING SUPERVIVENCIA  ");
    attroff(COLOR_PAIR(1));
    WINDOW* rankingSupervivencia = newwin(12, this->getMAX_X()/2, this->getMAX_Y()/2-6, this->getMAX_X()/4);
    box(rankingSupervivencia,0,0);
    refresh();
    wrefresh(rankingSupervivencia);

    for (int i=0; i<size && i<10; i++)
    {
    	mvwprintw(rankingSupervivencia, 1+i, 1, "%d.- %s", (i+1), arrayUsuarios[i].getNickname());
    	mvwprintw(rankingSupervivencia, 1+i, getMAX_X()/4, "nivel");
    	mvwprintw(rankingSupervivencia, 1+i, 3*getMAX_X()/8, "%.0f", arrayUsuarios[i].getPuntuaciones()[1]);
    }

    wrefresh(rankingSupervivencia);

     move(this->getMAX_Y()/2+6, this->getMAX_X()/4+1);
    attron(A_REVERSE);
    printw("pulsa enter para volver...");
    attroff(A_REVERSE);

    while(getch()!= 10);
    liberarMemoriaRankingSupervivencia(arrayUsuarios, aux, rankingSupervivencia);

}
void RankingSupervivencia::liberarMemoriaRankingSupervivencia (Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingSupervivencia)
{
	delete aux;
	delete [] arrayusuarios;

	wclear(rankingSupervivencia);
    wrefresh(rankingSupervivencia);
    delwin(rankingSupervivencia);
    clear();
    refresh();
}