#include "ChaseState.h"
#include "EnemigoIA.h"
#include "IdleState.h"

ChaseState::ChaseState() : State<EnemigoIA>()
{
}

ChaseState::~ChaseState()
{
}

void ChaseState::Enter(EnemigoIA * character) {
	character->SetMaxVelocity(0.2f);
}

void ChaseState::Execute(EnemigoIA * character) {
	
	character->ChaseTarget();
	
	if (!character->IsWithinRangeOfTarget(150.0f)) {
		character->GetStateMachine()->ChangeState(new IdleState());
		return;
	} 	
}

void ChaseState::Exit(EnemigoIA * character) {
	character->SetVelocity(0, 0);
}