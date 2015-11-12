/**********
 * pathwin.c - path display window functions
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * National Robotics Engineering Consortium, Carnegie Mellon University
 * Copyright (c) 2012 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

#ifdef WIN32
#include <windows.h>
#define GL_BGR GL_BGR_EXT
#define GL_BGRA GL_BGRA_EXT
#endif
#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <malloc.h>
#include <string.h>

#include <pthread.h>
#include <semaphore.h>

#ifndef WIN32
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#endif

#include "path.h"

#include "misc.h"

static GtkWidget *path_widget = NULL;

//static struct double_rect path_box = {0};
static struct double_box world_box;

void draw_grid(double xstart, double ystart, double xend, double yend,
               double xoffset, double yoffset);

static void draw();
extern void draw_cross(double x, double y);
void draw_mark(double mx, double my, double r, double g, double b);
void draw_robot(double alpha, int outline);

static double xoffset = 0.0;
static double yoffset = 0.0;

static GLdouble model_matrix[16];
static GLdouble proj_matrix[16];
static GLint view_matrix[4];

struct path_type *path = NULL;
static struct path_type *trail = NULL;

void path_refresh();

int path_draw_ctrl = 1;

static double start_x = 0.0;
static double start_y = 0.0;
static double goal_x = 0.0;
static double goal_y = 0.0;
static double curgoal_x = 0.0;
static double curgoal_y = 0.0;
static int curgoal_valid = 0;

static int nav_state = 0;

static pthread_mutex_t trail_mutex;

struct path_type *wpt_path = NULL;

void click_waypoint(double north, double east);

static void reshape(GtkWidget *w)
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context(w);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(w);

  if (gdk_gl_drawable_gl_begin(gldrawable, glcontext)) {
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

	  xoffset = (world_box.xstart + world_box.xend) / 2.0;
	  yoffset = (world_box.ystart + world_box.yend) / 2.0;

     gluOrtho2D(world_box.xstart-xoffset, world_box.xend-xoffset,
                world_box.ystart-yoffset, world_box.yend-yoffset);
     //     gluOrtho2D(world_box.ystart-yoffset, world_box.yend-yoffset,
     //                world_box.xend-xoffset, world_box.xstart-xoffset);
     //    glRotated(-90.0, 0.0, 0.0, 1.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glGetDoublev(GL_MODELVIEW_MATRIX, model_matrix);
     glGetDoublev(GL_PROJECTION_MATRIX, proj_matrix);
     glGetIntegerv(GL_VIEWPORT, view_matrix);
     gdk_gl_drawable_gl_end (gldrawable);
  }

}

static double scroll_sx = 0.0, scroll_sy = 0.0;

static int sel_mode = 0;

static gint button(GtkWidget *w, GdkEventButton *event)
{
    double realy, wx, wy, wz;
    double a;
    char *str;
    double winx, winy, winz;
    double dx, dy;
    int i;

    realy = view_matrix[3] - event->y - 1;
    gluUnProject(event->x, realy, 0.0, model_matrix, proj_matrix,
                     view_matrix, &wx, &wy, &wz);

    printf("clicked: (%f, %f)\n", xoffset+wx, yoffset+wy);
    //    pathwin_add_trail(xoffset+wx, yoffset+wy);

    if (event->button == 1) {
      scroll_sx = event->x;
      scroll_sy = event->y;
      
      click_waypoint(yoffset+wy, xoffset+wx);

    }
    else if (event->button == 2) {
      scroll_sx = event->x;
      scroll_sy = event->y;
    }
    else if (event->button == 3) {
      {
         double dx, dy;

         dx = world_box.xend - world_box.xstart;
         dy = world_box.yend - world_box.ystart;

         if (event->state & GDK_SHIFT_MASK) {
            //            printf("zoom out...\n");
            dx *= 1.2;
            dy *= 1.2;
            wx = (world_box.xstart + world_box.xend)/2.0;
            wy = (world_box.ystart + world_box.yend)/2.0;
         }
         else {
            //            printf("zoom in...\n");
            dx *= 0.8;
            dy *= 0.8;
				//            wx = (world_box.xstart + world_box.xend)/2.0;
				//            wy = (world_box.ystart + world_box.yend)/2.0;
				wx += xoffset;
				wy += yoffset;
         }

         world_box.xstart = wx - dx/2.0;
         world_box.xend = wx + dx/2.0;
         world_box.ystart = wy - dy/2.0;
         world_box.yend = wy + dy/2.0;
         reshape(path_widget);

         //         path_refresh();

         printf("xsize: %f, ysize: %f\n",
                world_box.xend - world_box.xstart,
                world_box.yend - world_box.ystart);

      }
      return(TRUE);
    }

    return(FALSE);
}

// Mouse
static gboolean motion(GtkWidget *w, GdkEventMotion *event, gpointer d)
{
  double realy, wx, wy, wz;
  double dx, dy;
  int scroll = 0;

  realy = view_matrix[3] - event->y - 1;
  gluUnProject(event->x, realy, 0.0, model_matrix, proj_matrix,
                    view_matrix, &wx, &wy, &wz);

  //  if (!event->state)
  //    gtruth_click(wx+xoffset, wy+yoffset, 0);


  if (event->state & GDK_CONTROL_MASK || sel_mode) {
    return(TRUE);
  }

  if (event->state & GDK_SHIFT_MASK) {

    return(TRUE);
  }

  if (event->state & GDK_BUTTON1_MASK) {
    scroll = 1;
  }

  if (scroll) {
     //     dx = event->x - scroll_sx;
     //     dy = event->y - scroll_sy;
     realy = view_matrix[3] - scroll_sy - 1;
     gluUnProject(scroll_sx, realy, 0.0, model_matrix, proj_matrix,
                      view_matrix, &dx, &dy, &wz);
     dx -= wx;
     dy -= wy;
     world_box.xstart += dx;
     world_box.ystart += dy;
     world_box.xend += dx;
     world_box.yend += dy;
     xoffset += dx;
     yoffset += dy;
     //     reshape(w);
     //     path_refresh();
     scroll_sx = event->x;
     scroll_sy = event->y;
  }

  return(FALSE);
}

static gint scroll(GtkWidget *w, GdkEventScroll *event)
{
    double realy, wx, wy, wz;
    double dx, dy;

    realy = view_matrix[3] - event->y - 1;
    gluUnProject(event->x, realy, 0.0, model_matrix, proj_matrix,
                     view_matrix, &wx, &wy, &wz);

    printf("scroll: (%f, %f)\n", xoffset+wx, yoffset+wy);
    //    printf("%f %f : %f %f\n", event->x, event->y, event->x_root, event->y_root);

    dx = world_box.xend - world_box.xstart;
    dy = world_box.yend - world_box.ystart;

    if (event->direction == GDK_SCROLL_UP) {
      //            printf("zoom out...\n");
      dx *= 1.1;
      dy *= 1.1;
      wx = (world_box.xstart + world_box.xend)/2.0;
      wy = (world_box.ystart + world_box.yend)/2.0;
    }
    else if (event->direction == GDK_SCROLL_DOWN) {
      //            printf("zoom in...\n");
      dx *= 0.90;
      dy *= 0.90;
                  wx = (world_box.xstart + world_box.xend)/2.0;
                  wy = (world_box.ystart + world_box.yend)/2.0;
                  //      wx += xoffset;
                  //      wy += yoffset;
    }
    else {
      return(FALSE);
    }

    world_box.xstart = wx - dx/2.0;
    world_box.xend = wx + dx/2.0;
    world_box.ystart = wy - dy/2.0;
    world_box.yend = wy + dy/2.0;
    reshape(path_widget);

    //    path_refresh();

    //    printf("xsize: %f, ysize: %f\n",
    //           world_box.xend - world_box.xstart,
    //           world_box.yend - world_box.ystart);

    return(TRUE);

}

void path_realize(GtkWidget *w, GtkWidget *ebox)
{
  GdkGLContext *glcontext;
  GdkGLDrawable *gldrawable;
  float vals[2];
  int val;
  //  GLenum glerr;
  //  char *str;

  printf("path_realize...\n");

  pthread_mutex_init(&trail_mutex, NULL);

  glcontext = gtk_widget_get_gl_context(w);
  gldrawable = gtk_widget_get_gl_drawable(w);

  path_widget = w;

  g_signal_connect(G_OBJECT(ebox), "button_press_event", G_CALLBACK(button), NULL);
  //  g_signal_connect(G_OBJECT(ebox), "button_release_event", G_CALLBACK(button_rel), NULL);
  g_signal_connect(G_OBJECT(ebox), "motion_notify_event", G_CALLBACK(motion), NULL);
  g_signal_connect(G_OBJECT(ebox), "scroll_event", G_CALLBACK(scroll), NULL);
  //  g_signal_connect(G_OBJECT(w), "key_press_event", G_CALLBACK(keypress), NULL);

  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return;

  glDisable(GL_TEXTURE_2D);

  gdk_gl_drawable_gl_end (gldrawable);
}

gboolean path_configure(GtkWidget *widget, GdkEventConfigure *event, gpointer d)
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(widget);
  GLfloat w, h;
  double a;
  //  struct float_box b;
  //  double dx, dy, c;

  if (!path) path = path_init();

  w = widget->allocation.width;
  h = widget->allocation.height;
  //  a = w / h;
  a = h / w;

  //  if (!imagevi) {
	 world_box.xstart = -40.0;
	 world_box.xend = 40.0;
	 world_box.ystart = world_box.xstart * a;
	 world_box.yend = world_box.xend * a;
    //  }

  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return(FALSE);

  glViewport(0, 0, w, h);

  gdk_gl_drawable_gl_end (gldrawable);

  reshape(widget);

  return(TRUE);
}

gboolean path_expose(GtkWidget *widget, GdkEventExpose *event, gpointer d)
{
  GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(widget);
  static int count = 0;
  static GTimer *fps = NULL;
  //  char filename[600];

  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return(FALSE);

   if (!fps)
    fps = g_timer_new();

   count++;
   if (count > 120) {
     //     printf("fps = %.1f\n", count / g_timer_elapsed(fps, NULL));
     g_timer_reset(fps);
     count = 0;
   }

  draw();

  /* Swap buffers */
  if (gdk_gl_drawable_is_double_buffered (gldrawable))
    gdk_gl_drawable_swap_buffers (gldrawable);
  else glFlush ();

  gdk_gl_drawable_gl_end (gldrawable);

  return(TRUE);
}

