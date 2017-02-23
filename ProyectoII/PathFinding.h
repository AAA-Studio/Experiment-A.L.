#ifndef _H_PathFinding_H_
#define _H_PathFinding_H_

#include "Vector3.h"
#include <vector>
#include "SearchCell.h"
class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void FindPath(Vector3 currentPos, Vector3 targetPos);
	Vector3 NextPathPos();
	void ClearOpenList() { m_openList.clear(); }
	void ClearVisitedList() { m_visitedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	bool m_initialezStarGoal;
	bool m_foundGoal;

private:
	void SetStartAndGoal(SearchCell start, SearchCell goal);
	void Pathopened(int x, int z, float newCost, SearchCell *pPadre);
	// Minuto 14:47 del tutorial
};
#endif

