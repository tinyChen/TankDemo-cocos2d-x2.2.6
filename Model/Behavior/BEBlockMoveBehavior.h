#ifndef INCLUDED_BE_BLOCK_MOVE_BEHAVIOR_H_
#define INCLUDED_BE_BLOCK_MOVE_BEHAVIOR_H_

#include "BEBlockBehavior.h"
#include <functional>

class BEMapSceneGrid;
class BEBlockMover;

class BEBlockMoveBehavior : public BEBlockBehavior
{
public:
	BEBlockMoveBehavior(BEMapSceneGrid *sceneGrid, float movingSpeed, int toward);
	~BEBlockMoveBehavior();

public:
	void setBehaviorEndedCallback(std::function<void (BEBlock *)> ftn) { m_callback = ftn; }
	void setBlock(BEBlock *block);	
	void updateBehavior(float dt);

private:
	BEBlockMover *m_mover;
	float m_timeCount;
	float m_movingSpeed;
	int m_toward;
	std::function<void (BEBlock *)> m_callback;
};

#endif