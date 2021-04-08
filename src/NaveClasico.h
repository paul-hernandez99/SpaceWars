#ifndef NAVECLASICO_H_
#define NAVECLASICO_H_
#include <curses.h>
#include "Nave.h"

class NaveClasico: public Nave
{
	int corazones;
public:
	NaveClasico(): Nave(-1,-1,-1), corazones(-1){}
	NaveClasico(int x, int y, int vidas, int corazones): Nave(x, y, vidas), corazones(corazones){}
	virtual ~NaveClasico(){}
	virtual void pintarNaveChoque(WINDOW* ventana);
	virtual void pintarVidas(int anchuraTerminal);
	virtual void pintarNave(WINDOW* ventana);
	int getCorazones() const;
	void setCorazones(int corazones);
};



#endif