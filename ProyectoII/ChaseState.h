#ifndef _H_ChaseState_H_
#define _H_ChaseState_H_

#include "State.h" 

template<class character_type>
class ChaseState: public State<character_type>
{
public:
	ChaseState();
	~ChaseState();

	void Enter(character_type * character);
	void Execute(character_type * character);
	void Exit(character_type * character);
};
#endif
