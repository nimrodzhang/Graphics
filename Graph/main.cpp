#include "common.h"
#include "control.h"
#include "display.h"


void main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINX, WINY);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graph");
	gluOrtho2D(0.0, WINX, WINY, 0.0);	
	glClearColor(1.0, 1.0, 1.0, 0.0);		
	glShadeModel(GL_FLAT);			

	createMenu();
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutDisplayFunc(displayFunc);
	
	glutMainLoop();

}