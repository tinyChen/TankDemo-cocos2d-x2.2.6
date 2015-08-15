#include "BETankEnemyView.h"
#include "BETank.h"
#include "GeoPoint.h"
#include "BEToward.h"

USING_NS_CC;

BETankEnemyView::BETankEnemyView(BEBlock *block) : BEBlockView(block), m_towardNode(nullptr), m_gridIdNode(nullptr)
{
	BETank *tank = dynamic_cast<BETank *>(getBlock());
	tank->addView(this);
}

BETankEnemyView::~BETankEnemyView()
{
	BETank *tank = dynamic_cast<BETank *>(getBlock());
	tank->removeView(this);
}

static void changeToward(CCNode *towardNode, int toward, const CCSize &size)
{
	CCPoint position = towardNode->getPosition();
	const CCSize &nodeSize = towardNode->getContentSize();
	float rotation = 0.0f;
	switch (toward)
	{
	case kBETowardLeft:
		position.setPoint(nodeSize.width * 0.5f, size.height * 0.5f);
		break;
	case kBETowardUp:
		position.setPoint(size.width * 0.5f, size.height - nodeSize.width * 0.5f);
		rotation = 90.0f;
		break;
	case kBETowardRight:
		position.setPoint(size.width - nodeSize.width * 0.5f, size.height * 0.5f);
		break;
	case kBETowardDown:
		position.setPoint(size.width * 0.5f, nodeSize.width * 0.5f);
		rotation = 90.0f;
		break;
	default:
		assert(false && "illegal toward");
	}
	towardNode->setPosition(position);
	towardNode->setRotation(rotation);
}

bool BETankEnemyView::init()
{
	const CCSize &size = getContentSize();
	CCLayerColor *layerColor = CCLayerColor::create(ccc4(89, 172, 255, 255));
	layerColor->setContentSize(size);
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(layerColor);

	m_towardNode = CCLayerColor::create(ccc4(255, 0, 0, 255));
	m_towardNode->setContentSize(CCSize(size.width * 0.4f, size.height * 0.2f));
	m_towardNode->ignoreAnchorPointForPosition(false);
	m_towardNode->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	layerColor->addChild(m_towardNode);

	BETank *tank = dynamic_cast<BETank *>(getBlock());
	changeToward(m_towardNode, tank->getToward(), size);

	static char buf[256];
	snprintf(buf, sizeof(buf), "%d", tank->getGridId());
	m_gridIdNode = CCLabelTTF::create(buf, "", 20);
	m_gridIdNode->setColor(ccc3(0, 0, 255));
	m_gridIdNode->setPosition(CCPoint(size.width * 0.5f, size.height * 0.5f));
	addChild(m_gridIdNode, 1);

	return true;
}

void BETankEnemyView::onTankPositionChanged(const GeoPoint &pos)
{
	setPosition(ccp(pos.x(), pos.y()));

	BETank *tank = dynamic_cast<BETank *>(getBlock());
	static char buf[256];
	snprintf(buf, sizeof(buf), "%d", tank->getGridId());
	dynamic_cast<CCLabelTTF *>(m_gridIdNode)->setString(buf);
}

void BETankEnemyView::onTankTowardChanged(int toward)
{
	const CCSize &size = getContentSize();
	BETank *tank = dynamic_cast<BETank *>(getBlock());
	changeToward(m_towardNode, tank->getToward(), size);
}

BETankEnemyView *BETankEnemyView::create(BEBlock *block)
{
	BETankEnemyView *grassBlock = new BETankEnemyView(block);
	grassBlock->autorelease();
	grassBlock->init();
	return grassBlock;
}