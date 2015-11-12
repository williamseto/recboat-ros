/**********
 * main.c - RecBoat GUI
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/time.h>

#include <math.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "misc.h"
#include "glstuff.h"

#include "path.h"
#include "pathwin.h"

#include "ros_wrapper.h"

int doneG = 0;

#define B_RUN       1
#define B_STOP      2
#define B_CLEAR     3
//#define B_PAUSE     4
#define B_ESTOP    12
#define B_QUIT     20

#define B_ADDWPT       30
#define B_STARTDRIVE   31
#define B_STOPDRIVE    32
#define B_PAUSEDRIVE   33
#define B_CLEARWPT     34
#define B_SAVEWPT      35
#define B_LOADWPT      36
#define B_NEXTWPT      37
#define B_CLEARPATH    38

#define GPIO_HCI        1
#define GPIO_PORT       2
#define GPIO_STBD       3
#define GPIO_REMSEL     4
#define GPIO_KILL       5
#define GPIO_CTRL       6

static int status_id;
static GtkWidget *w_status = NULL;
static GtkWidget *w_win = NULL;
static GtkWidget *w_gpio_on[9];
static GtkWidget *w_gpio_off[9];
static GtkWidget *w_estop_sense = NULL;
static GtkWidget *w_mode = NULL;
static GtkWidget *w_manrem = NULL;
static GtkWidget *w_num = NULL;

/* vcu status */
static GtkWidget *w_port_th = NULL;
static GtkWidget *w_stbd_th = NULL;
static GtkWidget *w_port_shift = NULL;
static GtkWidget *w_stbd_shift = NULL;
static GtkWidget *w_port_out = NULL;
static GtkWidget *w_stbd_out = NULL;
static GtkWidget *w_steer_angle = NULL;
static GtkWidget *w_steer_req = NULL;
static GtkWidget *w_steer_mode = NULL;

static GtkWidget *w_steer_slide = NULL;
static GtkWidget *w_throttle_slide = NULL;
static GtkWidget *w_dir = NULL;

static GtkWidget *w_port = NULL;
static GtkWidget *w_stbd = NULL;
static GtkWidget *w_steer = NULL;

static GtkWidget *w_rt_amps = NULL;
static GtkWidget *w_rt_bamps = NULL;
static GtkWidget *w_rt_ff = NULL;
static GtkWidget *w_rt_fm = NULL;
static GtkWidget *w_rt_fs = NULL;
static GtkWidget *w_rt_power = NULL;
static GtkWidget *w_rt_temp = NULL;
static GtkWidget *w_rt_volt = NULL;

/* pose */
static GtkWidget *w_lat = NULL;
static GtkWidget *w_lon = NULL;
static GtkWidget *w_north = NULL;
static GtkWidget *w_east = NULL;
static GtkWidget *w_alt = NULL;
           
static GtkWidget *w_roll = NULL;
static GtkWidget *w_pitch = NULL;
static GtkWidget *w_yaw = NULL;
           
static GtkWidget *w_vel = NULL;
           
static GtkWidget *w_nsat = NULL;
           
static GtkWidget *w_ins = NULL;
static GtkWidget *w_sol = NULL;
static GtkWidget *w_pos = NULL;

static GtkWidget *w_vel_spin = NULL;

/* navigation state */
static GtkWidget *w_nav_state = NULL;

extern struct path_type *wpt_path;

static pthread_t ros_pthread;
void *ros_thread(void *d);
void ros_init(int *argc, char ***argv);
void ros_exit();

#define WPT_IMMEDIATE     1  /* override current goal */
#define WPT_ADD           2  /* set goal or add to list */
#define WPT_CLEAR         3  /* clear list */

static int nav_paused = 0;

double gettime()
{
  struct timeval tv;
  struct timezone tz;
  double time;

  gettimeofday(&tv, &tz);

  time = tv.tv_sec + tv.tv_usec / 1000000.0;

  return(time);
}

void main_quit()
{

  doneG = 1;

  printf("exiting...\n");

  ros_exit();

  gtk_main_quit();

}

