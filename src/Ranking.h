#ifndef RANKING_H_
#define RANKING_H_

#include <curses.h>
#include "Usuario.h"

class Ranking
{
	private:
		static int MAX_X;
		static int MAX_Y;

	public:
		Ranking();
		virtual ~Ranking(){}
		static int getMAX_X(){return MAX_X;}
		static int getMAX_Y(){return MAX_Y;}
		virtual void mostrarRanking (Usuario* usuarios, int size) = 0;
};
#endif