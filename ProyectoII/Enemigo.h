#ifndef _H_Enemigo_H_
#define _H_Enemigo_H_

#include "checkML.h"
#include "Entidad.h"
#include "MathCore.h"
#include "Pathfinding.h"
#include <vector>

#define M_PI 3.1416

class Enemigo: public Entidad
{
	/*enum PathState
	{
		CHECK_AROUND,
		RANDOMIZE,
		SEARCHING,
		FOUND_GOAL,
	};
	PathState m_pathState;
	PathFinding * m_pathfinding;*/
public:

	enum State {
		IDLE, 
		PATROL,
	};

	Enemigo(Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto, vector <Vector2> waypoints);
	//Enemigo(vector <Vector2> waypoints);
	virtual ~Enemigo();

	//virtual void Draw();
	virtual void Initialize();
	virtual void Update();

private: 

	Vector2 findNextWayPoints();

	State m_currentState;
	vector <Vector2> m_waypoints;
	Vector2 m_currentWayPoint;
	int m_currentIndex;
	float m_idleTime;
	/*virtual bool HandleKeydown(int key);
	virtual bool HandleKeyUp(int key);
	virtual void HandleMouseDown(bool isLeft, Vector3 mouseWorldPos);*/

	/*double radius;
	Vector3 pos;

private: 
	bool hasBeenHit;
	bool isAtGoal;
	bool lockedGuard;
	float regainControllerTimer;
	int angle;
	const float LASER_SIGTH_DIST = 500.0f;

	void RandomizeGoal();
	bool GetEnemyView(const Vector3 &targetPos);
	void SetTargetTurretAngle(float angulos) { angle = angulos; }
	inline float GetTargetTurretAngle() const { return angle; }
	float rad2deg(double rad) { // de radianes a grados
		double deg = 0;
		deg = rad * (180/M_PI);
		return deg;
	}

	Vector3 targetPos;*/
};
#endif
