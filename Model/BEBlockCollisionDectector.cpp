#include "BEBlockCollisionDectector.h"
#include "BEBlock.h"
#include "BEGridUtil.h"
#include "GeoRect.h"
#include "GeoSize.h"
#include "BEMapSceneGrid.h"
#include "BEUnobstructedBlock.h"

void BEBlockCollisionDectector::addBlock(BEBlock *block, std::function<void (BEBlock *, BEBlock *)> ftn)
{
	auto iter = m_blocks.find(block);
	if (iter == m_blocks.end())
	{
		m_blocks.insert(make_pair(block, ftn));
	}
}

void BEBlockCollisionDectector::removeBlock(BEBlock *block)
{
	auto iter = m_blocks.find(block);
	if (iter != m_blocks.end())
	{
		m_blocks.erase(iter);
	}
}


static bool isBlockInCollision(BEBlock *block, BEBlock *collidedBlock)
{
	const GeoPoint &cPos = collidedBlock->getPosition();
	const GeoPoint &bPos = block->getPosition();
	const GeoSize &cSize = collidedBlock->getSize();
	const GeoSize &bSize = block->getSize();
	GeoRect cRect(GeoPoint(cPos.x() - cSize.width() * 0.5f, cPos.y() + cSize.height() * 0.5f),
		GeoPoint(cPos.x() + cSize.width() * 0.5f, cPos.y() - cSize.height() * 0.5f));
	GeoRect bRect(GeoPoint(bPos.x() - bSize.width() * 0.5f, bPos.y() + bSize.height() * 0.5f),
		GeoPoint(bPos.x() + bSize.width() * 0.5f, bPos.y() - bSize.height() * 0.5f));
	return cRect.isIntersectant(bRect);
}

void BEBlockCollisionDectector::update(float dt)
{
	if (m_sceneGrid == nullptr) return;

	for (auto iter = m_blocks.begin(); iter != m_blocks.end(); ++iter)
	{
		BEBlock *block = iter->first;
		if (block == nullptr) continue;
		if (dynamic_cast<BEUnobstructedBlock *>(block)) continue;

		int gridId = BEGridUtil::getGridIdByPosition(m_sceneGrid, block->getPosition());
		if (!m_sceneGrid->isGridIdInRange(gridId)) continue;

		BEBlock *collidedBlock = (BEBlock *)(m_sceneGrid->getGridData(gridId));
		if (collidedBlock == nullptr) continue;

		if (block->getBoundingBox().isIntersectant(collidedBlock->getBoundingBox()))
		{
			iter->second(block, collidedBlock);
			break;
		}						
	}
}