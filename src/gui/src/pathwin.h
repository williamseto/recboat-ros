/**********
 * pathwin.h - path display window functions
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * National Robotics Engineering Consortium, Carnegie Mellon University
 * Copyright (c) 2012 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

void path_realize(GtkWidget *w);
gboolean path_configure(GtkWidget *widget, GdkEventConfigure *event, gpointer d);
gboolean path_expose(GtkWidget *widget, GdkEventExpose *event, gpointer d);
void path_refresh();
void pathwin_add_trail(double x, double y, double yaw);
void pathwin_clear_trail();
void pathwin_gotoxy(double cx, double cy);
void pathwin_set_start(double x, double y);
void pathwin_set_goal(double x, double y);
void pathwin_set_curgoal(double x, double y, int valid);
void pathwin_set_nav_state(int state);
void pathwin_add_wpt(double x, double y);
void pathwin_clear_wpt();
