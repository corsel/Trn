#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct Vec2
{
	float x;
	float y;
	
	Vec2(float argX = 0.0f, float argY = 0.0f);
};

struct ColorRGBA
{
	float red;
	float green;
	float blue;
	float alpha;
	
	ColorRGBA(float argRed = 0.0f, float argGreen = 0.0f, float argBlue = 0.0f, float argAlpha = 1.0f);
};

#endif //UTILS_H_INCLUDED

