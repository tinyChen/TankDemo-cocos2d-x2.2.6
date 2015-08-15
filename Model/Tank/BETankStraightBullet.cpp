#include "BETankStraightBullet.h"
#include "BEBlockBehaviorManager.h"
#include "BEBlockMoveBehavior.h"
#include "GeoSize.h"
#include "BEIBulletView.h"
#include "BEBlockCollisionDectector.h"
#include <cassert>
#include "BEMapSceneGrid.h"
#include "BEMapSceneUtil.h"
#include "BETank.h"
#include "BEUnobstructedBlock.h"
#include "BEBlockUtil.h"
#include "BETankPlayer.h"
#include "BETankEnemy.h"
#include "BEFriableBlock.h"

static void notifyBulletPositionChanged(const std::vector<BEIBulletView *> &views, const GeoPoint &position, int toward)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		views[i]->onBulletPositionChanged(position, toward);
	}
}

static void removeBullet(BEBlock *block)
{
	BEBlockBehaviorManager::theMgr()->removeBehavior(block);
	BEBlockCollisionDectector::theDectector()->removeBlock(block);
	BETankBullet *bullet = dynamic_cast<BETankBullet *>(block);
	BEMapSceneUtil::removeBullet(bullet);
}

BETankStraightBullet::BETankStraightBullet(const GeoSize &size, BETank *tank, float damage, float speed)
	: m_damage(damage), m_tank(tank), m_speed(speed), BETankBullet(size)
{
	m_toward = m_tank->getToward();
	const GeoSize &tankSize = m_tank->getSize();
	setPosition(BEBlockUtil::getBlockPositionByOffset(m_tank->getPosition(), tankSize.width() * 0.8f, m_toward));
	BEBlockMoveBehavior *moveBehavior = new BEBlockMoveBehavior(BEMapSceneUtil::getMapSceneGrid(), m_speed, m_toward);
	BEBlockBehaviorManager::theMgr()->addBehavior(moveBehavior, this);
	moveBehavior->setBehaviorEndedCallback([=](BEBlock *block)
	{
		removeBullet(block);
	});
	
	BEBlockCollisionDectector::theDectector()->addBlock(this, [=](BEBlock *block, BEBlock *cBlock)
	{
		BEUnobstructedBlock *uBlock = dynamic_cast<BEUnobstructedBlock *>(cBlock);
		if (uBlock) { removeBullet(block); return; }

		BETankEnemy *enemyTank = dynamic_cast<BETankEnemy *>(cBlock);
		if (enemyTank)
		{
			BETankEnemy *myTank = dynamic_cast<BETankEnemy *>(m_tank);
			if (!myTank)
			{
				BEMapSceneUtil::removeTank(enemyTank);
			}
			removeBullet(block);
			return;
		}
		BETankPlayer *playerTank = dynamic_cast<BETankPlayer *>(cBlock);
		if (playerTank)
		{
			BEMapSceneUtil::removeTank(playerTank);
			removeBullet(block);
			return;
		}
		BEFriableBlock *fblock = dynamic_cast<BEFriableBlock *>(cBlock);
		if (fblock)
		{
			BEMapSceneUtil::removeBlock(fblock->getGridId());
			removeBullet(block);
			return;
		}
	});
}

BETankStraightBullet::~BETankStraightBullet()
{

}

void BETankStraightBullet::setPosition(const GeoPoint &position)
{
	BEObstructedBlock::setPosition(position);
	notifyBulletPositionChanged(m_views, position, m_toward);
}

void BETankStraightBullet::removeView(BEIBulletView *view)
{
	for (size_t i = 0; i < m_views.size(); ++i)
	{
		if (m_views[i] == view)
		{
			m_views[i] = m_views.back();
			m_views.resize(m_views.size() - 1);
			break;
		}
	}
}
