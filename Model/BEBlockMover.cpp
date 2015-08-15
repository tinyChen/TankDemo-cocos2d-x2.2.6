#include "BEBlockMover.h"
#include "BEToward.h"
#include "GeoPoint.h"
#include "BETank.h"
#include "BEMapSceneGrid.h"
#include "BEGrid.h"
#include <assert.h>
#include "BEGridUtil.h"
#include "BEBlockUtil.h"

static bool isBlockInDestination(BEMapSceneGrid *sceneGrid, BEBlock *block, int targetGridId, float movingSpeed)
{
	int blockGridId = BEGridUtil::getGridIdByPosition(sceneGrid, block->getPosition());
	if (!sceneGrid->isGridIdInRange(blockGridId)) return true;
	if (!sceneGrid->isGridIdInRange(targetGridId)) return false;

	const GeoPoint &targetGridPosition = sceneGrid->getGrid(targetGridId)->getPosition();
	const GeoPoint &blockPosition = block->getPosition();
	return (abs(blockPosition.x() - targetGridPosition.x()) <= movingSpeed 
		&& abs(blockPosition.y() - targetGridPosition.y()) <= movingSpeed);
}

void BEBlockMover::update(float dt)
{
	if ((m_timeCount += dt) >= 0.005f)
	{
		m_timeCount = 0.0f;
		BEBlockUtil::setBlockPositionByToward(m_block, m_movingSpeed, m_targetToward);
		if (isBlockInDestination(m_sceneGrid, m_block, m_targetGridId, m_movingSpeed))
		{
			if (m_sceneGrid->isGridIdInRange(m_targetGridId))
			{
				const GeoPoint &targetGridPosition = m_sceneGrid->getGridPosition(m_targetGridId);
				m_block->setPosition(targetGridPosition);
			}
			if (m_callbackFtn) m_callbackFtn(m_block);			
		}
	}
}

void BEBlockMover::setTargetToward(int toward)
{
	m_targetToward = toward;
	BETank *tank = dynamic_cast<BETank *>(m_block);
	if (tank)
	{
		tank->setToward(toward);
	}	
}