#include "BETankManualMoveBehavior.h"
#include "KeyboardListenerUtil.h"
#include "BETank.h"
#include "BEBlockUtil.h"
#include "BEGridUtil.h"
#include "BEMapSceneUtil.h"
#include "BEGrid.h"
#include "BEMapSceneGrid.h"
#include "BETankPlayer.h"
#include "GeoRect.h"
#include "LogUtil.h"

static bool updateTankToward(BETank *tank)
{
	if (KeyboardListenerUtil::isKeyDown('S'))
	{
		tank->setToward(kBETowardLeft);		
	}else if (KeyboardListenerUtil::isKeyDown('D'))
	{
		tank->setToward(kBETowardDown);	
	}else if (KeyboardListenerUtil::isKeyDown('F'))
	{
		tank->setToward(kBETowardRight);	
	}else if (KeyboardListenerUtil::isKeyDown('E'))
	{
		tank->setToward(kBETowardUp);	
	}else
	{
		return false;
	}
	return true;
}

void BETankManualMoveBehavior::updateBehavior(float dt)
{
	BETank *tank = dynamic_cast<BETank *>(getBlock());
	if (tank == nullptr) return;

	if (updateTankToward(tank))
	{
		BEMapSceneGrid *sceneGrid = getMapSceneGrid();
		const std::vector<int> &gridIds = BEGridUtil::getFrontGridIds(sceneGrid, tank->getGridId(), tank->getToward(), 2);
		const GeoPoint &pos = BEBlockUtil::getBlockPositionByOffset(tank->getPosition(), tank->getMovingSpeed(), tank->getToward());
		const GeoSize &tankSize = tank->getSize();
		GeoRect boudingBox = GeoRect(GeoPoint(pos.x() - tankSize.width() * 0.5f, pos.y() + tankSize.height() * 0.5f),
			GeoPoint(pos.x() + tankSize.width() * 0.5f, pos.y() - tankSize.height() * 0.5f));
		
		for (size_t i = 0; i < gridIds.size(); ++i)
		{
			BEObstructedBlock *rb = dynamic_cast<BEObstructedBlock *>((BEBlock *)sceneGrid->getGridData(gridIds[i]));
			if (rb && rb->getBoundingBox().isIntersectant(boudingBox)) 
			{
				GeoRect tankRect = tank->getBoundingBox();
				const GeoPoint &tankPos = tank->getPosition();
				LogUtil::log("tank: leftTop = (%.f, %.f), rightBottom = (%.f, %.f), pos = (%.f, %.f), gridId = %d", tankRect.getLeftTop().x(), 
					tankRect.getLeftTop().y(), tankRect.getRightBottom().x(), tankRect.getRightBottom().y(), tankPos.x(),
					tankPos.y(), tank->getGridId());
				GeoRect blockRect = rb->getBoundingBox();
				const GeoPoint &blockPos = rb->getPosition();
				LogUtil::log("block: leftTop = (%.f, %.f), rightBottom = (%.f, %.f), pos = (%.f, %.f), gridId = %d", blockRect.getLeftTop().x(), 
					blockRect.getLeftTop().y(), blockRect.getRightBottom().x(), blockRect.getRightBottom().y(), blockPos.x(),
					blockPos.y(), rb->getGridId());
				return;
			}
		}
		tank->setPosition(BEBlockUtil::getBlockPositionByOffset(tank->getPosition(), tank->getMovingSpeed(), tank->getToward()));
	}
}