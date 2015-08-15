#include "BEMapSceneUtil.h"
#include "BEMapScene.h"
#include "BEMapSceneGrid.h"

BEMapScene *BEMapSceneUtil::s_mapScene = nullptr;

void BEMapSceneUtil::addBlock(int blockId, int blockType)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->addBlock(blockId, blockType);
}

void BEMapSceneUtil::addEnemyTank(int blockId)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->addEnemyTank(blockId);
}

void BEMapSceneUtil::addBullet(int blockId, BETank *tank, const GeoSize &size)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->addBullet(blockId, tank, size);
}

void BEMapSceneUtil::removeBullet(BETankBullet *bullet)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->removeBullet(bullet);
}

void BEMapSceneUtil::removeBlock(int blockId)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->removeBlock(blockId);
}

void BEMapSceneUtil::removeTank(BETank *tank)
{
	if (s_mapScene == nullptr) return;
	s_mapScene->removeTank(tank);
}

BEMapSceneGrid *BEMapSceneUtil::getMapSceneGrid()
{
	if (s_mapScene == nullptr) return nullptr; 
	return s_mapScene->getMapSceneGrid();
}

void BEMapSceneUtil::addPlayerTank(int blockId)
{
	if (s_mapScene == nullptr) return; 
	return s_mapScene->addPlayerTank(blockId);
}