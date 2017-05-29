#include "PathFinding.h"
#include "Juego.h"
#include "Tile.h"
#include <stdio.h> // Input and Output operations
#include <utility>
#include <iostream>

PathFinding::PathFinding(Mapa * pGameWorld) : pMapa (pGameWorld)
{
	m_pathState = NONE;
	m_startCell = NULL;
	m_goalCell = NULL;
	m_initializedStartGoal = false;
	m_foundGoal = false;
}

void PathFinding::Initialize(pair <float, float>  pStartPos, pair <float, float>  pTargetPos) {
	
	
	m_pathState = INITIALIZE;

	m_openList.clear();
	m_visitedList.clear();
	//m_closesPath.clear();

	// Celda del enemigo
	SearchCell start;
	start.setX(floorf(pStartPos.first / (float)TILE_WIDTH));
	start.setY(floorf(pStartPos.second / (float)TILE_HEIGHT));

	// Celda objetivo
	SearchCell goal;
	goal.setX(floorf(pTargetPos.first / (float)TILE_WIDTH));
	goal.setY(floorf(pTargetPos.second / (float)TILE_HEIGHT));

	cout << "Posicion Enemigo(" << start.GetCellX() << ", " << start.GetCellY() << "); " << endl;
	InitializaStartGoal(&start, &goal);
	FindPath(pStartPos, pTargetPos);

	m_pathState = SEARCHING;
}

void PathFinding::InitializaStartGoal(SearchCell* pStart, SearchCell* pGoal) {
	// if's para asegurar que se inicializan las celdas correspondientes
	if (!m_startCell) {
		
		m_startCell = new SearchCell(pStart->GetCellX(), pStart->GetCellY(), NULL);
	}
	if (!m_goalCell) {

		m_goalCell = new SearchCell(pGoal->GetCellX(), pGoal->GetCellY(), pGoal);
	}

	// Informacion de las celdas anteriores, coordenadas e id
	m_startCell->setX((float)pStart->GetCellX());
	m_startCell->setY((float)pStart->GetCellY());
	m_startCell->SetID(pStart->GetCellY() * LEVEL_WIDTH + pStart->GetCellX());

	m_goalCell->setX((float)pGoal->GetCellX());
	m_goalCell->setY((float)pGoal->GetCellY());
	m_goalCell->SetID(pGoal->GetCellY() * LEVEL_WIDTH + pGoal->GetCellX());

	// El padre del objetivo es la celda que ocupa
	m_goalCell->SetParent(pGoal);

	m_startCell->setH(m_startCell->ManHattanDistance(m_goalCell));

	m_openList.push_back(m_startCell);
}

void PathFinding::Iterate() {

	if (m_openList.empty()) {
		m_pathState = ERROR_GOAL_NOT_FOUND;
		return;
	}
	// Siguiente celda a la que se dirige el enemigo, "avanzadilla"
	SearchCell * currentCell = GetNextCell();

	// Justo la celda siguiente a la que estamos es el personaje
	if (currentCell->GetID() == m_goalCell->GetID()) {
		m_pathState = FOUND_GOAL;
	
		m_goalCell->SetParent(currentCell);
	
		//Movimiento sin algoritmos, el iter es el personaje y guardas el camino hacia el objetivo
		for (SearchCell * iter = m_goalCell; iter != m_startCell; iter = iter->GetParent()) {
			m_closesPaths.push_back(make_pair(iter->GetCellX() * (float)TILE_WIDTH/2.0f, iter->GetCellY() * (float)TILE_HEIGHT/2.0f));
		}
	}

	else {

		float x = (float)currentCell->GetCellX();
		float y = (float)currentCell->GetCellY();
		float g = (float)currentCell->GetG();

		// Borramos las celdas de la openlist porque hemos generado otros Path.
		for (int i = 0; i < (int)m_openList.size(); i++) {
			if (currentCell->GetID() == m_openList[i]->GetID()) {
				m_openList.erase(m_openList.begin() + i);
			}
		}

		// comprueba izq
		PathOpened(x - 1, y, g + 1, currentCell);
		// comprueba drcha
		PathOpened(x + 1, y, g + 1, currentCell);
		// comprueba arriba
		PathOpened(x, y - 1, g + 1, currentCell);
		// comprueba abajo
		PathOpened(x, y + 1, g + 1, currentCell);

		
	}

}

