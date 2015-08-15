#ifndef INCLUDED_BE_TANK_MANUAL_ATTACK_BEHAVIOR_H_
#define INCLUDED_BE_TANK_MANUAL_ATTACK_BEHAVIOR_H_

#include "BEBlockBehavior.h"

class BEMapSceneGrid;

class BETankManualAttackBehavior : public BEBlockBehavior
{
public:
	BETankManualAttackBehavior(BEMapSceneGrid *sceneGrid) 
		: BEBlockBehavior(sceneGrid), m_timeCount(0.0f), m_haveShot(false) { setInterval(0.5f); }
	~BETankManualAttackBehavior();

private:
	BETankManualAttackBehavior(const BETankManualAttackBehavior &behavior);
	BETankManualAttackBehavior &operator = (const BETankManualAttackBehavior &behavior);

public:
	void updateBehavior(float dt);

private:
	float m_timeCount;
	bool m_haveShot;

};
#endif