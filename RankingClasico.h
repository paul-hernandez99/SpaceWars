#ifndef RANKINGCLASICO_H_
#define RANKINGCLASICO_H_

#include "Ranking.h"

class RankingClasico : public Ranking
{
	public:
		RankingClasico() : Ranking () {}
		virtual ~RankingClasico(){}
		virtual void mostrarRanking (Usuario* usuarios, int size);
		void liberarMemoriaRankingClasico (Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingClasico);
};
#endif