void PathFinding::FindPath(pair <float, float> currentPos, pair <float, float> targetPos) {
	
	if (!m_initializedStartGoal) {

		// Resetea las listas de celdas para elegir el nuevo camino
		for (auto i : m_openList) {
			delete i;
		}
		m_openList.clear();
		
		for (auto i : m_visitedList) {
			delete i;
		}
		m_visitedList.clear();

		m_pathToGoal.clear();

		// Inicializacion del start
		SearchCell start;

		start.setX((float)m_GameWorld->GetCellX(currentPos.first));
		start.setY((float)m_GameWorld->GetCellY(currentPos.second));

		// Inicializacion del Goal
		SearchCell goal;

		goal.setX((float)m_GameWorld->GetCellX(targetPos.first));
		goal.setY((float)m_GameWorld->GetCellY(targetPos.second));

		m_foundGoal = false;
		SetStartAndGoal(start, goal);
		m_initializedStartGoal = true;
	}

	else {
		ContinuePath();
	}
}

void PathFinding::SetStartAndGoal(SearchCell start, SearchCell goal){
	
	m_startCell = new SearchCell(start.GetCellX(), start.GetCellY(), NULL);
	m_goalCell = new SearchCell(goal.GetCellX(), goal.GetCellY(), &goal);

	// Doy informacion a la nueva Celda, 
	// !!!!!!!!!!!!! No se crean celdas como tal, solo son para comprobar la informacion
	m_startCell->setG(0);
	m_startCell->setH(m_startCell->ManHattanDistance(m_goalCell));
	m_startCell->SetParent(nullptr);
	m_openList.push_back(m_startCell); //todas las adyacentes

}

