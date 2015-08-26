#include "animation.h"

//AnimationServer class
AnimationServer *AnimationServer::instance = NULL;
AnimationServer::AnimationServer() 
{
	
}
AnimationServer *AnimationServer::getInstance()
{
	if (instance == NULL)
	{
		instance = new AnimationServer();
	}
	return instance;
}

//Animation class
template <typename T>
Animation<T>::Animation(T *argRef, T argStart, T argEnd, float argLifeTime)
: ref(argRef), startVal(argStart), endVal(argEnd), lifeTime(argLifeTime), isAlive(true) {}
template <typename T>
bool Animation<T>::getIsAlive() {return isAlive;}

//Lerp class
Vec2Lerp::Vec2Lerp(Vec2 *argRef, Vec2 argStart, Vec2 argEnd, float argLifeTime) : Animation<Vec2>(argRef, argStart, argEnd, argLifeTime) {}
void Vec2Lerp::step(float argStepSize) //virtual implementation
{
	static int iteration = 0; //debug
	currentTime += argStepSize;
	if (currentTime >= lifeTime)
	{
		*ref = endVal;
		std::cout << "animation is finished.\n";
		isAlive = false;
		return;
	}
		*ref = startVal + (endVal - startVal) * (currentTime / lifeTime);
		std::cout << "iteration: " << iteration++ << "\tcurrentTime: " << currentTime << "\tvalue: <" << ref->x << ", " << ref->y << ">\n";
}
