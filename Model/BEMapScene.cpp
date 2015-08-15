#include "BEMapScene.h"
#include "BEBlockUtil.h"
#include "BEIMapSceneView.h"
#include "BEBlock.h"
#include "BEGrid.h"
#include "BETank.h"
#include "BEBlockBehavior.h"
#include "BEBlockType.h"
#include <assert.h>
#include "KeyboardUtil.h"
#include "BEBlockBehaviorManager.h"
#include "BETankMoveBehavior.h"
#include "BEBlockMoveBehavior.h"
#include "BEMapSceneGridUpdater.h"
#include "BETankStraightBullet.h"
#include "LogUtil.h"
#include "BEBlockCollisionDectector.h"
#include "BEMapSceneUtil.h"
#include "BETankAttackBehavior.h"
#include "BETankPlayer.h"

static void notifyBlockAdded(const std::vector<BEIMapSceneView *> &views, BEBlock *block, int blockType)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		views[i]->onBlockAdded(block, blockType);
	}
}

static void notifyBlockRemoved(const std::vector<BEIMapSceneView *> &views, BEBlock *block)
{
	for (size_t i = 0; i < views.size(); ++i)
	{
		views[i]->onBlockRemoved(block);
	}
}

BEMapScene::BEMapScene(const GeoSize &rect, int row, int column) : m_sceneGrid(rect, row, column)
{
	BEMapSceneGridUpdater::theUpdater()->setMapSceneGrid(&m_sceneGrid);
	BEBlockCollisionDectector::theDectector()->setMapSceneGrid(&m_sceneGrid);
	BEMapSceneUtil::setMapScene(this);
}

BEMapScene::~BEMapScene()
{}


void BEMapScene::updateScene(float dt)
{	
	BEBlockBehaviorManager::theMgr()->update(dt);
	BEBlockCollisionDectector::theDectector()->update(dt);

	static bool isKeyDown = false;
	if (KEY_DOWN(VK_RBUTTON) && !isKeyDown)
	{
		isKeyDown = true;
		m_sceneGrid.visitEveryGrid([=](int gridId)->void
		{
			BETank *tank = dynamic_cast<BETank *>((BEBlock *)(m_sceneGrid.getGridData(gridId)));
			if (tank == nullptr && hasBlock(gridId))
			{
				removeBlock(gridId);
			}
		});		
	}else if (KEY_UP(VK_RBUTTON) && isKeyDown)
	{
		isKeyDown = false;
	}
}

void BEMapScene::addBlock(int blockId, int blockType)
{	
	if (hasBlock(blockId))
	{
		assert(false && "block overlapped");
		return ;
	}
	BEBlock *block = BEBlockUtil::createBlock(blockType, blockId, &m_sceneGrid, m_sceneGrid.getGridSize());
	notifyBlockAdded(m_sceneViews, block, blockType);	
}

void BEMapScene::addEnemyTank(int blockId)
{
	if (hasBlock(blockId))
	{
		assert(false && "block overlapped");
		return;
	}
	const GeoSize &gridSize = m_sceneGrid.getGridSize();
	BEBlock *block = BEBlockUtil::createBlock(kBEBlockTypeTankEnemy, blockId, &m_sceneGrid, 
		GeoSize(gridSize.width() * 0.7f, gridSize.height() * 0.7f));	
	BETank *tank = dynamic_cast<BETank *>(block);
	tank->addBehavior(new BETankMoveBehavior(&m_sceneGrid)); 
	tank->addBehavior(new BETankAttackBehavior(&m_sceneGrid)); 
	m_tanks.push_back(tank);
	notifyBlockAdded(m_sceneViews, tank, kBEBlockTypeTankEnemy);	
}

void BEMapScene::addBullet(int blockId, BETank *tank, const GeoSize &size)
{
	const GeoSize &gridSize = m_sceneGrid.getGridSize();
	BEBlock *block = new BETankStraightBullet(size, tank);

	BETankStraightBullet *bullet = dynamic_cast<BETankStraightBullet *>(block);	
	m_bullets.push_back(bullet);
	notifyBlockAdded(m_sceneViews, bullet, kBEBlockTypeBullet);	
}

void BEMapScene::addPlayerTank(int blockId)
{
	if (hasBlock(blockId))
	{
		assert(false && "block overlapped");
		return;
	}
	const GeoSize &gridSize = m_sceneGrid.getGridSize();
	BEBlock *block = BEBlockUtil::createBlock(kBEBlockTypeTankPlayer, blockId, &m_sceneGrid, 
		GeoSize(gridSize.width() * 0.7f, gridSize.height() * 0.7f));	
	BETank *tank = dynamic_cast<BETank *>(block);
	tank->setToward(kBETowardUp);
	m_tanks.push_back(tank);
	notifyBlockAdded(m_sceneViews, tank, kBEBlockTypeTankPlayer);	
}

bool BEMapScene::hasBlock(int blockId) const
{
	return m_sceneGrid.getGridData(blockId) != nullptr;
}

void BEMapScene::removeBlock(int blockId)
{	
	BEBlock *block = (BEBlock *)(m_sceneGrid.getGridData(blockId));
	if (block)
	{		
		m_sceneGrid.removeData(blockId);
		notifyBlockRemoved(m_sceneViews, block);
		delete block;		
	}else
	{
		assert(false && "remove block failed");
	}
}

void BEMapScene::removeTank(BETank *tank)
{
	//不同的tank有可能在同个格子上
	int gridId = tank->getGridId();
	m_sceneGrid.removeData(gridId);
	for (size_t i = 0; i < m_tanks.size(); ++i)
	{
		if (m_tanks[i] == tank)
		{
			m_tanks[i]->removeBehavior();
			m_tanks[i] = m_tanks.back();
			m_tanks.resize(m_tanks.size() - 1);
			notifyBlockRemoved(m_sceneViews, tank);	
			delete tank;
			break;
		}
	}	
}

void BEMapScene::removeBullet(BETankBullet *bullet)
{
 	//子弹的数据不更新到格子
 	for (size_t i = 0; i < m_bullets.size(); ++i)
 	{
 		if (m_bullets[i] == bullet)
 		{
 			m_bullets[i] = m_bullets.back();
 			m_bullets.resize(m_bullets.size() - 1);
 			notifyBlockRemoved(m_sceneViews, bullet);	
 			delete bullet;			
 			break;
 		}
 	}	
}

void BEMapScene::removeView(BEIMapSceneView *view)
{
	for (size_t i = 0; i < m_sceneViews.size(); ++i)
	{
		if (view == m_sceneViews[i])
		{
			m_sceneViews[i] = m_sceneViews.back();
			m_sceneViews.resize(m_sceneViews.size() - 1);
			break;
		}
	}
}