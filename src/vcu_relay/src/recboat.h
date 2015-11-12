/**********
 * recboat.h - Recboat VCU interface
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

struct recboat_type;

#ifdef __cplusplus
extern "C" {
#endif

struct recboat_type *recboat_init(const char *host, int port);
int recboat_stop(struct recboat_type *recboat, int stop);
int recboat_heartbeat(struct recboat_type *recboat);
int recboat_takectrl(struct recboat_type *rboat);
int recboat_llctrl(struct recboat_type *recboat, float port, float stbd, float steer);
int recboat_drive(struct recboat_type *recboat, float port, float stbd, float steer);
int recboat_pid(struct recboat_type *recboat, float p, float i, float d, float acc);
int recboat_getfd(struct recboat_type *rboat);

#ifdef __cplusplus
}
#endif
