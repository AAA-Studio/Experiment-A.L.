#include "ChaseState.h"

template<class character_type>
ChaseState::ChaseState()
{
}

template<class character_type>
ChaseState::~ChaseState()
{
}

template<class character_type>
void IdleState<character_type>::Enter(character_type * character) {}

template<class character_type>
void IdleState<character_type>::Execute(character_type * character) {}

template<class character_type>
void IdleState<character_type>::Exit(character_type * character) { }