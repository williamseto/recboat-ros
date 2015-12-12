/**********
 * path.c - store and manipulate paths
 * Jeff McMahill (jmcm@ri.cmu.edu)
 * Copyright (c) 2002 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

struct path_type {
  double *x;
  double *y;
  double *h;
  int npts;
  int nalloc;
};

#ifdef __cplusplus
extern "C" {
#endif

struct path_type *path_init();
void path_free(struct path_type *p);
int path_addpt(struct path_type *p, double x, double y, double h);
void path_clear(struct path_type *p);
void path_norm(struct path_type *p);
int path_write(struct path_type *p, char *filename);
int path_writefp(struct path_type *p, FILE *fp);
struct path_type *path_read(char *filename);
struct path_type *path_readfp(FILE *fp);
struct path_type *path_read_csv(char *filename);
struct path_type *path_readfp_csv(FILE *fp);
void path_stddev(struct path_type *p, double *sdx, double *sdy, double *sdz);
void path_mean(struct path_type *p, double *mx, double *my, double *mz);
void pathwin_add_wpt(double x, double y);
void pathwin_clear_wpt();
#ifdef __cplusplus
}
#endif
