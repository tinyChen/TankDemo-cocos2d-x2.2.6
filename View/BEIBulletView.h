#ifndef INCLUDED_BE_I_BULLET_VIEW_H_
#define INCLUDED_BE_I_BULLET_VIEW_H_

class GeoPoint;

class BEIBulletView
{
public:
	virtual ~BEIBulletView();
	virtual void onBulletPositionChanged(const GeoPoint &position, int toward) {}
};

#endif