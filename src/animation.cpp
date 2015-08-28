#include "animation.h"

//Animation class
template <typename T>
Animation<T>::Animation(T *argRef, T argStart, T argEnd, float argLifeTime)
: ref(argRef), startVal(argStart), endVal(argEnd), lifeTime(argLifeTime), isDead(false) {}
template <typename T>
Animation<T>::~Animation()
{
	std::cout << "Debug - Animation: Destructor called.\n";
}
template <typename T>
bool Animation<T>::getIsDead() {return isDead;}

//AnimationServer class
std::vector<Animation<Vec2>*> AnimationServer::vec2AnimVector;
std::vector<Animation<float>*> AnimationServer::floatAnimVector;
AnimationServer *AnimationServer::instance = NULL;
AnimationServer::AnimationServer()
: killFlag(true)
{
	pthread_create(&handle, NULL, threadLoop, NULL);
}
AnimationServer::~AnimationServer()
{
	pthread_exit(NULL);
}
void *AnimationServer::threadLoop(void *argArgs) //static
{
	while(AnimationServer::getInstance()->killFlag)
	{
		for (int i = 0; i < vec2AnimVector.size(); i++)
		{
			if (vec2AnimVector[i]->getIsDead())
			{
				std::cout << "Debug - AnimationServer: Animation killed.\n";
				delete vec2AnimVector[i];
				vec2AnimVector.erase(vec2AnimVector.begin() + i);
				break;
			}
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
Vec2Lerp::~Vec2Lerp()
{
	std::cout << "Debug - Vec2Lerp: Destructor called.\n";
}
void Vec2Lerp::step(float argStepSize) //virtual implementation
{
	static int iteration = 0; //debug
	currentTime += argStepSize;
	if (currentTime >= lifeTime)
	{
		*ref = endVal;
		std::cout << "Debug - Vec2Lerp: Animation is finished.\n";
		isDead = true;
		return;
	}
		*ref = startVal + (endVal - startVal) * (currentTime / lifeTime);
		std::cout << "Debug - Vec2Lerp: New step values are;\n\titeration: " << iteration++ << "\tcurrentTime: " << currentTime << "\tvalue: <" << ref->x << ", " << ref->y << ">\n";
}
