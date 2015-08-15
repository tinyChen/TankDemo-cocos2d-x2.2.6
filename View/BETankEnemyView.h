#ifndef INCLUDED_BE_TANK_ENEMY_VIEW_H_
#define INCLUDED_BE_TANK_ENEMY_VIEW_H_

#include "BEBlockView.h"
#include "BEITankView.h"

class BETankEnemyView : public BEBlockView, public BEITankView
{
public:
	static BETankEnemyView *create(BEBlock *block);

private:
	BETankEnemyView(BEBlock *block);
	~BETankEnemyView();

	bool init();
	void onTankTowardChanged(int toward);
	void onTankPositionChanged(const GeoPoint &pos);

private:
	cocos2d::CCNode *m_towardNode;
	cocos2d::CCLabelTTF  *m_gridIdNode;

};

#endif