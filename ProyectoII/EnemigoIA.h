#ifndef _H_EnemigoIA_H_
#define _H_EnemigoIA_H_

#include "Entidad.h"
#include "StateMachine.h"
#include "MundoVirtual.h"
#include <vector>

#define M_PI 3.1416

class EnemigoIA : public Entidad
{
public:

	EnemigoIA(MundoVirtual*pM, Entidad* target, int x, int y, int w, int h, JuegoSDL::Texturas_t textura,
		JuegoSDL::Efectos_t efecto, vector < pair<float, float>> waypoints);
	~EnemigoIA();

	void Initialize();
	virtual void update();

	void ChaseTarget();//Persigue al personaje
	bool IsWithinRangeOfTarget(float minDistance);//Devuelve true si esta en el rango con el personaje
	const pair <float, float>& findNextWayPoints();

	//GETTER
	StateMachine<EnemigoIA>* GetStateMachine();
	inline float getVida()const { return vida; };
	inline MundoVirtual* getMundo() const { return pMundo; };

	//SETTER
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	// void SetVelocity(float velocityX, float velocityY) { m_velocity.SetX(velocityX); m_velocity.SetY(velocityY); }
	void SetVelocity(float velocityX, float velocityY) { m_velocity.first = velocityX; m_velocity.second = velocityY; }


	// Auxiliar de momento
	inline std::vector<pair <float, float>> getWaypoints() const { return m_waypoints; }
	
	inline void restaVida() { vida--; };

protected: 
	StateMachine<EnemigoIA>* m_stateMachine;

	// Celdas por donde pasa el enemigo
	vector < pair<float, float>> m_waypoints;
	pair <float, float>* m_currentWayPoint;

	float m_maxVelocity;
	pair <float, float> m_velocity;

	
	Entidad* m_target = nullptr;// Puntero al personaje

	int m_currentIndex;

private:
	MundoVirtual* pMundo = nullptr;
	float vida;

	/*
	int angle;
	const float LASER_SIGTH_DIST = 500.0f;

	
	bool GetEnemyView(const Vector2 &targetPos);
	void SetTargetTurretAngle(float angulos) { angle = angulos; }
	inline float GetTargetTurretAngle() const { return angle; }
	float rad2deg(double rad) { // de radianes a grados
		double deg = 0;
		deg = rad * (180 / M_PI);
		return deg;
	}
	*/
};
#endif
