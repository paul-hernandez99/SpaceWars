#ifndef RANKINGSUPERVIVENCIA_H_
#define RANKINGSUPERVIVENCIA_H_

#include "Ranking.h"

class RankingSupervivencia : public Ranking
{
	public:
		RankingSupervivencia () : Ranking() {}
		virtual ~RankingSupervivencia(){}
		virtual void mostrarRanking (Usuario* usuarios, int size);
		void liberarMemoriaRankingSupervivencia (Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingSupervivencia);
};
#endif