static int button_cb(int p, GtkWidget *w)
{
  int b;
  char str[200];
  int i, state;
  float vel;

  b = GPOINTER_TO_INT(p);
  switch (b) {
     case B_QUIT:
		 main_quit();
		 break;
     case B_ESTOP:    /* send estop */
       //		 recboat_stop(rboat);
       state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w));
       printf("estop: %d\n", state);
       ros_vcu_estop(state);
		 break;
     case B_ADDWPT:
       //       goal_x = cur_x;
       //       goal_y = cur_y;
       //       pathwin_set_goal(goal_x, goal_y);
       //       ros_nav_wpt(cur_pose_status.north, cur_pose_status.east, 0.5, WPT_ADD);
       pathwin_add_wpt(cur_pose_status.east, cur_pose_status.north);
       break;
     case B_CLEARWPT:
       ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);
       pathwin_clear_wpt();
       break;
     case B_SAVEWPT:
       if (wpt_path)
         path_write(wpt_path, "waypoints.txt");
       break;
     case B_LOADWPT:
       if (wpt_path) path_free(wpt_path);
       wpt_path = path_read("waypoints.txt");
       break;
     case B_STARTDRIVE:
       printf("start...\n");
       /* only resend waypoints for fresh start */
       if (!nav_paused) {
         printf("sending waypoints...\n");
         ros_nav_wpt(0.0, 0.0, 0.0, WPT_CLEAR);
         if (!wpt_path || !wpt_path->npts) break;

         if (!w_vel_spin) vel = 0.5;
         else
           vel = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_vel_spin));
         printf("vel: %f\n", vel);

         for (i = 0; i < wpt_path->npts; i++) {
           ros_nav_wpt(wpt_path->y[i], wpt_path->x[i], vel, WPT_ADD);
         }
       }
       nav_paused = 0;
       usleep(100000);
       ros_nav_cmd(3);
       //       start_x = cur_x;
       //       start_y = cur_y;
       //       pathwin_set_start(start_x, start_y);
       //       driving = 1;
       break;
     case B_STOPDRIVE:
       nav_paused = 0;
       ros_nav_cmd(1);
       //       driving = 0.0;
       //       pathwin_set_curgoal(0.0, 0.0, 0);
       break;
     case B_PAUSEDRIVE:
       ros_nav_cmd(2);
       nav_paused = 1;
       //       driving = 0.0;
       //       pathwin_set_curgoal(0.0, 0.0, 0);
       break;
     case B_NEXTWPT:
       ros_nav_cmd(4);
       break;
     case B_CLEARPATH:
       pathwin_clear_trail();
       break;
     default:
		 printf("unknown button press (%d)?!\n", b);
  }
}

static void add_ctrl(GtkWidget *table, char *name, int r, int cb, int gpio)
{
  GtkWidget *label, *but;

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  w_gpio_on[gpio] = but = gtk_button_new_with_label("On");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(cb));
  gtk_table_attach_defaults(GTK_TABLE(table), but, 1, 2, r, r+1);

  w_gpio_off[gpio] = but = gtk_button_new_with_label("Off");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(cb+1));
  gtk_table_attach_defaults(GTK_TABLE(table), but, 2, 3, r, r+1);

}

static void add_gstat(GtkWidget *table, char *name, int r, int gpio)
{
  GtkWidget *label, *event;

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  w_gpio_on[gpio] = event = gtk_event_box_new();
  label = gtk_label_new("On");
  gtk_container_add(GTK_CONTAINER(event), label);
  gtk_table_attach_defaults(GTK_TABLE(table), event, 1, 2, r, r+1);

  w_gpio_off[gpio] = event = gtk_event_box_new();
  label = gtk_label_new("Off");
  gtk_container_add(GTK_CONTAINER(event), label);
  gtk_table_attach_defaults(GTK_TABLE(table), event, 2, 3, r, r+1);

}

static GtkWidget *add_status(GtkWidget *table, char *name, char *def, int r)
{
  GtkWidget *label;

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  label = gtk_label_new(def);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 1, 3, r, r+1);

  return(label);
}

static GtkWidget *add_spin_cur(GtkWidget *table, char *name, double def, GtkWidget **spin, int r)
{
  GtkWidget *label;
  char str[50];

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  sprintf(str, "%0.2f", def);
  label = gtk_label_new(str);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 1, 2, r, r+1);

  *spin = gtk_spin_button_new_with_range(0.0, 100.0, 0.01);
  gtk_table_attach_defaults(GTK_TABLE(table), *spin, 2, 3, r, r+1);

  return(label);
}