void path_refresh()
{

  if (!path_widget) return;

  path_expose(path_widget, NULL, NULL);

  //  gdk_window_invalidate_rect(path_widget->window, &path_widget->allocation, TRUE);
}

#if 0
static void path_interp(struct path_type *path, double t, double *x, double *y, double *h)
{
    double dx, dy;
    int i;

    if (!path->npts) return;

    i = (int) floor(t);
    if (i >= path->npts-1) {
        *x = path->x[i];
        *y = path->y[i];

        if (i) {
            dx = path->x[i] - path->x[i-1];
            dy = path->y[i] - path->y[i-1];
            *h = R2D(atan2(dy, dx))-90.0;
        }
        else
            *h = path->h[i];

        return;
    }
    t -= i;

    dx = path->x[i+1] - path->x[i];
    dy = path->y[i+1] - path->y[i];

    *x = path->x[i] + dx*t;
    *y = path->y[i] + dy*t;

    *h = R2D(atan2(dy, dx))-90.0;

}

void path_draw_wide(struct path_type *path, double w)
{
    int i;
    double a, dx, dy;

    glLineWidth(1.0);
//    glBegin(GL_LINE_STRIP);
    glBegin(GL_QUAD_STRIP);
//    glBegin(GL_LINES);
//    glBegin(GL_QUADS);
    for (i = 0; i < path->npts-1; i++) {
        dx = path->x[i+1] - path->x[i];
        dy = path->y[i+1] - path->y[i];
        if (!dx && !dy) continue;

        a = atan2(dy, dx);
        a += M_PI/2.0;
        dx = w * cos(a);
        dy = w * sin(a);
        glVertex2d(path->x[i] + dx-xoffset, path->y[i] + dy-yoffset);
        glVertex2d(path->x[i] - dx-xoffset, path->y[i] - dy-yoffset);

        glVertex2d(path->x[i+1] + dx-xoffset, path->y[i+1] + dy-yoffset);
        glVertex2d(path->x[i+1] - dx-xoffset, path->y[i+1] - dy-yoffset);
//        glVertex2d(path->x[i], path->y[i]);
    }
    glEnd();
}

