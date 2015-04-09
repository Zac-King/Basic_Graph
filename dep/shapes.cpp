#include "shapes.h"
#include <iostream>
#include <cassert>
#include "crenderutils.h"
#define NOMINMAX
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

void debug(char *a, bool todo = true)
{
	std::cerr << (todo ? "TODO: " : "WARNING: ") << a << std::endl;
	assert(!todo);
}

const circle operator*(const mat4 &m, const circle &s)
{
	return{ mulaff(m, s.position), length(mul(m, vec2(s.radius, 0))) };
}

const line   operator*(const mat4 &m, const line &s)
{
	return {mulaff(m, s.position), mulaff(m, s.end) };
}
const point  operator*(const mat4 &m, const point &s)
{
	return {m * s.position };
}
const aabb operator*(const mat4 &m, const aabb &s)
{
	return { mulaff(m, s.position), mul(m, s.dimension) };
}


const collision circle_circle(const circle &a, const circle &b)
{
	collision r;
	vec2 diff = a.position - b.position;

	r.normal = normal(diff);
	r.contact = (a.position + b.position) / 2;
	r.depth = a.radius + b.radius - length(diff);
	r.result = r.depth > 0;

	return r;
}

// TODO:
const collision circle_line(const circle &a, const line &b)
{
	collision r;
	debug("circle line");
	return r;
}

const collision circle_aabb(const circle &a, const aabb &b)
{
	collision r;
	debug("circle aabb");
	return r;
}

const collision line_line(const line &a, const line &b)
{
	collision r;
	debug("line line");
	return r;
}

const collision line_aabb(const line &a, const aabb &b)
{
	collision r;
	debug("line aabb");
	return r;
}

const collision aabb_aabb(const aabb &a, const aabb &b)
{
	collision r;
	debug("AABB AABB : only result, no normal data", false);

	r.result = 
	!(a.max().x < a.min().x ||
	b.max().x < a.min().x ||
	a.max().y < a.min().y ||
	b.max().y < a.min().y);

	return r;
}




const collision circle_point(const circle &a, const point &b) { return circle_circle(a, b); }
const collision line_point(const line &a, const point &b)	  { return circle_line(b, a); }
const collision point_point(const point &a, const point &b)	  { return circle_circle(a,b); }
const collision point_aabb(const point &a, const aabb &b)	  { return circle_aabb(a, b); }



void draw_line(const mat4 &m, const line &a, const vec4 &color)
{
	glLoadIdentity();
	glLoadMatrixf(m.m);
	glColor4fv(color.v);
	glBegin(GL_LINES);
		glVertex2fv(a.position.v);
		glVertex2fv(a.end.v);
	glEnd();
}

void draw_circle(const mat4 &m, const circle &a, const vec4 &color)
{
	const float step = PI / 12;
	
	glLoadIdentity();
	glLoadMatrixf(m.m);
	glColor4fv(color.v);
	glBegin(GL_LINE_LOOP);
	
	for (float i = 0; i <= 2 * PI; i += step)
		glVertex2fv((a.position + vec2(cos(i), sin(i))*a.radius).v);
	glEnd();
}
void draw_point(const mat4 &m, const point &a, const vec4 &color)
{
	draw_circle(m, circle(a.position, 1), color);
	draw_circle(m,circle(a.position, a.drawsize), color);
}
void draw_aabb(const mat4 &m, const aabb &a, const vec4 &color)
{
	for (int i = 0; i < 4; ++i)
		draw_line(m, a.edge(i), color);
}