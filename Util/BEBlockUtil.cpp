#include "BEBlockUtil.h"
#include "BEBlockView.h"
#include "BEBlockType.h"
#include "BEUnobstructedBlock.h"
#include "BEObstructedBlock.h"
#include "BEFriableBlock.h"
#include "BERigidBlock.h"
#include "BEGrassBlock.h"
#include "BEMetalBlock.h"
#include "BEWallBlock.h"
#include "BETank.h"
#include "BETankEnemyView.h"
#include "BEGrid.h"
#include "BEMapSceneGrid.h"
#include "BEBulletView.h"
#include <assert.h>
#include "BETankPlayerView.h"
#include "BETankPlayer.h"
#include "BETankEnemy.h"

BEBlock *BEBlockUtil::createBlock(int blockType, const GeoSize &rect)
{
	switch(blockType)
	{
	case kBEBlockTypeGrass:
		return new BEUnobstructedBlock(rect);
	case kBEBlockTypeMetal:
		return new BERigidBlock(rect);
	case kBEBlockTypeWall:
		return new BEFriableBlock(rect);
	case kBEBlockTypeTankEnemy:
		return new BETankEnemy(rect);
	case kBEBlockTypeBullet:
		assert(false && "to do");
		return nullptr;
	case kBEBlockTypeTankPlayer:
		return new BETankPlayer(rect);
	default:
		assert(false && "illegal block type");
	}
	return nullptr;
}

BEBlock *BEBlockUtil::createBlock(int blockType, int blockId, BEMapSceneGrid *sceneGrid, const GeoSize &size)
{
	BEBlock *block = createBlock(blockType, size);
	block->setGridId(blockId);
	block->setPosition(sceneGrid->getGrid(blockId)->getPosition());	
	sceneGrid->setData(blockId, block);
	return block;
}

BEBlockView *BEBlockUtil::createBlockView(int blockType, BEBlock *block)
{
	switch(blockType)
	{
	case kBEBlockTypeGrass:
		return BEGrassBlock::create(block);
	case kBEBlockTypeMetal:
		return BEMetalBlock::create(block);
	case kBEBlockTypeWall:
		return BEWallBlock::create(block);
	case kBEBlockTypeTankEnemy:
		return BETankEnemyView::create(block);
	case kBEBlockTypeBullet:
		return BEBulletView::create(block);
	case kBEBlockTypeTankPlayer:
		return BETankPlayerView::create(block);
	default:
		assert(false && "illegal block type");
	}
	return nullptr;
}

void BEBlockUtil::setBlockPositionByToward(BEBlock *block, float movingSpeed, int toward)
{	
	const GeoPoint &position = block->getPosition();
	switch (toward)
	{
	case kBETowardLeft:
		block->setPosition(GeoPoint(position.x() - movingSpeed, position.y()));
		break;
	case kBETowardUp:
		block->setPosition(GeoPoint(position.x(), position.y() + movingSpeed));
		break;
	case kBETowardRight:
		block->setPosition(GeoPoint(position.x() + movingSpeed, position.y()));
		break;
	case kBETowardDown:
		block->setPosition(GeoPoint(position.x(), position.y() - movingSpeed));
		break;
	default:
		assert(false && "illegal toward");
	}
}

const GeoPoint &BEBlockUtil::getBlockPositionByOffset(const GeoPoint &position, float offest, int toward)
{
	static GeoPoint s_pos;
	s_pos.setX(position.x());
	s_pos.setY(position.y());
	switch (toward)
	{
	case kBETowardLeft:
		s_pos.setX(s_pos.x() - offest);
		break;
	case kBETowardUp:
		s_pos.setY(s_pos.y() + offest);
		break;
	case kBETowardRight:
		s_pos.setX(s_pos.x() + offest);
		break;
	case kBETowardDown:
		s_pos.setY(s_pos.y() - offest);
		break;
	default:
		assert(false && "illegal toward");
	}
	return s_pos;
}
