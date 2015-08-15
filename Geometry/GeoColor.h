#ifndef INCLUDED_GE_COLOR
#define INCLUDED_GE_COLOR

#include <wtypes.h>

class GeoColor
{
	typedef unsigned char ge_byte;

public:
	GeoColor(ge_byte r, ge_byte g, ge_byte b, ge_byte a = 0xff)
		: m_r(r), m_g(g), m_b(b), m_alpha(a)
	{
	}
	GeoColor() : m_r(0), m_g(0), m_b(0), m_alpha(0xff) {}
	GeoColor(const GeoColor &color) 
		: m_r(color.m_r), m_g(color.m_g), m_b(color.m_b), m_alpha(color.m_alpha) 
	{}
	GeoColor &operator = (const GeoColor &color)
	{
		m_r = color.m_r;
		m_g = color.m_g;
		m_b = color.m_b;
		m_alpha = color.m_alpha;
		return *this;
	}
	operator DWORD () const
	{
		return m_alpha << 24 | m_r << 16 | m_g << 8 | m_b;
	}
	~GeoColor() {}

	//MANIPULATORS
	void setAlpha(ge_byte a) { m_alpha = a; }
	void setR(ge_byte r) { m_r = r; }
	void setG(ge_byte g) { m_g = g; }
	void setB(ge_byte b) { m_b = b; }	

	//ACCESSORS
	ge_byte r() const { return m_r; }
	ge_byte g() const { return m_g; }
	ge_byte b() const { return m_b; }
	ge_byte a() const { return m_alpha; }

private:
	ge_byte m_r;
	ge_byte m_g;
	ge_byte m_b;
	ge_byte m_alpha;
};

#endif