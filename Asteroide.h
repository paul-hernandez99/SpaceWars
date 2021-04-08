#ifndef ASTEROIDE_H_
#define ASTEROIDE_H_
#include <curses.h>

class Asteroide
{
	int x;
	int y;
	int tipo;
public:
	Asteroide(): x(-1), y(-1), tipo(-1){}
	Asteroide(int x, int y, int tipo): x(x), y(y), tipo(tipo){}
	virtual ~Asteroide(){}
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	int getTipo() const;
	void setTipo(int tipo);
};

#endif