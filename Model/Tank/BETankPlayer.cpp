#include "BETankPlayer.h"
#include "BETankManualMoveBehavior.h"
#include "BEMapSceneGrid.h"
#include "BEMapSceneUtil.h"
#include "BEBlockBehaviorManager.h"
#include "BETankManualAttackBehavior.h"

BETankPlayer::BETankPlayer(const GeoSize &size) : BETank(size)
{
	BEBlockBehavior *mb = new BETankManualMoveBehavior(BEMapSceneUtil::getMapSceneGrid());
	BEBlockBehaviorManager::theMgr()->addBehavior(mb, this);
	BEBlockBehavior *ab = new BETankManualAttackBehavior(BEMapSceneUtil::getMapSceneGrid());
	BEBlockBehaviorManager::theMgr()->addBehavior(ab, this);
}