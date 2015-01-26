#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <sys/time.h>
#include "slider.h"
#include <string.h>
#include <math.h>

int mousex, mousey;
char buf[256] = {0};
double val = 50.0;
double temp_v = 50.0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	

	//glutWarpPointer(100, 100);
	sprintf(buf, "%7.3f %%", val);

}

void print_bitmap(char *str)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0.4, -0.05);
	int i, l = strlen(str);
	for(i = 0; i < l; i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
}

void display(void)
{
	struct slider_p s = {slider, 0, 0, .3, 0, 0, 10};
	double d = temp_v / 50.0;

	/* Borrar el buffer del lienzo */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Dibujar deslizador */
	s.draw(&s);

	/* Mostrar el valor */
	print_bitmap(buf);

	glEnable(GL_MULTISAMPLE);
	glRectf(-2.5-d, -d, -2.5+d, +d);
	glDisable(GL_MULTISAMPLE);

	/*
	glBegin(GL_LINE_LOOP);
		//glColor3f(.3f, .3f, .3f);
		glVertex2f(.0, .0);
		glVertex2f(.0, .3);
		glVertex2f(2.0, .3);
		glVertex2f(2.0, .0);
		glVertex2f(.0, .0);
	glEnd();
	*/


	glFlush();
	//glutSwapBuffers();
}

void reshape(int w, int h)
{
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
}


void mouse_move(int x, int y)
{
	int dx = x - mousex;
	int dy = y - mousey;

	
	//dx = dx < -100 ? -100 : dx;
	//dx = dx >  100 ?  100 : dx;
	//dy = dy < -100 ? -100 : dy;
	//dy = dy >   99 ?   99 : dy;
	

	//printf("dx = %d, dy = %d\n", dx, dy);
	
	double min = 0.0, max = 100.0;
	double incy = (0+dy) * 10.0 / 400.0;
	double m = incy < 0 ? pow(2, -incy) : 1/pow(2, incy);
	//printf("m = %g\n", m);
	double c = dx / 100.0;
	double v = val + 50 * (c * m);

	v = v > max ? max : v;
	v = v < min ? min : v;

	temp_v = v;

	//printf("MOUSE MOVE: %4d, %4d\n", dx, dy);
	//printf("V = %f\n", v);
	
	sprintf(buf, "%7.3f %%", v);
	display();

	//mousex = x;
	//mousey = y;
		
	//if((x != 250) || (y != 250)) glutWarpPointer(250, 250);

	//mouse(0,0,x,y);
}

void mouse(int button, int state, int mx, int my)
{
	//printf("MOUSE: %d, %d, %4d, %4d\n", button, state, mx, my);

	if(button == 0)
	{
		if(state == 0) /* Enter */
		{
			mousex = mx;
			mousey = my;
		}
		else if(state == 1) /* Release */
		{
			val = temp_v;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 500);
	glutCreateWindow("Deslizador.");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMotionFunc(mouse_move);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}
