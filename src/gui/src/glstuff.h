/**********
 * glstuff.h - gtkglext initialization stuff
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * Copyright (c) 2005 Jeffrey D. McMahill
 * All rights reserved.
 **********/

GtkWidget *new_glarea(void (*realize)(), void (*configure)(), void (*expose)(),
                      int width, int height, GtkWidget **gl_w);
GtkWidget *new_glarea_d(void (*realize)(), void (*configure)(),
                        void (*expose)(), int width, int height, void *d);
