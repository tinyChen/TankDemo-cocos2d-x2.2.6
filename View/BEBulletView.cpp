#include "BEBulletView.h"
#include "BETankStraightBullet.h"

USING_NS_CC;

BEBulletView::BEBulletView(BEBlock *bullet) : BEBlockView(bullet), m_bulletNode(nullptr)
{
	BETankStraightBullet *straightBullet = dynamic_cast<BETankStraightBullet *>(getBlock());
	straightBullet->addView(this);
}

BEBulletView::~BEBulletView()
{

}

void BEBulletView::onBulletPositionChanged(const GeoPoint &position, int toward)
{
	setPosition(ccp(position.x(), position.y()));
}

bool BEBulletView::init()
{
	const CCSize &size = getContentSize();
	m_bulletNode = CCLayerColor::create(ccc4(0, 0, 0, 150));
	m_bulletNode->setContentSize(size);
	m_bulletNode->ignoreAnchorPointForPosition(false);
	m_bulletNode->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(m_bulletNode);

	return true;
}

BEBulletView *BEBulletView::create(BEBlock *bullet)
{
	BEBulletView *view = new BEBulletView(bullet);
	view->autorelease();
	view->init();
	return view;
}