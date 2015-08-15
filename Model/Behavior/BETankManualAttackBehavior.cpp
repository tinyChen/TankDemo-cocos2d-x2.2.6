#include "BETankManualAttackBehavior.h"
#include "BETank.h"
#include "BEGridUtil.h"
#include "BEMapSceneGrid.h"
#include "BEMapSceneUtil.h"
#include "LogUtil.h"
#include "KeyboardListenerUtil.h"

void BETankManualAttackBehavior::updateBehavior(float dt)
{
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

	BEBlock *block = getBlock();
	if (block == nullptr) return;

	BETank *tank = dynamic_cast<BETank *>(block);
	if (tank == nullptr) return;

	if (KeyboardListenerUtil::isKeyDown('A'))
	{
		BEMapSceneUtil::addBullet(tank->getGridId(), tank, GeoSize(20, 20));
		m_haveShot = true;
	}
}

BETankManualAttackBehavior::~BETankManualAttackBehavior()
{

}