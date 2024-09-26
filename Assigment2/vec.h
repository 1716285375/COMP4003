#pragma once
#include <cmath>
class CVec2f
{
public:
	CVec2f() {}
	CVec2f(float x_in, float y_in) : x(x_in), y(y_in) {}
	~CVec2f() {}

public:
	void normalize();
	float length();
	float dist(const CVec2f& right);

public:
	CVec2f operator + (const CVec2f& right) const;
	CVec2f operator - (const CVec2f& right) const;
	CVec2f operator * (const float value) const;
	CVec2f operator / (const float value) const;

	bool operator == (const CVec2f& right) const;
	bool operator != (const CVec2f& right) const;

	void operator += (const CVec2f& right);
	void operator -= (const CVec2f& right);
	void operator *= (const float value);
	void operator /= (const float value);

public:
	float x = .0f;
	float y = .0f;
};

