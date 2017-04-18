#ifndef _H_ChaseState_H_
#define _H_ChaseState_H_

#include "State.h" 

class EnemyIA;

class ChaseState : public State<EnemyIA>
{
public:
	ChaseState();
	~ChaseState();

	void Enter(EnemyIA * character);
	void Execute(EnemyIA * character);
	void Exit(EnemyIA * character);
};
#endif
