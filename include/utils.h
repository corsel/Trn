#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct Vec2
{
	float x;
	float y;
	
	Vec2(float argX = 0.0f, float argY = 0.0f);
	Vec2 operator+(Vec2 argOther);
	void operator+=(Vec2 argOther);
	Vec2 operator-(Vec2 argOther);
	Vec2 operator*(float argMultiplier);
	Vec2 operator/(float argDivisor);
};

struct ColorRGBA
{
	float red;
	float green;
	float blue;
	float alpha;
	
	ColorRGBA(float argRed = 0.0f, float argGreen = 0.0f, float argBlue = 0.0f, float argAlpha = 1.0f);
	ColorRGBA operator+(ColorRGBA argOther);
	void operator+=(ColorRGBA argOther);
	ColorRGBA operator-(ColorRGBA argOther);
	ColorRGBA operator*(float argMultiplier);
	ColorRGBA operator/(float argDivisor);
};

#endif //UTILS_H_INCLUDED