static GtkWidget *add_spin(GtkWidget *table, char *name, int r)
{
  GtkWidget *label, *spin;
  char str[50];

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  spin = gtk_spin_button_new_with_range(-2.0, 2.0, 0.01);
  gtk_table_attach_defaults(GTK_TABLE(table), spin, 1, 3, r, r+1);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0.0);

  return(spin);
}

static GtkWidget *add_spin_range(GtkWidget *table, char *name, int r, float min, float max, float step)
{
  GtkWidget *label, *spin;
  char str[50];

  label = gtk_label_new(name);
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
  //  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, r, r+1);

  spin = gtk_spin_button_new_with_range(min, max, step);
  gtk_table_attach_defaults(GTK_TABLE(table), spin, 1, 3, r, r+1);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0.0);

  return(spin);
}

static GtkWidget *vcu_status_frame()
{
  GtkWidget *frame, *table;

  frame = gtk_frame_new("VCU");

  table = gtk_table_new(26, 3, FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(table), 5);
  gtk_container_add(GTK_CONTAINER(frame), table);

  add_gstat(table, "HCI:", 0, GPIO_HCI);
  add_gstat(table, "Port:", 1, GPIO_PORT);
  add_gstat(table, "Stbd:", 2, GPIO_STBD);
  add_gstat(table, "Rem sel:", 3, GPIO_REMSEL);
  add_gstat(table, "Auto:", 4, GPIO_KILL);

  add_gstat(table, "Ctrl:", 5, GPIO_CTRL);

  //  w_estop_sense = add_status(table, "E-Stop:", "Off", 7);
  w_mode = add_status(table, "Mode:", "--", 8);

  //  w_manrem = add_status(table, "Man/Rem Sw:", "Manual", 9);
  w_port_th = add_status(table, "Port throttle:", "0.0", 10);
  w_stbd_th = add_status(table, "Stbd throttle:", "0.0", 11);
  w_port_shift = add_status(table, "Port shift:", "0.0", 12);
  w_stbd_shift = add_status(table, "Stbd shift:", "0.0", 13);
  w_port_out = add_status(table, "Port out:", "0.0", 14);
  w_stbd_out = add_status(table, "Stbd out:", "0.0", 15);
  w_steer_angle = add_status(table, "Steer angle:", "0.0", 16);
  w_steer_req = add_status(table, "Steer req:", "--", 17);
  w_steer_mode = add_status(table, "Steer mode:", "--", 18);

  w_rt_amps = add_status(table, "Amps:", "0.0", 19);
  w_rt_bamps = add_status(table, "BAmps:", "0.0", 20);
  w_rt_ff = add_status(table, "FF:", "0.0", 21);
  w_rt_fm = add_status(table, "FM:", "0.0", 22);
  w_rt_fs = add_status(table, "FS:", "0.0", 23);
  w_rt_power = add_status(table, "Power:", "0.0", 24);
  w_rt_temp = add_status(table, "Temp:", "0.0", 25);
  w_rt_volt = add_status(table, "Volt:", "0.0", 26);

  return(frame);
}

static GtkWidget *pose_status_frame()
{
  GtkWidget *frame, *table;
  int i;

  frame = gtk_frame_new("Pose");

  table = gtk_table_new(15, 3, FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(table), 5);
  gtk_container_add(GTK_CONTAINER(frame), table);

  i = 0;
  w_lat =   add_status(table, "Lat:",   "--", i++);
  w_lon =   add_status(table, "Lon:",   "--", i++);
  w_north = add_status(table, "North:", "--", i++);
  w_east =  add_status(table, "East:",  "--", i++);
  w_alt =   add_status(table, "Alt:",   "--", i++);

  w_roll =  add_status(table, "Roll:",  "--", i++);
  w_pitch = add_status(table, "Pitch:", "--", i++);
  w_yaw =   add_status(table, "Yaw:",   "--", i++);

  w_vel =   add_status(table, "Vel:",   "--", i++);

  w_nsat =  add_status(table, "NSat:",  "--", i++);

  w_ins =   add_status(table, "INS:",   "--", i++);
  w_sol =   add_status(table, "SOL:",   "--", i++);
  w_pos =   add_status(table, "POS:",   "--", i++);

  return(frame);
}

