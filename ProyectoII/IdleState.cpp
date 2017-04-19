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

	m_pathfinding = new PathFinding();

	Vector2 targetLocation = character->findNextWayPoints();
	m_pathfinding->Initialize(Vector2(character->getEntity()->getPosition().GetX(),
		character->getEntity()->getPosition().GetY()), targetLocation);

}

void IdleState::Execute(EnemigoIA * character) {

	m_pathfinding->Iterate();

	if (m_pathfinding->GetpathState() == PathFinding::FOUND_GOAL) {

		character->GetStateMachine()->ChangeState(
			new PatrolState(m_pathfinding->GetClosesPath()));
	}

	if (character->IsWithinRangeOfTarget(100.0f)) {
		character->GetStateMachine()->ChangeState(new ChaseState());
	}

}

void IdleState::Exit(EnemigoIA * character) {

	m_pathfinding->Clear();
}