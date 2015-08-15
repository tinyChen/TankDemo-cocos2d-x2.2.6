#include "BEBlockBehavior.h"
#include "BETankPathFinder.h"
#include "BEBlockMover.h"

BEBlockBehavior::BEBlockBehavior(BEMapSceneGrid *sceneGrid)
	: m_block(nullptr)
	, m_mapSceneGrid(sceneGrid)
	, m_interval(0.5f)
{
}	

BEBlockBehavior::~BEBlockBehavior()
{
}
