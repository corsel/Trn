#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "background.h"
#include "object.h"

class Level
{
private:
	Background *background;
	std::vector<Object*> objectVector;
	
public:
	Level();
	~Level();
	void pushObject(Object *argObject);
	void update(void);
};

#endif //LEVEL_H_INCLUDED

