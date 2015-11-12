#/**********
 * draw.c - various common drawing functions
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#ifdef WIN32
#include <windows.h>
#define GL_BGR GL_BGR_EXT
#define GL_BGRA GL_BGRA_EXT
#endif

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#include "misc.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define CROSS_SIZE  1.0

void draw_cross(double x, double y)
{

  //  printf("draw_cross: %f, %f\n", x, y);
    glColor3d(1.0, 1.0, 1.0);
    glLineWidth(2.0);

    glBegin(GL_LINES);
    glVertex2d(x-CROSS_SIZE, y);
    glVertex2d(x+CROSS_SIZE, y);
    glVertex2d(x, y-CROSS_SIZE);
    glVertex2d(x, y+CROSS_SIZE);
    glEnd();

    glLineWidth(1.0);
}

#define MARK_SIZE 1.5

void draw_mark(double mx, double my, double r, double g, double b)
{
  double x, y;
  double a;
  static double as = 0.0;

  glColor3d(0.0, 0.0, 0.0);
  glLineWidth(5.0);

  glBegin(GL_LINES);
  glVertex2d(mx-MARK_SIZE, my);
  glVertex2d(mx+MARK_SIZE, my);
  glVertex2d(mx, my-MARK_SIZE);
  glVertex2d(mx, my+MARK_SIZE);
  glEnd();

  glBegin(GL_LINE_LOOP);
  for (a = 0.0; a < 2.0*M_PI; a += 0.3) {
	 x = MARK_SIZE*cos(a+as) + mx;
	 y = MARK_SIZE*sin(a+as) + my;
	 glVertex2d(x, y);
  }
  glEnd();

  glLineWidth(1.0);
  //  glColor3d(1.0, 0.0, 0.0);
  glColor3d(r, g, b);
  glBegin(GL_LINES);
  glVertex2d(mx-MARK_SIZE, my);
  glVertex2d(mx+MARK_SIZE, my);
  glVertex2d(mx, my-MARK_SIZE);
  glVertex2d(mx, my+MARK_SIZE);
  glEnd();

  glBegin(GL_LINE_LOOP);
  for (a = 0.0; a < 2.0*M_PI; a += 0.3) {
	 x = MARK_SIZE*cos(a+as) + mx;
	 y = MARK_SIZE*sin(a+as) + my;
	 glVertex2d(x, y);
  }
  glEnd();

  //  as += 0.1;

  glLineWidth(1.0);
}

void draw_mark_rot(double mx, double my, double r, double g, double b, double t)
{
  double x, y;
  double a;
  static double as = 0.0;

  glColor3d(0.0, 0.0, 0.0);
  glLineWidth(5.0);

  glPushMatrix();
  glTranslated(mx, my, 0.0);
  glRotated(t, 0.0, 0.0, 1.0);

  glBegin(GL_LINES);
  glVertex2d(-MARK_SIZE, 0.0);
  glVertex2d(MARK_SIZE, 0.0);
  glVertex2d(0.0, -MARK_SIZE);
  glVertex2d(0.0, MARK_SIZE);
  glEnd();

  glBegin(GL_LINE_LOOP);
  for (a = 0.0; a < 2.0*M_PI; a += 0.3) {
	 x = MARK_SIZE*cos(a+as);
	 y = MARK_SIZE*sin(a+as);
	 glVertex2d(x, y);
  }
  glEnd();

  glLineWidth(1.0);
  //  glColor3d(1.0, 0.0, 0.0);
  glColor3d(r, g, b);
  glBegin(GL_LINES);
  glVertex2d(-MARK_SIZE, 0.0);
  glVertex2d(MARK_SIZE, 0.0);
  glVertex2d(0.0, -MARK_SIZE);
  glVertex2d(0.0, MARK_SIZE);
  glEnd();

  glBegin(GL_LINE_LOOP);
  for (a = 0.0; a < 2.0*M_PI; a += 0.3) {
	 x = MARK_SIZE*cos(a+as);
	 y = MARK_SIZE*sin(a+as);
	 glVertex2d(x, y);
  }
  glEnd();

  //  as += 0.1;

  glLineWidth(1.0);
  glPopMatrix();

}

