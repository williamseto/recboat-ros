/**********
 * glstuff.c - gtkglext initialization stuff
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * Copyright (c) 2005 Jeffrey D. McMahill
 * All rights reserved.
 **********/

#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#endif


#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glstuff.h"

static GdkGLConfig *configure_gl()
{
  static GdkGLConfig *glconfig = NULL;

  if (glconfig) return(glconfig);

  /* Try double-buffered visual */
  glconfig = gdk_gl_config_new_by_mode ((GdkGLConfigMode) (GDK_GL_MODE_RGB |
					// GDK_GL_MODE_DEPTH |
                                                           GDK_GL_MODE_DOUBLE));
  if (glconfig == NULL) {
    g_print ("\n*** Cannot find the double-buffered visual.\n");
    g_print ("\n*** Trying single-buffered visual.\n");

    /* Try single-buffered visual */
    glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB);
    //  GDK_GL_MODE_DEPTH);
    if (glconfig == NULL) {
      g_print ("*** No appropriate OpenGL-capable visual found.\n");
      exit (1);
    }
  }

  return(glconfig);
}

GtkWidget *new_glarea(void (*realize)(), void (*configure)(), void (*expose)(),
                      int width, int height, GtkWidget **gl_w)
{
  GtkWidget *draw, *event;
  static GdkGLConfig *glconfig = NULL;

  if (!glconfig) glconfig = configure_gl();

  draw = gtk_drawing_area_new();

  if (width && height)
    gtk_widget_set_size_request(draw, width, height);

  //    printf("can focus: %d\n", gtk_widget_get_can_focus(draw));
  //    printf("can default: %d\n", gtk_widget_get_can_default(draw));

  //  gtk_widget_set_can_focus(draw, 0);

  gtk_widget_set_gl_capability(draw, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);

  event = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(event), draw);

  gtk_widget_add_events(event, GDK_BUTTON1_MOTION_MASK |
			GDK_BUTTON2_MOTION_MASK |
			GDK_BUTTON3_MOTION_MASK |
                        GDK_POINTER_MOTION_MASK |
                        GDK_SCROLL_MASK |
                        GDK_BUTTON_PRESS_MASK);
                        //			GDK_KEY_PRESS_MASK);

  //    printf("can default: %d\n", gtk_widget_get_can_default(draw));
  //  printf("can focus: %d\n", gtk_widget_get_can_focus(draw));

  g_signal_connect_after(G_OBJECT(draw), "realize", G_CALLBACK(realize), event);
  g_signal_connect(G_OBJECT(draw), "configure_event", G_CALLBACK(configure), NULL);
  g_signal_connect(G_OBJECT(draw), "expose_event", G_CALLBACK(expose), NULL);

  //  printf("can focus: %d\n", gtk_widget_get_can_focus(draw));

  gtk_widget_show(draw);

  if (gl_w) *gl_w = draw;

  return(event);
}

GtkWidget *new_glarea_d(void (*realize)(), void (*configure)(),
                        void (*expose)(), int width, int height, void *d)
{
  GtkWidget *draw;
  static GdkGLConfig *glconfig = NULL;

  if (!glconfig) glconfig = configure_gl();

  draw = gtk_drawing_area_new();
  if (width && height)
    gtk_widget_set_size_request(draw, width, height);
  gtk_widget_set_gl_capability(draw, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE);
  gtk_widget_add_events(draw,
                        //         GDK_BUTTON1_MOTION_MASK |
                        //			GDK_BUTTON2_MOTION_MASK |
                        //			GDK_BUTTON3_MOTION_MASK |
                        //			GDK_POINTER_MOTION_MASK |
                        //			GDK_BUTTON_PRESS_MASK |
			GDK_KEY_PRESS_MASK);

#if 0
  if (gtk_widget_get_can_focus(draw))
    printf("Can focus!\n");
  else
    printf("Can't focus!\n");

  gtk_widget_set_can_focus(draw, 1);
#endif

  g_signal_connect_after(G_OBJECT(draw), "realize", G_CALLBACK(realize), d);
  g_signal_connect(G_OBJECT(draw), "configure_event", G_CALLBACK(configure), d);
  g_signal_connect(G_OBJECT(draw), "expose_event", G_CALLBACK(expose), d);

  return(draw);
}
