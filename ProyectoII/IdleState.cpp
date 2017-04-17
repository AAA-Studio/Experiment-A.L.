#include "IdleState.h"

template<class character_type>
IdleState::IdleState()
{


}

template<class character_type>
IdleState::~IdleState()
{

	if (m_pathfinding != NULL) {
		delete m_pathfinding;
		m_pathfinding = NULL;
	}
}

template<class character_type>
void IdleState<character_type>::Enter(character_type * character) {

	Vector2 targetLocation = character->getEntidad()->findNextWayPoints();
	m_pathfinding->Initialize(Vector2(character->getEntidad()->getPosition().GetX(),
		character->getEntidad()->getPosition().GetY()), targetLocation);

}

template<class character_type>
void IdleState<character_type>::Execute(character_type * character) {

	m_pathfinding->Iterate();

	if (m_pathfinding->GetpathState() == PathFinding::FOUND_GOAL) {

		//m_currentState = PATROL;
	}

}

template<class character_type>
void IdleState<character_type>::Exit(character_type * character) { }