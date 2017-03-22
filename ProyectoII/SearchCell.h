#ifndef _H_SearchCell_H_
#define _H_SearchCell_H_

#include "checkML.h"
#include <SDL.h>
#include <math.h>

// Tama�o del mundo
#define WORLD_SIZE 80
// El mundo se divide en celdas donde el enemigo puede estar
#define CELL_SIZE 20  

class SearchCell
{
public:
	
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Auxiliar que luego se tiene que quitar y usar correctamente
	enum tColor {
		ROJO,
		AZUL,
		VERDE,
	};

	enum CellState {
		CELL_BLOCKED
	};

	int m_xcoord, m_ycoord;
	int m_id;
	SearchCell * pPadre;
	float G; // distancia acumulada desde la primera celda hasta la celda en la que te encuentras
	float H; // distancia estimada al objetivo

	SearchCell() : pPadre(0){};
	SearchCell(int x, int y, SearchCell * parent = nullptr) : m_xcoord(x), m_ycoord(y),
		pPadre(parent), m_id(y * WORLD_SIZE + x), G(0), H(0){};


	inline float GetF() const { return G + H; }
	inline int GetCellX(float x) const { return floor(x / CELL_SIZE); }
	inline int GetCellY(float y) const { return floor(y / CELL_SIZE); }
	inline CellState GetCellState(float x, float y) const { 
		return CELL_BLOCKED;
	}

	void DrawSquare(int posX, int posY, tColor color) {
	
	}
	void DrawSquare(float posX, float posY, tColor color) {
	
	}
	
	
	
	// �por que ManHattanDistance?: https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
	float ManHattanDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (float)(fabsf((this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabsf((this->m_ycoord - nodeEnd->m_ycoord)));
		return x + z;
	}
	// ChebySev Distance: https://en.wikipedia.org/wiki/Chebyshev_distance
	float ChebySevDistance(SearchCell * nodeEnd) { // Distancia en la que esta el enemigo al personaje
		float x = (float)(fabsf((this->m_xcoord - nodeEnd->m_xcoord)));
		float z = (float)(fabsf((this->m_ycoord - nodeEnd->m_ycoord)));
		return floor(x - z);
	}
	
	~SearchCell();
};
#endif