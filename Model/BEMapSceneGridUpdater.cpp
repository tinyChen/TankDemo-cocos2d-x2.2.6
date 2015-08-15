#include "BEMapSceneGridUpdater.h"
#include "BEBlock.h"
#include "BEMapSceneGrid.h"
#include "BEGridUtil.h"
#include "BETank.h"
#include "BEObstructedBlock.h"
#include <cassert>

void BEMapSceneGridUpdater::updateSceneGridData(BEBlock *block)
{
	if (m_sceneGrid == nullptr) return;
	if (block == nullptr) return;

	int gridId = -1;
	BETank *tank = nullptr;
	
	if ((tank = dynamic_cast<BETank *>(block)))
	{
		gridId = BEGridUtil::getGridIdByBlock(m_sceneGrid, block, tank->getToward());
	}else
	{
		gridId = BEGridUtil::getGridIdByPosition(m_sceneGrid, block->getPosition());
	}
	if (!m_sceneGrid->isGridIdInRange(gridId))
	{
		return;
	}
	if (gridId != block->getGridId())
	{
		BEBlock *temp = (BEBlock *)(m_sceneGrid->getGridData(gridId));
		if (dynamic_cast<BETank *>(temp) == nullptr && dynamic_cast<BERigidBlock *>(temp))
		{
			assert(false && "obstructed block cannot change data");
		}
		m_sceneGrid->removeData(block->getGridId());
		m_sceneGrid->setData(gridId, block);
		block->setGridId(gridId);
	}
}
