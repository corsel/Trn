#include "glut-functions.h"

Level *activeLevel = NULL;

void TrnGlutFunctions::init(int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(TrnGlutFunctions::screenWidth, TrnGlutFunctions::screenHeight);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("test window");
	
	if (TrnGlutFunctions::fullscreen) glutFullScreen();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0f, 10.0f, 10.0f, 10.0f, 0.5f, 10.0f);
	
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	
	glutIdleFunc(TrnGlutFunctions::display);	
	glutDisplayFunc(TrnGlutFunctions::display);
	
	glMatrixMode(GL_MODELVIEW);
}
void TrnGlutFunctions::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (activeLevel != NULL) activeLevel->update();
	
	glutSwapBuffers();
}
void TrnGlutFunctions::keyboard(unsigned char argKey, int argX, int argY)
{
}
void TrnGlutFunctions::mouse(int argButton, int argState, int argX, int argY)
{
}