static GtkWidget *nav_status_frame()
{
  GtkWidget *frame, *table;
  int i;

  frame = gtk_frame_new("Navigation");

  table = gtk_table_new(5, 3, FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(table), 5);
  gtk_container_add(GTK_CONTAINER(frame), table);

  i = 0;
  w_nav_state =   add_status(table, "State:",   "--", i++);

  return(frame);
}

void init_win()
{
  GtkWidget *win, *vbox, *aspect, *hbox, *mainvbox, *but, *gl;
  GtkWidget *label, *frame, *table, *w, *spin;
  int i;

  for (i = 0; i < 9; i++) {
	 w_gpio_on[i] = NULL;
	 w_gpio_off[i] = NULL;
  }

  /* main window */
  w_win = win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //  gtk_widget_set_size_request(win, 200, 600);
  gtk_widget_set_size_request(win, 1280, 800);
  gtk_container_set_border_width(GTK_CONTAINER(win), 2);
  //  gtk_window_set_decorated(GTK_WINDOW(win), FALSE);
  gtk_window_set_title(GTK_WINDOW(win), "RecBoat");
  //  gtk_widget_set_size_request(win, 1280, 1024);
  //  gtk_widget_set_size_request(win, 1024, 768);
  gtk_quit_add_destroy(1, GTK_OBJECT(win));

  g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(main_quit), NULL);

  hbox = gtk_hbox_new(FALSE, 3);
  gtk_container_add(GTK_CONTAINER(win), hbox);

  /* main vbox */
  mainvbox = gtk_vbox_new(FALSE, 2);
  gtk_widget_set_size_request(mainvbox, 200, 680);
  gtk_box_pack_start(GTK_BOX(hbox), mainvbox, FALSE, FALSE, 0);

  vbox = gtk_vbox_new(FALSE, 2);
  gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

  gl = new_glarea((void (*)()) path_realize, (void (*)()) path_configure, (void (*)()) path_expose, 600, 750, NULL);
  gtk_box_pack_start(GTK_BOX(vbox), gl, TRUE, TRUE, 0);

  /* navigation controls */
  hbox = gtk_hbox_new(FALSE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

  but = gtk_button_new_with_label("Add waypoint");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_ADDWPT));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Clear waypoints");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_CLEARWPT));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Save waypoints");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_SAVEWPT));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Load waypoints");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_LOADWPT));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  w = gtk_vseparator_new();
  gtk_box_pack_start(GTK_BOX(hbox), w, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Start");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_STARTDRIVE));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Stop");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_STOPDRIVE));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Pause");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_PAUSEDRIVE));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  but = gtk_button_new_with_label("Next waypoint");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_NEXTWPT));
  gtk_box_pack_start(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  w_vel_spin = gtk_spin_button_new_with_range(0.0, 1.0, 0.01);
  gtk_box_pack_start(GTK_BOX(hbox), w_vel_spin, FALSE, TRUE, 0);

  gtk_spin_button_set_value(GTK_SPIN_BUTTON(w_vel_spin), 0.5);

  but = gtk_button_new_with_label("Clear path");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_CLEARPATH));
  gtk_box_pack_end(GTK_BOX(hbox), but, FALSE, TRUE, 0);

  /* vcu status */
  frame = vcu_status_frame();
  gtk_box_pack_start(GTK_BOX(mainvbox), frame, FALSE, FALSE, 0);

  /* pose status */
  frame = pose_status_frame();
  gtk_box_pack_start(GTK_BOX(mainvbox), frame, FALSE, FALSE, 0);

  /* nav status */
  frame = nav_status_frame();
  gtk_box_pack_start(GTK_BOX(mainvbox), frame, FALSE, FALSE, 0);

  frame = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(mainvbox), frame, FALSE, FALSE, 0);

  /* test button for estop */
  but = gtk_toggle_button_new_with_label("E-Stop");
  g_signal_connect_swapped(G_OBJECT(but), "clicked",
									G_CALLBACK(button_cb), GINT_TO_POINTER(B_ESTOP));
  gtk_box_pack_start(GTK_BOX(mainvbox), but, FALSE, FALSE, 0);

  w_status = gtk_statusbar_new();
  status_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(w_status), "status");
  gtk_statusbar_push(GTK_STATUSBAR(w_status), status_id, "Ready.");
  gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(w_status), 0);
  gtk_box_pack_end(GTK_BOX(mainvbox), w_status, FALSE, TRUE, 0);

  gtk_widget_show_all(win);
}

