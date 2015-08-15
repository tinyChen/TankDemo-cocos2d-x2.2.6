#ifndef INCLUDED_BE_TANK_MOVE_BEHAVIOR_H_
#define INCLUDED_BE_TANK_MOVE_BEHAVIOR_H_

#include "BEBlockBehavior.h"

class BEMapSceneGrid;
class BETankPathFinder;
class BEBlockMover;
class BETank;

class BETankMoveBehavior : public BEBlockBehavior
{
public:
	BETankMoveBehavior(BEMapSceneGrid *sceneGrid) 
		: BEBlockBehavior(sceneGrid), m_targetGridId(-1), m_targetToward(-1), m_mover(nullptr), m_finder(nullptr), m_timeCount(0.0f) {}
	~BETankMoveBehavior();

private:
	BETankMoveBehavior(const BETankMoveBehavior &behavior);
	BETankMoveBehavior &operator = (const BETankMoveBehavior &behavior);

public:
	int getTargetGridId() const { return m_targetGridId; }
	int getTargetToward() const { return m_targetToward; }
	
	void setBlock(BEBlock *tank);
	void updateBehavior(float dt);

private:
	int m_targetGridId;
	int m_targetToward;
	BETankPathFinder *m_finder;
	BEBlockMover *m_mover;
	float m_timeCount;
};

#endif