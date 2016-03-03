#include "object.h"

//Object class
Object::Object() {}
Object::~Object() {}

//Box class
Box::Box()
: Object() {}
Box::Box(Vec2 argPosn, Vec2 argSize, ColorRGBA argColor)
: Object(), posn(argPosn), size(argSize), color(argColor) {}
Box::~Box() {}
void Box::update() 
{
	//Texture added for test purposes.
	glPushMatrix();
	glTranslatef(posn.x, posn.y, 0.0f);
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-size.x / 2.0f, -size.y / 2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(size.x / 2.0f, -size.y / 2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(size.x / 2.0f, size.y / 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-size.x / 2.0f, size.y / 2.0f);
	glEnd();
	glPopMatrix();
}
