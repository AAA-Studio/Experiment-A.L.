#ifndef _H_PatrolState_H_
#define _H_PatrolState_H_

#include "State.h" 

template<class character_type>

class PatrolState : public State<character_type>
{
public:
	PatrolState();
	~PatrolState();

	void Enter(character_type * character);
	void Execute(character_type * character);
	void Exit(character_type * character);
};
#endif
