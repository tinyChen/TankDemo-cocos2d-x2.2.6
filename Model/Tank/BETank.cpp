#include "BETank.h"
#include "BEITankView.h"
#include "BEBlockBehaviorManager.h"
#include "BEBlockBehavior.h"
#include "BEMapSceneGridUpdater.h"
#include <assert.h>


static void notifyTankPositionChanged(const std::vector<BEITankView *> &views, const GeoPoint &position)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		views[i]->onTankPositionChanged(position);
	}
}

static void notifyTankTowardChanged(const std::vector<BEITankView *> &views, int toward)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		views[i]->onTankTowardChanged(toward);
	}
}

BETank::~BETank()
{
	removeBehavior();
}

void BETank::removeView(BEITankView *view)
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

void BETank::setPosition(const GeoPoint &position)
{
	BEObstructedBlock::setPosition(position);
	BEMapSceneGridUpdater::theUpdater()->updateSceneGridData(this);
	notifyTankPositionChanged(m_views, position);
}

void BETank::setToward(int toward)
{
	m_toward = toward;
	notifyTankTowardChanged(m_views, toward);
}

void BETank::addBehavior(BEBlockBehavior *behavior)
{
	assert(behavior && "null pointer is illegal");
	if (behavior == nullptr) return;

	BEBlockBehaviorManager *mgr = BEBlockBehaviorManager::theMgr();
	mgr->addBehavior(behavior, this);
}

void BETank::removeBehavior()
{
	BEBlockBehaviorManager::theMgr()->removeBehavior(this);
}