static void set_gpio(int gpio, int state)
{
  GdkColor on, off;

  if (!w_gpio_on[gpio]) return;
  if (!w_gpio_off[gpio]) return;

  on.red = 0xffff;
  on.green = 0;
  on.blue = 0;

  off.red = 0;
  off.green = 0xffff;
  off.blue = 0;

  //  printf("gpio %d -> %s\n", gpio, state ? "on" : "off");

  if (state) {
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_NORMAL, &on);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_ACTIVE, &on);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_PRELIGHT, &on);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_SELECTED, &on);

	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_NORMAL, NULL);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_ACTIVE, NULL);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_PRELIGHT, NULL);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_SELECTED, NULL);
  }
  else {
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_NORMAL, NULL);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_ACTIVE, NULL);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_PRELIGHT, NULL);
	 gtk_widget_modify_bg(w_gpio_on[gpio], GTK_STATE_SELECTED, NULL);

	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_NORMAL, &off);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_ACTIVE, &off);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_PRELIGHT, &off);
	 gtk_widget_modify_bg(w_gpio_off[gpio], GTK_STATE_SELECTED, &off);
  }

}

static void update_label(char *fmt, double val, GtkWidget *label)
{
  char str[20];

  sprintf(str, fmt, val);
  gtk_label_set_text(GTK_LABEL(label), str);

}

static void pose_status_update(struct ros_pose_status *pose)
{
  char str[20];

  update_label("%.5f", pose->lat, w_lat);
  update_label("%.5f", pose->lon, w_lon);
  update_label("%.2f", pose->north, w_north);
  update_label("%.2f", pose->east, w_east);
  update_label("%.2f", pose->alt, w_alt);

  update_label("%.2f", pose->roll, w_roll);
  update_label("%.2f", pose->pitch, w_pitch);
  update_label("%.2f", pose->yaw, w_yaw);

  update_label("%.2f", pose->vel, w_vel);

  update_label("%.0f", pose->nsat, w_nsat);

  gtk_label_set_text(GTK_LABEL(w_ins), pose->ins_str);
  gtk_label_set_text(GTK_LABEL(w_sol), pose->sol_str);
  gtk_label_set_text(GTK_LABEL(w_pos), pose->pos_str);

}

static void nav_status_update(struct ros_nav_status *nav)
{
  char *str;

  if (nav->state == 0) str = "Idle";
  else if (nav->state == 1) str = "Active";

  gtk_label_set_text(GTK_LABEL(w_nav_state), str);

  pathwin_set_goal(nav->goal_east, nav->goal_north);
  pathwin_set_start(nav->start_east, nav->start_north);
  pathwin_set_curgoal(nav->la_east, nav->la_north, 1);
  pathwin_set_nav_state(nav->state);

}

