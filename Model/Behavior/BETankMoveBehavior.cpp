#include "BETankMoveBehavior.h"
#include "BETankPathFinder.h"
#include "BEBlockMover.h"
#include "BETank.h"

BETankMoveBehavior::~BETankMoveBehavior()
{
	if (m_finder) delete m_finder;
	if (m_mover) delete m_mover;
}

void BETankMoveBehavior::setBlock(BEBlock *block)
{
	BEBlockBehavior::setBlock(block);

	if (m_finder) delete m_finder;
	if (m_mover) delete m_mover;

	BETank *tank = dynamic_cast<BETank *>(block);
	m_finder = new BETankPathFinder(tank, getMapSceneGrid());
	m_mover = new BEBlockMover(tank, getMapSceneGrid());
	m_mover->setMovingSpeed(tank->getMovingSpeed());
	m_mover->setTankReachDestinationCallback([&](BEBlock *tank)
	{
		m_finder->update(&m_targetGridId, &m_targetToward);			
	});

	m_finder->update(&m_targetGridId, &m_targetToward);
}

void BETankMoveBehavior::updateBehavior(float dt)
{
	if (m_targetGridId >= 0)
	{	
		m_mover->setTargetGridId(m_targetGridId);
		m_mover->setTargetToward(m_targetToward);
		m_mover->update(dt);		
	}else
	{
		if ((m_timeCount += dt) > getInterval())
		{
			m_timeCount = 0.0f;
			m_finder->update(&m_targetGridId, &m_targetToward);
		}
	}
}