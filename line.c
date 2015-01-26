#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <sys/time.h>
#include "slider.h"

#define MIN_TIME	200000.0

GLfloat ctrlpoints[4][3] = {
	{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, 
	{2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};


double usec()
{
	struct timeval t;
	if (gettimeofday(&t, 0) < 0 ) return -1.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	
	/*
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	*/

	glEnable(GL_MULTISAMPLE);

	glutWarpPointer(100, 100);

}

void display(void)
{
	printf("Display at %f us.\n", usec());
	fflush(stdout);
	double u;
	u = usec();
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 300; i++) 
		glEvalCoord1f((GLfloat) i/300.0);
	glEnd();
	/* The following code displays the control points as dots. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++) 
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	struct slider_p s = {slider, 1., 1., .2};
	s.draw(&s);

	glFlush();
	//glutSwapBuffers();
	printf("Took %f us.\n", usec()-u);
	fflush(stdout);
}

void reshape(int w, int h)
{
	printf("Reshape at %f us.\n", usec());
	fflush(stdout);
	double u;
	u = usec();
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
				5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
				5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	printf("Took %f us.\n", usec()-u);
	fflush(stdout);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_MULTISAMPLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Líneas con antialiasing.");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
