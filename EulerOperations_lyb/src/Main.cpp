#include <iostream>
#include"EulerOperations.h"
#include"Sweeping.h"
#include"Brep.h"
#include"displayEntity.h"


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("3D_CAD_Modeling");
	initRendering();
	Brep::generateBrepOfSolid();
	glutDisplayFunc(render);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(handleMousePress);
	glutMotionFunc(handleMouseActiveMotion);
	glutMainLoop();
	return 0;
}




