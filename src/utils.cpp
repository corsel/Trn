#include "utils.h"

//Vec2 struct
Vec2::Vec2(float argX /*=0.0f*/, float argY /*=0.0f*/)
: x(argX), y(argY) {}
Vec2 Vec2::operator+(Vec2 argOther)
{
	return Vec2(this->x + argOther.x, this->y + argOther.y);
}
void Vec2::operator+=(Vec2 argOther)
{
	this->x += argOther.x;
	this->y += argOther.y;
}
Vec2 Vec2::operator-(Vec2 argOther)
{
	return Vec2(this->x - argOther.x, this->y - argOther.y);
}
Vec2 Vec2::operator*(float argMultiplier)
{
	return Vec2(argMultiplier * this->x, argMultiplier * this->y);
}
Vec2 Vec2::operator/(float argDivisor)
{
	return Vec2(this->x / argDivisor, this->y / argDivisor);
}

//ColorRGBA struct
ColorRGBA::ColorRGBA(float argRed /*=0.0f*/, float argGreen /*=0.0f*/, float argBlue /*=0.0f*/, float argAlpha /*=1.0f*/)
: red(argRed), green(argGreen), blue(argBlue), alpha(argAlpha) {}

