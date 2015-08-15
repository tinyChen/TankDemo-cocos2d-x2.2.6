#ifndef INCLUDED_GE_SIZE
#define INCLUDED_GE_SIZE


class GeoSize
{
public:
	GeoSize(float width, float height) : m_width(width), m_height(height) {}
	GeoSize() : m_width(0.0f), m_height(0.0f) {}
	GeoSize(const GeoSize &pt)
	{
		m_width = pt.m_width;
		m_height = pt.m_height;
	}
	GeoSize &operator = (const GeoSize &pt)
	{
		m_width = pt.m_width;
		m_height = pt.m_height;
		return *this;
	}
	~GeoSize() {}

	//MANIPULATORS
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }

	//ACCESSORS
	float width() const { return m_width; }
	float height() const { return m_height; }

private:
	float m_width;
	float m_height;
};

#endif