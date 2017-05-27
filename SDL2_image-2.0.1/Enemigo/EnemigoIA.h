#ifndef _H_EnemigoIA_H_
#define _H_EnemigoIA_H_

#include "Enemigo.h"
#include "StateMachine.h"
#include "MathCore.h"
#include <vector>

#define M_PI 3.1416

class EnemigoIA: public Entidad
{
public:

	EnemigoIA();
	EnemigoIA(/*Juego*pJ, int x, int y, Texturas_t textura, Efectos_t efecto,*/Entidad * pEntidad);
	~EnemigoIA();

	void Initialize();
	void Update();
	void ChaseTarget();
	bool IsWithinRangeOfTarget(float minDistance);
	StateMachine<EnemigoIA>* GetStateMachine();
	Vector2 findNextWayPoints();
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetVelocity(float velocityX, float velocityY) { m_velocity.m_x = velocityX; m_velocity.m_y = velocityY; }
	Vector2 getPosition() const
	{
		return Vector2(posX, posY);
	}

protected: 
	StateMachine<EnemigoIA>* m_stateMachine;
	vector <Vector2> m_waypoints; // Celdas por donde pasa el enemigo
	float m_maxVelocity;
	Vector2 m_velocity;

	// Sobran algunas, comprobar cuales
	Entidad * m_entidad;
	State m_currentState;
	vector <Vector2> m_waypoints; // Celdas por donde pasa el enemigo
	Vector2 * m_currentWayPoint;
	Entidad* m_target;
	int m_currentIndex;
	float m_idleTime;
	float m_maxVelocity;
	Vector2 m_velocity;
	SDL_Rect* m_transform;

private:

	int angle;
	const float LASER_SIGTH_DIST = 500.0f;

	void RandomizeGoal();
	bool GetEnemyView(const Vector2 &targetPos);
	void SetTargetTurretAngle(float angulos) { angle = angulos; }
	inline float GetTargetTurretAngle() const { return angle; }
	float rad2deg(double rad) { // de radianes a grados
		double deg = 0;
		deg = rad * (180 / M_PI);
		return deg;
	}

	Vector2 targetPos;
};
#endif
