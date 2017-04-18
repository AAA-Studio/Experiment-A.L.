#ifndef _H_ChaseState_H_
#define _H_ChaseState_H_

#include "State.h" 


using namespace std;
class EnemigoIA;

class ChaseState : public State<EnemigoIA>
{
public:
	ChaseState();
	~ChaseState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);
};
#endif
