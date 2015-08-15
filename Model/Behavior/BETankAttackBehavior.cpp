#include "BETankAttackBehavior.h"
#include "BETank.h"
#include "BEGridUtil.h"
#include "BEMapSceneGrid.h"
#include "BEMapSceneUtil.h"
#include "LogUtil.h"
#include "BETankPlayer.h"
#include "BETankEnemy.h"

void BETankAttackBehavior::updateBehavior(float dt)
{
	BEBlock *block = getBlock();
	if (block == nullptr) return;

	BETank *tank = dynamic_cast<BETank *>(block);
	if (tank == nullptr) return;

	if (m_haveShot)
	{
		if ((m_timeCount += dt) > getInterval()) 
		{
			m_timeCount = 0.0f;
			m_haveShot = false;
		}else
		{
			return;
		}
	}

	int hatredScope = 3;
	int toward = tank->getToward();
	int gridId = tank->getGridId();
	BEMapSceneGrid *sceneGrid = getMapSceneGrid();
	const std::vector<int> &gridScope = BEGridUtil::getGridScopeByStep(sceneGrid, gridId, toward, hatredScope);
	for (size_t i = 0; i < gridScope.size(); ++i)
	{
		BEObstructedBlock *block = dynamic_cast<BEObstructedBlock *>((BEBlock *)(sceneGrid->getGridData(gridScope[i])));
		if (!block) continue;
		BETankPlayer *player = dynamic_cast<BETankPlayer *>(block);	
		BETankEnemy *enemy = dynamic_cast<BETankEnemy *>(block);
		if (player || !enemy)
		{
			LogUtil::log("find enemy");
			m_haveShot = true;
			BEMapSceneUtil::addBullet(gridId, tank, GeoSize(20, 20));
			break;
		}	
	}
}

BETankAttackBehavior::~BETankAttackBehavior()
{

}