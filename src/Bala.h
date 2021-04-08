#ifndef BALA_H_
#define BALA_H_

class Bala
{
	int x;
	int y;
public:
	Bala(): x(-1), y(-1){}
	Bala(int x, int y): x(x), y(y){}
	virtual ~Bala(){}
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};

#endif