#ifndef _H_PatrolState_H_
#define _H_PatrolState_H_

#include "State.h" 
#include <vector>

using namespace std;
class EnemigoIA;

class PatrolState : public State<EnemigoIA>
{
public:
	PatrolState(vector<pair <float, float>> waypoints);
	~PatrolState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);

private:
	vector<pair <float, float>> m_waypoints;
};

#endif
