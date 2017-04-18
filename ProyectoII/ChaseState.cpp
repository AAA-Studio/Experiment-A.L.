#include "ChaseState.h"
#include "EnemigoIA.h"
#include "IdleState.h"

ChaseState::ChaseState()
{
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemyIA * character) {}

void ChaseState::Execute(EnemyIA * character) {

	if (!character->IsWithinRangeOfTarget(100.0f)) {
		
		character->GetStateMachine()->ChangeState(new IdleState());

	}
}

void ChaseState::Exit(EnemyIA * character) { }