static double clamp(double val, double min, double max)
{

  if (val < min) val = min;
  if (val > max) val = max;

  return(val);
}

static void draw_curve(double px, double py, double x0, double y0,
                       double x1, double y1)
{
  double a, r, cx, cy, start, end, x, y, t;

  cx = (x0+x1)/2.0;
  cy = (y0+y1)/2.0;

  r = dist(x0, y0, x1, y1) / 2.0;

  start = atan2(y0-cy, x0-cx);

  t = (x0-px)*(y1-py)-(y0-py)*(x1-px);
  if (t < 0.0)
    end = start - M_PI;
  else
    end = start + M_PI;
  //  end = atan2(y1-cy, x1-cx);
  //  if (end < start) {
  //    t = start;
  //    start = end;
  //    end = t;
  //  }

  if (start < end) {
    for (a = start; a <= end; a += 0.1) {
      x = r * cos(a) + cx;
      y = r * sin(a) + cy;
      glVertex2d(x, y);
    }
  }
  else {
    for (a = start; a >= end; a -= 0.1) {
      x = r * cos(a) + cx;
      y = r * sin(a) + cy;
      glVertex2d(x, y);
    }
  }

}

void draw_path_index(struct path_type *p, int start,
                     double xoff, double yoff)
{
  int i;
  int npts;
  double px, py;

  npts = p->npts;
  //    glColor3d(1.0, 1.0, 0.0);
  glLineWidth(2.0);

  glBegin(GL_LINE_STRIP);
  for (i = start; i < npts; i++) {
    if (p->h[i] == 2.0) continue;
    glVertex2d(p->x[i]-xoff, p->y[i]-yoff);
    if (p->h[i] == 1.0 && i+1 < npts) {  /* curve */
      draw_curve(px-xoff, py-yoff,
                 p->x[i]-xoff, p->y[i]-yoff, p->x[i+1]-xoff, p->y[i+1]-yoff);
      //                 p->x[i]-xoff, p->y[i]-yoff, p->x[i+2]-xoff, p->y[i+2]-yoff);
    }
    px = p->x[i];
    py = p->y[i];
  }
  glEnd();

  glLineWidth(1.0);

}
#endif