static void draw_grid_low(double xstart, double ystart, double xend,
                          double yend, double xoffset, double yoffset,
                          double cx, double cy, double dx, double dy)
{
  double x, y;

  glBegin(GL_LINES);
  for (x = cx; x < xend; x += dx) {
    glVertex2d(x-xoffset, ystart-yoffset);
    glVertex2d(x-xoffset, yend-yoffset);
  }
  for (x = cx; x > xstart; x -= dx) {
    glVertex2d(x-xoffset, ystart-yoffset);
    glVertex2d(x-xoffset, yend-yoffset);
  }
  for (y = cy; y < yend; y += dy) {
    glVertex2d(xstart-xoffset, y-yoffset);
    glVertex2d(xend-xoffset, y-yoffset);
  }
  for (y = cy; y > ystart; y -= dy) {
    glVertex2d(xstart-xoffset, y-yoffset);
    glVertex2d(xend-xoffset, y-yoffset);
  }
  glEnd();

}

void draw_grid(double xstart, double ystart, double xend, double yend,
               double xoffset, double yoffset)
{
  double cx, cy, x, y;
  double dx = 1.0, dy = 1.0;

  if (yend - ystart <= 50.0) {
    dx = 1.0;
    dy = 1.0;
    cx = (xstart + xend)/2.0;
    cy = (ystart + yend)/2.0;
  
    cx -= fmod(cx, dx);
    cy -= fmod(cy, dy);

    glColor3d(0.2, 0.2, 0.3);
    glLineWidth(1.0);
    draw_grid_low(xstart, ystart, xend, yend, xoffset, yoffset, cx, cy, dx, dy);
  }

  dx = 10.0;
  dy = 10.0;
  cx = (xstart + xend)/2.0;
  cy = (ystart + yend)/2.0;
  
  cx -= fmod(cx, dx);
  cy -= fmod(cy, dy);

  glColor3d(0.3, 0.3, 0.4);
  glLineWidth(2.0);
  draw_grid_low(xstart, ystart, xend, yend, xoffset, yoffset, cx, cy, dx, dy);
  glLineWidth(1.0);

}

void draw_start(double x, double y)
{
  double dx = MARK_SIZE, dy = MARK_SIZE;

  glBegin(GL_LINES);
  glVertex2d(x, y-dy);
  glVertex2d(x, y+dy);

  glVertex2d(x-dx, y);
  glVertex2d(x+dx, y);

  glVertex2d(x-dx*0.7, y-dy*0.7);
  glVertex2d(x+dx*0.7, y+dy*0.7);

  glVertex2d(x-dx*0.7, y+dy*0.7);
  glVertex2d(x+dx*0.7, y-dy*0.7);

  glEnd();
}

void comphot(double v, double *r, double *g, double *b)
{

	if (v > 1.0) v = 1.0;
	if (v < 0.0) v = 0.0;
	*r = *g = *b = 0.0;
	if (v <= 1.0/3.0) *r = v * 3.0;
	else if (v <= 2.0/3.0) {
		*r = 1.0;
		*g = (v - 1.0/3.0) * 3.0;
	}
	else {
		*r = *g = 1.0;
		*b = (v - 2.0/3.0) * 3.0;
	}
}

void compihot(double v, int *r, int *g, int *b)
{
  int iv;

  iv = v * 766;
  if (iv > 766) iv = 766;
  if (iv < 0) iv = 0;
  *r = *g = *b = 0;
  if (iv <= 255) *r = iv;
  else if (iv <= 510) {
	 *r = 255;
	 *g = iv - 255;
  }
  else {
	 *r = *g = 255;
	 *b = iv - 510;
  }

}

void compicool(double v, int *r, int *g, int *b)
{
  int iv;

  iv = v * 766;
  if (iv > 766) iv = 766;
  if (iv < 0) iv = 0;
  *r = *g = *b = 0;
  if (iv <= 255) *b = iv;
  else if (iv <= 510) {
	 *b = 255;
	 *g = iv - 255;
  }
  else {
	 *b = *g = 255;
	 *r = iv - 510;
  }

}

#define BOAT_WIDTH  3.0
#define BOAT_LENGTH 10.0

void draw_boat(double x, double y, double yaw)
{

  glPushMatrix();

  glTranslated(x, y, 0.0);
  glRotated(R2D(yaw), 0.0, 0.0, 1.0);

  //  printf("draw_cross: %f, %f\n", x, y);
  glColor3d(1.0, 1.0, 1.0);
  glLineWidth(2.0);

  glBegin(GL_LINE_STRIP);
  glVertex2d(0.0, 0.0+2.0);  /* front tip */
  glVertex2d(0.0-BOAT_WIDTH/2.0, 0.0+2.0-BOAT_LENGTH);
  glVertex2d(0.0+BOAT_WIDTH/2.0, 0.0+2.0-BOAT_LENGTH);
  glVertex2d(0.0, 0.0+2.0);  /* front tip */
  glEnd();

  glLineWidth(1.0);

  glPopMatrix();
}
