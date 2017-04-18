#include "ChaseState.h"
#include "EnemigoIA.h"

ChaseState::ChaseState()
{
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemyIA * character) {}

void ChaseState::Execute(EnemyIA * character) {

	if (!character->IsWithinRangeOfTarget(100.0f)) {
		
	}
}

void ChaseState::Exit(EnemyIA * character) { }