SearchCell * PathFinding::GetNextCell(){
	
	// Comprueba la mejor F de la lista, 
	// con este numero obligamos a que se cambie por lo menos 1 vez
	float bestF = 999999.0f;

	int cellIndex = -1;
	SearchCell * nextCell = NULL;

    // Se encarga de buscar el indice con mejor distancia de la lista	
	for (int i = 0; i < (int)m_openList.size(); i++) {
		if (m_openList[i]->GetF() < bestF){
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	// Mete la informacion de la celda encontrada en el anterior for
	if (cellIndex >= 0) {
		nextCell = m_openList[cellIndex];
		m_openList.erase(m_openList.begin() + cellIndex);
		m_visitedList.push_back(nextCell);
		
	}
	return nextCell;
}

void PathFinding::PathOpened(float x, float y, float newCost, SearchCell *pPadre){
	
	if (x <= 0 || x >= LEVEL_WIDTH || y <= 0 || y >= LEVEL_HEIGHT) {
		return;
	}

	// Tile* tile = pMapa->GetTileAt((int) x, (int) y);

	SDL_Rect tile = { x, y, TILE_WIDTH, TILE_HEIGHT };
	// if (tile == NULL || pMapa->tileColision(tile)) return;
	if (pMapa->touchesWall(tile)){  
		return; 
	}

	
	// este id es solo para comprobar, no cambia el id de ninguna celda
	int id = (int)( y * LEVEL_WIDTH + x);

	// recorro la lista de visitadas hasta que coincida con el id de arriba.
	for (int i = 0; i < (int)m_visitedList.size(); i++) {
		if (id == m_visitedList[i]->GetID()) {
			return;
		}
	}

	// Celda para comprobar informacion, si cumple requisitos el Padre sera sustituido
	SearchCell * newChild = new SearchCell((int)x, (int)y, pPadre);
	
	newChild->SetID(id);
	newChild->setG(newCost);
	newChild->setH(pPadre->ManHattanDistance(m_goalCell));

	for (int i = 0; i < (int)m_openList.size(); i++) {
		if (newChild->GetID() == m_openList[i]->GetID()) {

			float newF = newChild->GetG() + newCost + m_openList[i]->GetH();

			if (m_openList[i]->GetF() > newF) {

				m_openList[i]->setG(newF);
				m_openList[i]->SetParent(newChild);
			}

			else {
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

void PathFinding::Clear() {
	
	m_pathState = NONE;

	if (m_startCell) {
		delete m_startCell;
		m_startCell = NULL;
	}

	if (m_goalCell) {
		delete m_goalCell;
		m_goalCell = NULL;
	}

	m_openList.clear();
	m_visitedList.clear();
	m_closesPaths.clear();

}

void PathFinding::ContinuePath() {
	
	if (m_openList.empty()) {
		return;
	}

	SearchCell * currentCell = GetNextCell();

	if (currentCell->GetID() == m_goalCell->GetID()) {
		m_goalCell->SetParent(currentCell->GetParent());

		SearchCell * getPath = nullptr;

		// Va por todas las celdas comprobando cual es el camino mas corto y las mete en la lista
		// va hasta NULL porque la celda Start es la unica que lo tiene a NULL
		for (getPath = m_goalCell; getPath != NULL; getPath->GetParent()) {

			m_pathToGoal.push_back(make_pair(getPath->GetCellX() * TILE_WIDTH, getPath->GetCellY() * TILE_HEIGHT));
		}

		m_foundGoal = true;
	}
	else {

		for (int i = 0; i < (int)m_openList.size(); i++)
		{
			if (currentCell->GetID() == m_openList[i]->GetID()){

				m_openList.erase(m_openList.begin() + i);

			}
		}

		// Celda derecha
		PathOpened((float)currentCell->GetCellX() + 1, (float)currentCell->GetCellY(), currentCell->GetG() + 1, currentCell);

		//Celda izquierda
		PathOpened((float)currentCell->GetCellX() - 1, (float)currentCell->GetCellY(), currentCell->GetG() + 1, currentCell);
		
		// Celda superior
		PathOpened((float)currentCell->GetCellX(), (float)currentCell->GetCellY() - 1, currentCell->GetG() + 1, currentCell);

		// Celda inferior
		PathOpened((float)currentCell->GetCellX(), (float)currentCell->GetCellY() + 1, currentCell->GetG() + 1, currentCell);

		// Celda diagonal izquierda superior								/* 1.4f es lo que vale la diagonal de la Celda */
		PathOpened((float)currentCell->GetCellX() - 1, (float)currentCell->GetCellY() - 1, currentCell->GetG() + 1.4f, currentCell);

		// Celda diagonal izquierda inferior
		PathOpened((float)currentCell->GetCellX() - 1, (float)currentCell->GetCellY() + 1, currentCell->GetG() + 1.4f, currentCell);
		
		// Celda diagonal derecha superior
		PathOpened((float)currentCell->GetCellX() + 1, (float)currentCell->GetCellY() - 1, currentCell->GetG() + 1.4f, currentCell);

		// Celda diagonal derecha inferior
		PathOpened((float)currentCell->GetCellX() + 1, (float)currentCell->GetCellY() + 1, currentCell->GetG() + 1.4f, currentCell);
		
		
	}
}

pair <float, float> PathFinding::NextPathPos(Enemigo  *enemigo) {
	
	int index = 1; 

	pair <float, float> nextPos = make_pair(m_pathToGoal[m_pathToGoal.size() - index].first, m_pathToGoal[m_pathToGoal.size() - index].second);

	// pos es la actual posicion del enemigo
	pair <float, float>enemPos(enemigo->getRect().x, enemigo->getRect().y);
	// Vector2 distance = nextPos - enemPos

	pair <float, float> toTarget = make_pair(nextPos.first - enemPos.first, nextPos.second - enemPos.second);
	float distance = sqrt((toTarget.first*toTarget.first) + (toTarget.second*toTarget.second));

	if (distance< m_pathToGoal.size()) {

		// Si el enemigo consigue avanzar en el radio de celdas elimina la que ya estaba
		if (distance < 50) {
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}

	return nextPos;
}

pair <float, float> PathFinding::GetNextClosesPoint() {
	// Siguiente paso en la lista de celdas del camino
	pair <float, float> nextPath = m_closesPaths[m_closesPaths.size() - 1];
	// borras esa celda
	m_closesPaths.erase(m_closesPaths.begin() + m_closesPaths.size() - 1);

	return nextPath;
}

int PathFinding::GetClosesPathSize() {

	return (int)m_closesPaths.size();
}

vector<pair <float, float>> PathFinding::GetClosesPath() {

	return m_closesPaths;
}

PathFinding::~PathFinding()
{
	Clear();
}
