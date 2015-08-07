#include "level.h"

//Level class
Level::Level()
{
	background = new Background();
}
void Level::update()
{
	background->update();
}
