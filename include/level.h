#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "background.h"

class Level
{
private:
	Background *background;
	
public:
	Level();
	~Level();
	void update(void);
};

#endif //LEVEL_H_INCLUDED

