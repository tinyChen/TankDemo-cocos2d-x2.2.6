#ifndef INCLUDED_BE_TANK_MANUAL_MOVE_BEHAVIOR_H_
#define INCLUDED_BE_TANK_MANUAL_MOVE_BEHAVIOR_H_

#include "BEBlockBehavior.h"

class BEMapSceneGrid;

class BETankManualMoveBehavior : public BEBlockBehavior
{
public:
	BETankManualMoveBehavior(BEMapSceneGrid *sceneGrid) : BEBlockBehavior(sceneGrid) {}
	~BETankManualMoveBehavior() {}

public:
	void updateBehavior(float dt);

private:

};

#endif