#ifndef SLIDER_H
#define SLIDER_H

struct slider_p
{
	void (* draw)(struct slider_p *);
	GLdouble x, y;
	GLdouble s;
	GLdouble v;
	GLdouble min, max;
};

void slider(struct slider_p *s);

#endif
