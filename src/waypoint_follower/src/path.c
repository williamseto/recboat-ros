/**********
 * path.c - store and manipulate paths
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * Copyright (c) 2002 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#include "path.h"

#define PATH_ALLOC_INIT 200
#define PATH_ALLOC_INC	200

struct path_type *wpt_path = NULL;


struct path_type *path_init()
{
  struct path_type *p;

  p = (struct path_type *) malloc(sizeof(struct path_type));
  if (p == NULL) return(NULL);

  p->npts = 0;
  p->nalloc = PATH_ALLOC_INIT;
  p->x = malloc(p->nalloc * sizeof(*(p->x)));
  p->y = malloc(p->nalloc * sizeof(*(p->y)));
  p->h = malloc(p->nalloc * sizeof(*(p->h)));

  return(p);
}

void path_free(struct path_type *p)
{

  free(p->x);
  free(p->y);
  free(p->h);
  free(p);
}

int path_addpt(struct path_type *p, double x, double y, double h)
{

  if (p->npts >= p->nalloc) {
	 p->nalloc += PATH_ALLOC_INC;
	 p->x = realloc(p->x, p->nalloc * sizeof(*(p->x)));
	 p->y = realloc(p->y, p->nalloc * sizeof(*(p->y)));
	 p->h = realloc(p->h, p->nalloc * sizeof(*(p->h)));
  }

  p->x[p->npts] = x;
  p->y[p->npts] = y;
  p->h[p->npts] = h;
  p->npts++;

  return(0);
}

void path_clear(struct path_type *p)
{

  p->npts = 0;
}

void path_norm(struct path_type *p)
{
  int i;
  double sx, sy, sh;

  sx = p->x[0];
  sy = p->y[0];
  sh = p->h[0];

  for (i = 0; i < p->npts; i++) {
	 p->x[i] -= sx;
	 p->y[i] -= sy;
	 p->h[i] -= sh;
  }

}

int path_writefp(struct path_type *p, FILE *fp)
{
  int i;

  for (i = 0; i < p->npts; i++)
    fprintf(fp, "%f %f %f\n", p->x[i], p->y[i], p->h[i]);

  return(0);
}

int path_write(struct path_type *p, char *filename)
{
  FILE *fp;
  int err;

  fp = fopen(filename, "w");
  if (fp == NULL) {
    fprintf(stderr, "path_write: error opening file '%s'\n", filename);
    return(-1);
  }

  err = path_writefp(p, fp);
  fclose(fp);

  return(err);
}

struct path_type *path_readfp(FILE *fp)
{
  struct path_type *p;
  double x = 0.0, y = 0.0, h = 0.0;
  char buf[80];

  p = path_init();
  while (!feof(fp)) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
	if (!strcmp(buf, "--\n")) break;
    sscanf(buf, "%lf %lf %lf", &x, &y, &h);
    path_addpt(p, x, y, h);
  }

  return(p);
}

struct path_type *path_read(char *filename)
{
  FILE *fp;
  struct path_type *p;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "path_read: error opening file '%s'\n", filename);
    return(NULL);
  }

  p = path_readfp(fp);
  fclose(fp);

  return(p);

}

struct path_type *path_readfp_csv(FILE *fp)
{
  struct path_type *p;
  double x, y, h;
  char buf[80];

  p = path_init();
  while (!feof(fp)) {
    if (fgets(buf, sizeof(buf), fp) == NULL) break;
	if (!strcmp(buf, "--\n")) break;
    sscanf(buf, "%lf,%lf,%lf", &x, &y, &h);
    path_addpt(p, x, y, h);
  }

  return(p);
}

struct path_type *path_read_csv(char *filename)
{
  FILE *fp;
  struct path_type *p;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "path_read_csv: error opening file '%s'\n", filename);
    return(NULL);
  }

  p = path_readfp_csv(fp);
  fclose(fp);

  return(p);

}

void path_stddev(struct path_type *p, double *sdx, double *sdy, double *sdz)
{
	int i;
	double sx = 0.0, sy = 0.0, sz = 0.0;
	double dx = 0.0, dy = 0.0, dz = 0.0;

	for (i = 0; i < p->npts; i++) {
		sx += p->x[i];
		sy += p->y[i];
		sz += p->h[i];
	}
	sx /= p->npts;
	sy /= p->npts;
	sz /= p->npts;

	for (i = 0; i < p->npts; i++) {
		dx += (p->x[i] - sx) * (p->x[i] - sx);
		dy += (p->y[i] - sy) * (p->y[i] - sy);
		dz += (p->h[i] - sz) * (p->h[i] - sz);
	}

	dx /= p->npts - 1;
	dy /= p->npts - 1;
	dz /= p->npts - 1;

	*sdx = sqrt(dx);
	*sdy = sqrt(dy);
	*sdz = sqrt(dz);
}

void path_mean(struct path_type *p, double *mx, double *my, double *mz)
{
	int i;
	double sx = 0.0, sy = 0.0, sz = 0.0;

	for (i = 0; i < p->npts; i++) {
		sx += p->x[i];
		sy += p->y[i];
		sz += p->h[i];
	}
	sx /= p->npts;
	sy /= p->npts;
	sz /= p->npts;

	*mx = sx;
	*my = sy;
	*mz = sz;
}


//Functions added by Tushar

void pathwin_add_wpt(double x, double y)
{
printf("\npath.c add");

  if (!wpt_path) wpt_path = path_init();

  path_addpt(wpt_path, x, y, 0.0);

}

void pathwin_clear_wpt()
{
printf("\npath.c clear");
  path_clear(wpt_path);

}
