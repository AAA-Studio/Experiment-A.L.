#ifndef _H_SearchCell_H_
#define _H_SearchCell_H_

#include <SDL.h>
#include <math.h>

#define WORLD_SIZE 64

class SearchCell
{
public:
	
	int m_xcoord, m_zcoord;
	int m_id;
	SearchCell * pPadre;
	float G; // distancia
	float H; // distancia estimada al objetivo

	SearchCell() : pPadre(0){};
	SearchCell(int x, int z, SearchCell * parent = nullptr) : m_xcoord(x), m_zcoord(z),
		pPadre(parent), m_id(z * WORLD_SIZE + z), G(0), H(0){};
	float GetF(){ return G + H; }
	float ManHattanDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (fabsf(this->m_xcoord - nodeEnd->m_xcoord));
		float z = (fabsf(this->m_zcoord - nodeEnd->m_zcoord));
		return x + z;
	}
	
	~SearchCell();
};
#endif
