#include "Ranking.h"

int Ranking::MAX_X = 0;
int Ranking::MAX_Y = 0;

Ranking::Ranking()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
}
