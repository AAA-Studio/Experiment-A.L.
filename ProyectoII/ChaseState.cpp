#include "ChaseState.h"
#include "EnemigoIA.h"
#include "IdleState.h"

ChaseState::ChaseState()
{
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemigoIA * character) {}

void ChaseState::Execute(EnemigoIA * character) {
	
	if (!character->IsWithinRangeOfTarget(100.0f)) {
		
		character->GetStateMachine()->ChangeState(new IdleState());

	}
}

void ChaseState::Exit(EnemigoIA * character) { }