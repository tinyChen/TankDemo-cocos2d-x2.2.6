#include "BEBlockEditorView.h"
#include "BEMapScene.h"
#include "BEMapSceneGrid.h"
#include "GeoSize.h"
#include "GeoPoint.h"
#include "BEGrid.h"
#include "BEBlockType.h"
#include "BEMapSceneView.h"
#include "BEGridUtil.h"
#include "BEToward.h"
#include <math.h>
#include <time.h>
#include "GeoRect.h"

USING_NS_CC;

CCScene* BEBlockEditorView::theScene()
{
    CCScene *scene = CCScene::create();
    
    const CCSize &size = CCDirector::sharedDirector()->getWinSize();
    BEBlockEditorView *layer = BEBlockEditorView::create(new BEMapScene(GeoSize(size.width, size.height), 12, 12));

    scene->addChild(layer);

    return scene;
}

BEBlockEditorView::BEBlockEditorView(BEMapScene *mapScene) : m_mapScene(mapScene)
{

}

BEBlockEditorView::~BEBlockEditorView()
{
	delete m_mapScene;
}

void BEBlockEditorView::onEnter()
{
	CCLayer::onEnter();
	scheduleUpdate();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void BEBlockEditorView::onExit()
{
	CCLayer::onExit();
	unscheduleUpdate();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void BEBlockEditorView::update(float delta)
{
	m_mapScene->updateScene(delta);
}

static void addBlock(BEMapScene *mapScene, const CCPoint &glPos)
{
	int gridId = BEGridUtil::getGridIdByPosition(mapScene->getMapSceneGrid(), GeoPoint(glPos.x, glPos.y));
	if (mapScene->getMapSceneGrid()->isGridIdInRange(gridId) && !mapScene->hasBlock(gridId))
	{
		mapScene->addBlock(gridId, 2);
	}
}

bool BEBlockEditorView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	addBlock(m_mapScene, pTouch->getLocation());
	return true;
}

void BEBlockEditorView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	addBlock(m_mapScene, pTouch->getLocation());
}

void BEBlockEditorView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

BEBlockEditorView *BEBlockEditorView::create(BEMapScene *scene)
{
	BEBlockEditorView *view = new BEBlockEditorView(scene);
	view->autorelease();
	view->init();
	return view;
}

static void initGrids(BEMapScene *mapScene, CCNode *parent)
{
	int row = mapScene->getRow();
	int column = mapScene->getColumn();
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			int gridId = i * row + j;
			const GeoPoint &pos = mapScene->getGrid(gridId)->getPosition();
			const GeoSize &gridSize = mapScene->getGrid(gridId)->getRect();

			CCLayerColor *layerColor = CCLayerColor::create(ccc4(255, 255, 255, 255 - gridId * 2));
			layerColor->ignoreAnchorPointForPosition(false);
			layerColor->setAnchorPoint(ccp(0.5f, 0.5f));
			layerColor->setPosition(ccp(pos.x(), pos.y()));
			layerColor->setContentSize(CCSize(gridSize.width(), gridSize.height()));
			parent->addChild(layerColor);

			static char buf[256];
			snprintf(buf, sizeof(buf), "%d", gridId);
			CCLabelTTF *gridIdLabel = CCLabelTTF::create(buf, "", 20);
			gridIdLabel->setColor(ccc3(255, 0, 0));
			gridIdLabel->setPosition(CCPoint(gridSize.width() * 0.5f, gridSize.height() * 0.5f));
			layerColor->addChild(gridIdLabel, 1);
		}
	}
}

bool BEBlockEditorView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initGrids(m_mapScene, this);

	BEMapSceneView *sceneView = BEMapSceneView::create(m_mapScene);
	sceneView->setPosition(ccp(0, 0));
	addChild(sceneView);

	srand(time(nullptr));
	for (int i = 0; i < 5; )
	{
		int gridId = rand() % 50;
		if (!m_mapScene->hasBlock(gridId))
		{
			m_mapScene->addEnemyTank(gridId);
			++i;
		}		
	}
	m_mapScene->addPlayerTank(99);
	return true;
}