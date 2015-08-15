#include "BEBlockMoveBehavior.h"
#include "BEBlockMover.h"
#include "BEBlockBehaviorManager.h"
#include <cassert>

BEBlockMoveBehavior::BEBlockMoveBehavior(BEMapSceneGrid *sceneGrid, float movingSpeed, int toward)
	 : BEBlockBehavior(sceneGrid), m_movingSpeed(movingSpeed), m_toward(toward), m_mover(nullptr), m_timeCount(0.0f)
	 , m_callback(nullptr)
{	
}

BEBlockMoveBehavior::~BEBlockMoveBehavior()
{
	if (m_mover) delete m_mover;
}

void BEBlockMoveBehavior::setBlock(BEBlock *block)
{
	BEBlockBehavior::setBlock(block);

	if (m_mover) delete m_mover;

	m_mover = new BEBlockMover(block, getMapSceneGrid());
	m_mover->setMovingSpeed(m_movingSpeed);
	m_mover->setTargetToward(m_toward);
	m_mover->setTankReachDestinationCallback([=](BEBlock *tank)
	{
		if (m_callback) m_callback(tank);
	});
}

void BEBlockMoveBehavior::updateBehavior(float dt)
{
	m_mover->update(dt);
}