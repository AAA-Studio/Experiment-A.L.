#include "ChaseState.h"
#include "EnemigoIA.h"
#include "IdleState.h"

ChaseState::ChaseState()
{
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemigoIA * character) {
	character->SetMaxVelocity(125.0f);
}

void ChaseState::Execute(EnemigoIA * character) {
	
	character->ChaseTarget();
	if (!character->IsWithinRangeOfTarget(150.0f)) {
		character->GetStateMachine()->ChangeState(new IdleState());
	}
}

void ChaseState::Exit(EnemigoIA * character) {
	character->SetVelocity(0, 0);
}