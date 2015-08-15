#ifndef INCLUDED_GEO_RECT
#define INCLUDED_GEO_RECT

#include <assert.h>
#include "GeoPoint.h"
#include <math.h>

class GeoRect
{
public:
	GeoRect(const GeoPoint &leftTop, const GeoPoint &rightBottom) : m_leftTop(leftTop), m_rightBottom(rightBottom) {}
	GeoRect() {}
	GeoRect(const GeoRect &rect)
	{
		m_leftTop = rect.m_leftTop;
		m_rightBottom = rect.m_rightBottom;
	}
	GeoRect &operator = (const GeoRect &rect)
	{
		m_leftTop = rect.m_leftTop;
		m_rightBottom = rect.m_rightBottom;
		return *this;
	}
	~GeoRect() {}

	//MANIPULATORS
	void setLeftTop(const GeoPoint &leftTop) { m_leftTop = leftTop; }
	void setRightBottom(const GeoPoint &rightBottom) { m_rightBottom = rightBottom; }

	//ACCESSORS
	const GeoPoint &getLeftTop() const { return m_leftTop; }
	const GeoPoint &getRightBottom() const { return m_rightBottom; }
	bool isIntersectant(const GeoRect &rect) const;
	bool isPointInRect(const GeoPoint &pt) const;

private:
	GeoPoint m_leftTop;
	GeoPoint m_rightBottom;
};

inline bool GeoRect::isIntersectant(const GeoRect &rect) const
{
	float x1 = m_leftTop.x();
	float x2 = m_rightBottom.x();
	float y1 = m_leftTop.y();
	float y2 = m_rightBottom.y();
	float rx1 = rect.getLeftTop().x();
	float rx2 = rect.getRightBottom().x();
	float ry1 = rect.getLeftTop().y();
	float ry2 = rect.getRightBottom().y();
	if(fabs(x1 + x2 - rx1 - rx2) < (x2 - x1 + rx2 - rx1))
		if(fabs(-y1 - y2 + ry1 + ry2) < (-y2 + y1 - ry2 + ry1))
			return true;
	return false;
}

inline bool GeoRect::isPointInRect(const GeoPoint &pt) const
{
	return pt.x() >= m_leftTop.x() && pt.x() <= m_rightBottom.x()
		&& pt.y() <= m_leftTop.y() && pt.y() >= m_rightBottom.y();
}


#endif