#ifndef _H_SearchCell_H_
#define _H_SearchCell_H_

#include "checkML.h"
#include <SDL.h>
#include <math.h>

// Tamaño del mundo
#define WORLD_SIZE 80
// El mundo se divide en celdas donde el enemigo puede estar
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
	int GetCellX(float x) { return x / CELL_SIZE; }
	int GetCellZ(float z) { return z / CELL_SIZE; }

	// ¿por que ManHattanDistance?: https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
	float ManHattanDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (float)(fabsf((this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabsf((this->m_zcoord - nodeEnd->m_zcoord)));
		return x + z;
	}
	// ChebySev Distance: https://en.wikipedia.org/wiki/Chebyshev_distance
	unsigned int ChebySevDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (float)(fabsf((this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabsf((this->m_zcoord - nodeEnd->m_zcoord)));
		return (unsigned int)(x - z);
	}
	
	~SearchCell();
};
#endif
