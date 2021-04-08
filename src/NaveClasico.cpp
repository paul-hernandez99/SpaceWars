#include "NaveClasico.h"

void NaveClasico::pintarNaveChoque(WINDOW* ventana)
{
	wmove(ventana, this->getY(), this->getX()); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, this->getY()-1, this->getX()+1); wprintw(ventana, "\"\"");
}
void NaveClasico::pintarVidas(int anhura)
{
	move(2,8); printw("%i",this->getVidas());
	
	mvprintw(2,19,"   ");
	for(int i=0; i<this->getCorazones();i++)
	{
		mvprintw(2,19+i,"O");
	}
	refresh();
}
void NaveClasico::pintarNave(WINDOW* ventana)
{
	wmove(ventana, this->getY(), this->getX()); wprintw(ventana, "****");
	wmove(ventana, this->getY()-1, this->getX()+1); wprintw(ventana, "**");
}
int NaveClasico::getCorazones() const
{
	return this->corazones;
}
void NaveClasico::setCorazones(int corazones)
{
	this->corazones = corazones;
}