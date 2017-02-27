#ifndef _H_SearchCell_H_
#define _H_SearchCell_H_

#include <SDL.h>
#include <math.h>

#define WORLD_SIZE 80
#define CELL_SIZE 20

class SearchCell
{
public:
	
	int m_xcoord, m_zcoord;
	int m_id;
	SearchCell * pPadre;
	float G; // distancia acumulada desde la primera celda hasta la celda en la que te encuentras
	float H; // distancia estimada al objetivo

	SearchCell() : pPadre(0){};
	SearchCell(int x, int z, SearchCell * parent = nullptr) : m_xcoord(x), m_zcoord(z),
		pPadre(parent), m_id(z * WORLD_SIZE + x), G(0), H(0){};


	float GetF(){ return G + H; }

	// ¿por que ManHattanDistance?: https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
	float ManHattanDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (float)(fabsf((this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabsf((this->m_zcoord - nodeEnd->m_zcoord)));
		return x + z;
	}
	
	~SearchCell();
};
#endif
