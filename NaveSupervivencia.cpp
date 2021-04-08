#include "NaveSupervivencia.h"

void NaveSupervivencia::pintarNaveChoque(WINDOW* ventana)
{
	wmove(ventana, this->getY(), this->getX()); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, this->getY()-1, this->getX()+1); wprintw(ventana, "\"\"");
}
void NaveSupervivencia::pintarVidas(int anchuraTerminal)
{
	move(2,anchuraTerminal/2+7); printw("%i",this->getVidas());
	refresh();
}
void NaveSupervivencia::pintarNave(WINDOW* ventana)
{
	wmove(ventana, this->getY(), this->getX()); wprintw(ventana, "****");
	wmove(ventana, this->getY()-1, this->getX()+1); wprintw(ventana, "**");
}
