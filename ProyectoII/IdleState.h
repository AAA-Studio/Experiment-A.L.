#ifndef _H_IdleState_H_
#define _H_IdleState_H_

#include "State.h" 
#include "PathFinding.h"

template<class character_type>

class IdleState : public State<character_type>
{
public:
	IdleState();
	~IdleState();

	void Enter(character_type * character);
	void Execute(character_type * character);
	void Exit(character_type * character);

private:

	PathFinding* m_pathfinding;
};
#endif
