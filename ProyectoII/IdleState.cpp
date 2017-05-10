#include "IdleState.h"
#include "EnemigoIA.h"
#include "PatrolState.h"
#include "ChaseState.h"

IdleState::IdleState()
{

}


IdleState::~IdleState()
{
	if (m_pathfinding != NULL) {
		delete m_pathfinding;
		m_pathfinding = NULL;
	}
}

void IdleState::Enter(EnemigoIA * character) {

	m_pathfinding = new PathFinding(character->getMapa());
	
	pair <float, float> targetLocation = character->findNextWayPoints();
	pair <float, float> characterLocation = make_pair(character->getRect().x, character->getRect().y);
	m_pathfinding->Initialize(characterLocation, targetLocation);

}

void IdleState::Execute(EnemigoIA * character) {

	m_pathfinding->Iterate();
	/* nuevo waypoint*/
	if (m_pathfinding->GetpathState() == PathFinding::FOUND_GOAL) {

		character->GetStateMachine()->ChangeState(
			new PatrolState(m_pathfinding->GetClosesPath()));
	}
	/* Personaje */ 
	if (character->IsWithinRangeOfTarget(100.0f)) {
		character->GetStateMachine()->ChangeState(new ChaseState());
	}
}

void IdleState::Exit(EnemigoIA * character) {

	m_pathfinding->Clear();
}