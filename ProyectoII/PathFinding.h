#ifndef _H_PathFinding_H_
#define _H_PathFinding_H_

#include "SearchCell.h"
#include "MathCore.h"
#include <vector>
using namespace std;

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	// Este metodo utiliza las coordenadas del enemigo y las del jugador para crear el camino optimo
	void FindPath(Vector3 currentPos, Vector3 targetPos);
	// Devuelve la posicion del camino mas corto
	Vector3 NextPathPos();
	// Limpia la lista
	void ClearOpenList() { m_openList.clear(); }
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	// Comprueba que se han inicializado el Goal
	bool m_initializedStartGoal;
	bool m_foundGoal;

private:

	void SetStartAndGoal(SearchCell start, SearchCell goal);
	// Comprueba que la actual celda esta en m_openList
	void PathoOpened(int x, int z, float newCost, SearchCell *pPadre);
	// Busca a lo largo del mundo el Goal para seguir en el camino optimo
	void ContinuePath();

	SearchCell * GetNextCell();
	SearchCell * m_startCell;
	SearchCell * m_goalCell;
	vector <SearchCell*> m_openList;
	vector <SearchCell*> m_visitedList;
	vector <Vector3 *> m_pathToGoal;

};
#endif

