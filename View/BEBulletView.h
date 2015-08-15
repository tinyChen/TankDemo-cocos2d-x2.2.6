#ifndef INCLUDED_BE_BULLET_VIEW_H_
#define INCLUDED_BE_BULLET_VIEW_H_

#include "BEBlockView.h"
#include "BEIBulletView.h"

class BEBlock;

class BEBulletView : public BEBlockView, public BEIBulletView
{
public:
	static BEBulletView *create(BEBlock *bullet);

private:
	BEBulletView(BEBlock *bullet);
	~BEBulletView();

private:
	void onBulletPositionChanged(const GeoPoint &position, int toward);

private:
	bool init();

private:
	cocos2d::CCNode *m_bulletNode;
};

#endif