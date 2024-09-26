#include "vec.h"


void CVec2f::normalize()
{
	float c = sqrtf(x * x + y * y);
	x /= c;
	y /= c;
}

float CVec2f::length()
{
	float c = x * x + y * y;
	return sqrtf(c);
}

float CVec2f::dist(const CVec2f& right)
{
	return std::powf(x - right.x, 2.0) + std::powf(y - right.y, 2.0);
}

// 重载运算符 + - * /
CVec2f CVec2f::operator + (const CVec2f& right) const
{
	return CVec2f(x + right.x, y + right.y);
}

CVec2f CVec2f::operator - (const CVec2f& right) const
{
	return CVec2f(x - right.x, y - right.y);
}

CVec2f CVec2f::operator * (const float value) const
{
	return CVec2f(x * value, y * value);
}

CVec2f CVec2f::operator / (const float value) const
{
	return CVec2f(x / value, y / value);
}

// 重载运算符 += -= *= /=
void CVec2f::operator += (const CVec2f& right)
{
	x += right.x;
	x += right.x;
}

void CVec2f::operator -= (const CVec2f& right)
{
	x -= right.x;
	x -= right.x;
}

void CVec2f::operator *= (const float value)
{
	x *= value;
	x *= value;
}

void CVec2f::operator /= (const float value)
{
	x /= value;
	x /= value;
}

// 重载运算符 == !=
bool CVec2f::operator == (const CVec2f& right) const
{
	bool flag_x = false, flag_y = false;
	if (abs(x - right.x) < 1e-9)
		flag_x = true;
	if (abs(y - right.y) < 1e-9)
		flag_y = true;
	if (flag_x && flag_y)
		return true;
	else
		return false;
}

bool CVec2f::operator != (const CVec2f& right) const
{
	bool flag_x = false, flag_y = false;
	if (abs(x - right.x) > 1e-9)
		flag_x = true;
	if (abs(y - right.y) > 1e-9)
		flag_y = true;
	if (flag_x || flag_y)
		return true;
	else
		return false;
}