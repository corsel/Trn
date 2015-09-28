#include "level.h"

//Level class
Level::Level()
{
	background = new Background();
}
void Level::update()
{
	background->update();
	for (int i = 0; i < objectVector.size(); i++)
	{
		objectVector[i]->update();
	} 
}
void Level::pushObject(Object *argObject)
{
	objectVector.push_back(argObject);
}