static void vcu_status_update(struct ros_vcu_status *stat)
{
  char str[20];

  set_gpio(GPIO_HCI, stat->hci_switch);
  set_gpio(GPIO_PORT, stat->port_ind);
  set_gpio(GPIO_STBD, stat->stbd_ind);
  set_gpio(GPIO_REMSEL, stat->remote_select);
  set_gpio(GPIO_KILL, stat->autoled);

  set_gpio(GPIO_CTRL, stat->have_ctrl);

  sprintf(str, "%.2f", stat->port_throttle);
  gtk_label_set_text(GTK_LABEL(w_port_th), str);

  sprintf(str, "%.2f", stat->stbd_throttle);
  gtk_label_set_text(GTK_LABEL(w_stbd_th), str);

  sprintf(str, "%.2f", stat->port_shift);
  gtk_label_set_text(GTK_LABEL(w_port_shift), str);

  sprintf(str, "%.2f", stat->stbd_shift);
  gtk_label_set_text(GTK_LABEL(w_stbd_shift), str);

  sprintf(str, "%.2f", stat->port_throttle_out);
  gtk_label_set_text(GTK_LABEL(w_port_out), str);

  sprintf(str, "%.2f", stat->stbd_throttle_out);
  gtk_label_set_text(GTK_LABEL(w_stbd_out), str);

  sprintf(str, "%.2f", stat->steer_angle);
  gtk_label_set_text(GTK_LABEL(w_steer_angle), str);

  sprintf(str, "%.2f", stat->steer_angle_req);
  gtk_label_set_text(GTK_LABEL(w_steer_req), str);

  if (stat->steer_mode == STEER_OFF)
    gtk_label_set_text(GTK_LABEL(w_steer_mode), "Off");
  else if (stat->steer_mode == STEER_HOLD)
    gtk_label_set_text(GTK_LABEL(w_steer_mode), "Hold");
  else if (stat->steer_mode == STEER_ACTIVE)
    gtk_label_set_text(GTK_LABEL(w_steer_mode), "Active");

  /* roboteq stuff */
  sprintf(str, "%.1f", stat->rt_amps/10.0);
  gtk_label_set_text(GTK_LABEL(w_rt_amps), str);
  sprintf(str, "%.1f", stat->rt_bamps/10.0);
  gtk_label_set_text(GTK_LABEL(w_rt_bamps), str);
  sprintf(str, "%02x", stat->rt_ff);
  gtk_label_set_text(GTK_LABEL(w_rt_ff), str);
  sprintf(str, "%02x", stat->rt_fm);
  gtk_label_set_text(GTK_LABEL(w_rt_fm), str);
  sprintf(str, "%02x", stat->rt_fs);
  gtk_label_set_text(GTK_LABEL(w_rt_fs), str);
  sprintf(str, "%.1f%%", stat->rt_power/10.0);
  gtk_label_set_text(GTK_LABEL(w_rt_power), str);
  sprintf(str, "%d C", stat->rt_temp);
  gtk_label_set_text(GTK_LABEL(w_rt_temp), str);
  sprintf(str, "%.1f", stat->rt_volt/10.0);
  gtk_label_set_text(GTK_LABEL(w_rt_volt), str);

  if (stat->state == VCU_STATE_STANDBY)
    gtk_label_set_text(GTK_LABEL(w_mode), "Standby");
  else if (stat->state == VCU_STATE_AUTO)
    gtk_label_set_text(GTK_LABEL(w_mode), "Auto");
  else if (stat->state == VCU_STATE_ESTOP)
    gtk_label_set_text(GTK_LABEL(w_mode), "E-Stop");

}

#if 0
static void proc_pose(uint8_t *buf)
{
      pathwin_add_trail(east, north);

      cur_x = east;
      cur_y = north;
      pathwin_gotoxy(east, north);

}
#endif

/* callback from ros_thread */
void pose_update(struct ros_pose_status *pose)
{

  pathwin_add_trail(pose->east, pose->north, -pose->yaw);

}

void click_waypoint(double north, double east)
{

  //  ros_nav_wpt(north, east, 0.5, 0);

  pathwin_add_wpt(east, north);
}

#if 0
int idle_func()
{
  static double start = 0.0, cur, last;
  static int n = 0;

#if 0
  cur = timer_curtime();
  if (start == 0.0) start = last = cur;

  if (cur - last >= 0.05) {
    last = cur;
    n++;

    path_refresh();
  }

#endif

  /* if we return FALSE, timeout is destroyed */
  return(TRUE);
}
#endif

int idle_func(int *s)
{
	int val;


  return(TRUE);
  /* if we return FALSE, timeout is destroyed */
  //return(FALSE);
}

int run_func()
{

  /* update GUI */
  pose_status_update(&cur_pose_status);
  vcu_status_update(&cur_vcu_status);
  nav_status_update(&cur_nav_status);

  pathwin_gotoxy(cur_pose_status.east, cur_pose_status.north);
  //  path_refresh();

  return(TRUE);
}

int main(int argc, char** argv)
{
  int i;
  pthread_attr_t pattr;
  char *filename = NULL;
  char str[100];
  int err;

  ros_init(&argc, &argv);
  gtk_init(&argc, &argv);
  gtk_gl_init(&argc, &argv);

  gtk_rc_parse("gui.gtkrc");

  init_win();

  pthread_create(&ros_pthread, NULL, ros_thread, NULL);

  //  gtk_idle_add((GtkFunction) idle_func, NULL);
  g_timeout_add(100, (GtkFunction) run_func, NULL);

  gtk_main();

}
