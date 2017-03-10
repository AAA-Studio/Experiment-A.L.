#ifndef _H_PathFinding_H_
#define _H_PathFinding_H_

#include "checkML.h"
#include "SearchCell.h"
#include "MathCore.h"
#include "Enemigo.h"
#include "Mapa.h"
#include <vector>
using namespace std;

/*
Pathfinding por niveles para que sea rapido
Hay que ver si hat linea recta contra el personaje, buscar lo qye hay que esquivar
NathPoints, hago una lista de nathpoints y eso es lo que comprueba el enemigo
*/

class PathFinding
{
public:
	PathFinding(/*Mapa * pGameWorld*/);
	~PathFinding();

	// Este metodo utiliza las coordenadas del enemigo y las del jugador para crear el camino optimo
	void FindPath(Vector3 currentPos, Vector3 targetPos);

	void DrawDebug();

	// Devuelve la posicion del camino mas corto
	Vector3 NextPathPos(Enemigo* enemigo);
	// Limpia las diferentes listas
	void ClearOpenList() { m_openList.clear(); }
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	void DrawDebug();
	// Comprueba que se han inicializado el personaje
	bool m_initializedStartGoal;
	// Personaje encontrado
	bool m_foundGoal;


private:

	void SetStartAndGoal(SearchCell start, SearchCell goal);
	// Comprueba que la actual celda esta en m_openList
	void PathOpened(int x, int z, float newCost, SearchCell *pPadre);
	// Busca a lo largo del mundo el Goal para seguir en el camino optimo
	void ContinuePath();

	// Mapa * _pGameWorld;

	SearchCell * GetNextCell();

	// Primera celda donde se encuentra el enemigo
	SearchCell * m_startCell;

	// Celda donde se encuentra el personaje
	SearchCell * m_goalCell;

	SearchCell * m_GameWorld;

	// Celdas sin visitar
	vector <SearchCell*> m_openList;

	// Celdas visitadas
	vector <SearchCell*> m_visitedList;

	// Camino optimo al personaje
	vector <Vector3 *> m_pathToGoal;

};
#endif

