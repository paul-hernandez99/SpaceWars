#include "Menu.h"
#include <curses.h>

int Menu::MAX_X = 0;
int Menu::MAX_Y = 0;
int Menu::contadorSalida = 0;
const int Menu::MAX = 50;

void Menu::tamanyoTerminal()
{
	getmaxyx(stdscr, MAX_Y, MAX_X);
}