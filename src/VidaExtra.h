#ifndef VIDAEXTRA_H_
#define VIDAEXTRA_H_

class VidaExtra
{
	int x;
	int y;
public: 
	VidaExtra(): x(-1), y(-1){}
	VidaExtra(int x, int y): x(x), y(y){}
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
};

#endif