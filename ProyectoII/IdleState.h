#ifndef _H_IdleState_H_
#define _H_IdleState_H_

#include "State.h" 
#include "PathFinding.h"

class EnemigoIA;

class IdleState : public State<EnemigoIA>
{
public:
	IdleState();
	~IdleState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);

private:

	PathFinding* m_pathfinding = nullptr;
};
#endif
