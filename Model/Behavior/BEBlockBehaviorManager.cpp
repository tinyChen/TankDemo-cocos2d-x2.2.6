#include "BEBlockBehaviorManager.h"
#include "BEBlockBehavior.h"
#include <algorithm>

void BEBlockBehaviorManager::update(float dt)
{
	m_list.visitData([=](void *data)
	{
		BEBlockBehavior *b = (BEBlockBehavior *)data;
		b->updateBehavior(dt);
	});
}

void BEBlockBehaviorManager::addBehavior(BEBlockBehavior *behavior, BEBlock *target)
{
	behavior->setBlock(target);
	m_list.addData(behavior);	
}

void BEBlockBehaviorManager::removeBehavior(BEBlock *block)
{
	const std::vector<void *> &datas = m_list.removeData([=](void *data)->bool
	{
		BEBlockBehavior *b = (BEBlockBehavior *)data;
		return (b->getBlock() == block);
	});
	
	for (size_t i = 0; i < datas.size(); ++i)
	{
		BEBlockBehavior *b = (BEBlockBehavior *)datas[i];
		delete b;
	}
}