void draw_path(struct path_type *p, double xoff, double yoff)
{
  int i;

  //    glColor3d(1.0, 1.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
    for (i = 0; i < p->npts; i++) {
      glVertex2d(p->x[i]-xoff, p->y[i]-yoff);
    }
    glEnd();

    glLineWidth(1.0);

}

static void draw()
{
  int i;

//    glClearColor(0.2, 0.2, 0.2, 0.0);
    glClearColor(0.1, 0.3, 0.1, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

#if 1
    draw_grid(world_box.xstart, world_box.ystart,
              world_box.xend, world_box.yend, xoffset, yoffset);
#endif

    pthread_mutex_lock(&trail_mutex);
    if (path_draw_ctrl && trail) {
      glColor3d(1.0, 1.0, 0.0);
      draw_path(trail, xoffset, yoffset);
    }

    if (wpt_path) {
      glColor3d(0.5, 0.5, 0.0);
      draw_path(wpt_path, xoffset, yoffset);
      glColor3d(0.7, 0.7, 0.7);
      for (i = 0; i < wpt_path->npts; i++)
        draw_start(wpt_path->x[i] - xoffset, wpt_path->y[i] - yoffset);
    }

    if (nav_state) {
      glLineWidth(2.0);
      glColor3d(0.5, 0.0, 1.0);
      glBegin(GL_LINES);
      glVertex2d(start_x - xoffset, start_y - yoffset);
      glVertex2d(goal_x - xoffset, goal_y - yoffset);
      glEnd();

      glColor3d(1.0, 0.0, 0.0);
      draw_start(start_x - xoffset, start_y - yoffset);
      //      draw_mark(start_x - xoffset, start_y - yoffset, 1.0, 0.0, 0.0);

      draw_mark(goal_x - xoffset, goal_y - yoffset, 0.0, 1.0, 0.0);
      if (curgoal_valid)
        draw_mark(curgoal_x - xoffset, curgoal_y - yoffset, 0.0, 0.0, 1.0);
    }

    if (trail && trail->npts) {
      draw_boat(trail->x[trail->npts-1]-xoffset, trail->y[trail->npts-1]-yoffset,
                trail->h[trail->npts-1]);

      //      glPushMatrix();
      //      glTranslated(trail->x[trail->npts-1]-xoffset, trail->y[trail->npts-1]-yoffset, 0.0);
      //      draw_robot(0.8, 1);
      //      glPopMatrix();
    }
    pthread_mutex_unlock(&trail_mutex);

    glPopMatrix();

}

void pathwin_add_trail(double x, double y, double yaw)
{

  pthread_mutex_lock(&trail_mutex);

  if (!trail) trail = path_init();

  path_addpt(trail, x, y, yaw);

  pthread_mutex_unlock(&trail_mutex);

}

void pathwin_clear_trail()
{

  pthread_mutex_lock(&trail_mutex);

  if (trail) path_clear(trail);

  pthread_mutex_unlock(&trail_mutex);
}

void pathwin_gotoxy(double cx, double cy)
{
  double dx, dy;

  dx = world_box.xend - world_box.xstart;
  dy = world_box.yend - world_box.ystart;

  world_box.xstart = cx - dx/2.0;
  world_box.xend = cx + dx/2.0;
  world_box.ystart = cy - dy/2.0;
  world_box.yend = cy + dy/2.0;

  xoffset = cx;
  yoffset = cy;

  //  reshape(path_widget);

  path_refresh();
}

void pathwin_set_start(double x, double y)
{

  start_x = x;
  start_y = y;

}

void pathwin_set_goal(double x, double y)
{

  goal_x = x;
  goal_y = y;

}

void pathwin_set_curgoal(double x, double y, int valid)
{

  curgoal_x = x;
  curgoal_y = y;
  curgoal_valid = valid;

}

void pathwin_set_nav_state(int state)
{

  nav_state = state;
}

void pathwin_add_wpt(double x, double y)
{

  if (!wpt_path) wpt_path = path_init();

  path_addpt(wpt_path, x, y, 0.0);

}

void pathwin_clear_wpt()
{

  path_clear(wpt_path);

}
