#include "BEMapSceneView.h"
#include "BEMapScene.h"
#include "BEBlockView.h"
#include "GeoPoint.h"
#include "BEBlock.h"
#include "BEBlockUtil.h"

BEMapSceneView::BEMapSceneView(BEMapScene *scene)
	: m_mapScene(scene)
{
	m_mapScene->addView(this);
}

BEMapSceneView::~BEMapSceneView()
{
	m_mapScene->removeView(this);
}

bool BEMapSceneView::init()
{	
	return true;
}

void BEMapSceneView::onBlockAdded(BEBlock *block, int blockType)
{
	const GeoPoint &position = block->getPosition();
	BEBlockView *view = BEBlockUtil::createBlockView(blockType, block);
	view->setAnchorPoint(ccp(0.5f, 0.5f));
	view->setPosition(ccp(position.x(), position.y()));
	addChild(view, 1);
	
	m_blockViews.push_back(view);
}

void BEMapSceneView::onBlockRemoved(BEBlock *block)
{
	for (size_t i = 0; i < m_blockViews.size(); ++i)
	{
		if (m_blockViews[i]->getBlock() == block)
		{
			m_blockViews[i]->removeFromParent();
			m_blockViews[i] = m_blockViews.back();
			m_blockViews.resize(m_blockViews.size() - 1);
			break;
		}
	}
}

BEMapSceneView *BEMapSceneView::create(BEMapScene *scene)
{
	BEMapSceneView *view = new BEMapSceneView(scene);
	view->autorelease();
	view->init();
	return view;
}