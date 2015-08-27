#include "animation.h"

//Animation class
template <typename T>
Animation<T>::Animation(T *argRef, T argStart, T argEnd, float argLifeTime)
: ref(argRef), startVal(argStart), endVal(argEnd), lifeTime(argLifeTime), isAlive(true) {}
template <typename T>
bool Animation<T>::getIsAlive() {return isAlive;}

//AnimationServer class
bool AnimationServer::killFlag = true;
std::vector<Animation<Vec2>*> AnimationServer::vec2AnimVector;
std::vector<Animation<float>*> AnimationServer::floatAnimVector;
AnimationServer *AnimationServer::instance = NULL;
AnimationServer::AnimationServer()
{
	std::cout << "in constructor test: " << pthread_create(&handle, NULL, threadLoop, NULL) << std::endl;	
}
AnimationServer::~AnimationServer()
{
	pthread_exit(NULL);
}
void *AnimationServer::threadLoop(void *argArgs) //static
{
	std::cout << "thread created.\n";
	while(killFlag)
	{
		for (int i = 0; i < vec2AnimVector.size(); i++)
		{
			vec2AnimVector[i]->step(0.1f);
		}
		/*
		for (int i = 0; i < floatAnimVector.size(); i++)
		{
			floatAnimVector[i]->step(0.1f);
		}
		*/
	}
}

AnimationServer *AnimationServer::getInstance() //static
{
	if (instance == NULL)
	{
		instance = new AnimationServer();
	}
	std::cout << "getInstance exit.\n";
	return instance;
}
void AnimationServer::registerAnimation(Animation<Vec2> *argAnimation) 
{
	vec2AnimVector.push_back(argAnimation);
}
void AnimationServer::registerAnimation(Animation<float> *argAnimation) 
{
	floatAnimVector.push_back(argAnimation);
}

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
