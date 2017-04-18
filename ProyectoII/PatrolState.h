#ifndef _H_PatrolState_H_
#define _H_PatrolState_H_

#include "State.h" 
#include <vector>
#include "MathCore.h"
using namespace std;
class EnemigoIA;

class PatrolState : public State<EnemigoIA>
{
public:
	PatrolState(vector<Vector2> waypoints);
	~PatrolState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);

private:
	vector<Vector2> m_waypoints;
};
#endif
