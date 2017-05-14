#ifndef _H_PatrolState_H_
#define _H_PatrolState_H_

#include "State.h" 
#include <vector>

class EnemigoIA;

class PatrolState : public State<EnemigoIA>
{
public:
	PatrolState(std::vector<std::pair <float, float>> waypoints);
	~PatrolState();

	void Enter(EnemigoIA * character);
	void Execute(EnemigoIA * character);
	void Exit(EnemigoIA * character);

private:
	std::vector<std::pair <float, float>> m_waypoints;
};

#endif
