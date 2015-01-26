#include <GL/gl.h>
#include <stdio.h>
#include "slider.h"

/*
void slider_init(struct slider_p *s, GLdouble x, GLdouble y, GLdouble s)
{
	s->draw = slider;
	s->x = x;
	s->y = y;
	s->s = s;
}
*/

void slider(struct slider_p *s)
{
	//printf("Slider [%p] value %f\n", s, s->v);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(s->x - s->s/2.0,
		s->y - s->s/2.0,
		s->x + s->s/2.0,
		s->y + s->s/2.0);
}
