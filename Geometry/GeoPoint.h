#ifndef INCLUDED_GEO_POINT_H_
#define INCLUDED_GEO_POINT_H_

class GeoPoint
{
public:
	GeoPoint(float x, float y) : m_x(x), m_y(y) {}
	GeoPoint() : m_x(0.0f), m_y(0.0f) {}
	GeoPoint(const GeoPoint &pt)
	{ 
		m_x = pt.m_x;
		m_y = pt.m_y;
	}
	GeoPoint &operator = (const GeoPoint &pt)
	{
		m_x = pt.m_x;
		m_y = pt.m_y;
		return *this;
	}
	GeoPoint &operator -=(const GeoPoint &pt)
	{
		m_x -= pt.m_x;
		m_y -= pt.m_y;
		return *this;
	}
	bool operator == (const GeoPoint &pt)
	{
		return m_x == pt.m_x && m_y == pt.m_y;
	}
	bool operator != (const GeoPoint &pt)
	{
		return !(*this == pt);
	}
	bool operator > (const GeoPoint &pt)
	{
		return m_x > pt.x() && m_y > pt.y();
	}
	bool operator < (const GeoPoint &pt)
	{
		return m_x < pt.x() && m_y < pt.y();
	}
	~GeoPoint() {}

	//MANIPULATORS
	void setPoint(float x, float y) { m_x = x; m_y = y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	//ACCESSORS
	float x() const { return m_x; }
	float y() const { return m_y; } 

private: 
	float m_x;
	float m_y;
};

inline GeoPoint operator - (const GeoPoint &lPt, const GeoPoint &rPt)
{
	return GeoPoint(lPt.x() - rPt.x(), lPt.y() - rPt.y());
} 

inline GeoPoint operator + (const GeoPoint &lPt, const GeoPoint &rPt)
{
	return GeoPoint(lPt.x() + rPt.x(), lPt.y() + rPt.y());
} 
#endif