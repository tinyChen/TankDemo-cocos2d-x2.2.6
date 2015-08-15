#ifndef INCLUDED_BE_TANK_ATTACK_BEHAVIOR_H_
#define INCLUDED_BE_TANK_ATTACK_BEHAVIOR_H_

#include "BEBlockBehavior.h"

class BEMapSceneGrid;

class BETankAttackBehavior : public BEBlockBehavior
{
public:
	BETankAttackBehavior(BEMapSceneGrid *sceneGrid) 
		: BEBlockBehavior(sceneGrid), m_timeCount(0.0f), m_haveShot(false) { setInterval(0.8f); }
	~BETankAttackBehavior();

private:
	BETankAttackBehavior(const BETankAttackBehavior &behavior);
	BETankAttackBehavior &operator = (const BETankAttackBehavior &behavior);

public:
	void updateBehavior(float dt);

private:
	float m_timeCount;
	bool m_haveShot;

};
#endif