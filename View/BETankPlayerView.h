#ifndef INCLUDED_BE_TANK_PLAYER_VIEW_H_
#define INCLUDED_BE_TANK_PLAYER_VIEW_H_

#include "BEBlockView.h"
#include "BEITankView.h"

class BETankPlayerView : public BEBlockView, public BEITankView
{
public:
	static BETankPlayerView *create(BEBlock *block);

private:
	BETankPlayerView(BEBlock *block);
	~BETankPlayerView();

	bool init();
	void onTankTowardChanged(int toward);
	void onTankPositionChanged(const GeoPoint &pos);

private:
	cocos2d::CCNode *m_towardNode;
	cocos2d::CCLabelTTF  *m_gridIdNode;

};

#endif