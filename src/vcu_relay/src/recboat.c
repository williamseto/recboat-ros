/**********
 * recboat.c - Recboat VCU interface
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University and Jeffrey D. McMahill
 * All rights reserved.
 **********/

#ifdef WIN32
#include <winsock2.h>
#endif
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "recboat_interface.h"
#include "recboat.h"

struct recboat_type {
  int s;	/* socket */
  struct sockaddr_in dest;
};

struct recboat_type *recboat_init(const char *host, int port)
{
  struct recboat_type *rboat;
  struct protoent *pt;
  struct sockaddr_in sa;
  struct hostent *he;

#ifdef WIN32
  WSADATA d;
  WORD w;

  w = MAKEWORD(2, 2);
  WSAStartup(w, &d);
#endif

  rboat = (struct recboat_type *) malloc(sizeof(struct recboat_type));

  pt = getprotobyname("udp");
  if (!pt) {
	 fprintf(stderr, "recboat_init: Cannot map udp to protocol number.\n");
	 return(NULL);
  }

  rboat->s = socket(PF_INET, SOCK_DGRAM, pt->p_proto);

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;

  sa.sin_port = htons((u_short) 1530);
  //  sa.sin_port = htons((u_short) port);

  if (bind(rboat->s, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
	 fprintf(stderr, "recboat_init: bind failed.\n");
  }

  he = gethostbyname(host);
  if (!he) {
	 fprintf(stderr, "recboat_init: host '%s' not found.\n", host);
	 return(NULL);
  }

  memset(&rboat->dest, 0, sizeof(rboat->dest));
  rboat->dest.sin_family = AF_INET;
  memcpy(&rboat->dest.sin_addr, he->h_addr, he->h_length);
  rboat->dest.sin_port = htons((u_short) port);

  return(rboat);
}

#define CRC16_GEN_POL 0x8005
#define MKSHORT(a,b) ((unsigned short)(a)|((unsigned short)(b)<<8))

static unsigned short genCRC(char *buf, int len)
{
  unsigned short uCRC16;
  unsigned char abData[2];
  int i,j;

  uCRC16=0;
  abData[0]=0;
  i = len;
  j = 0;

  while(i--)
    {
      abData[1]=abData[0];
      abData[0]=buf[j++];
      if(uCRC16 & 0x8000)
	{
	  uCRC16 = (uCRC16 & 0x7fff)<<1;
	  uCRC16 ^= CRC16_GEN_POL;
	}
      else
	uCRC16<<=1;
      uCRC16 ^=MKSHORT(abData[0],abData[1]);
    }
  
  return(uCRC16);
}

static int send_cmd(struct recboat_type *recboat, int cmd, int len, int id, char *buf)
{
  char msg[512];
  short crc = 0;
  int err = 0;

  msg[0] = 0x53;  /* start bytes */
  msg[1] = 0x74;
  msg[2] = cmd >> 8;
  msg[3] = cmd & 0xff;
  msg[4] = len >> 8;
  msg[5] = len & 0xff;
  msg[6] = id >> 8;
  msg[7] = id & 0xff;

  memcpy(&msg[8], buf, len);
  crc = genCRC(msg, len+8);
  msg[len+8] = crc >> 8;
  msg[len+8+1] = crc & 0xff;

  sendto(recboat->s, msg, len+10, 0, (struct sockaddr *) &recboat->dest,
			sizeof(recboat->dest));

  return(err);
}

int recboat_stop(struct recboat_type *rboat, int stop)
{
  int err;
  uint8_t s;

  s = stop;
  err = send_cmd(rboat, CMD_STOP, 1, 0, &s);

  return(err);
}

int recboat_heartbeat(struct recboat_type *rboat)
{
  int err;

  err = send_cmd(rboat, CMD_HEART, 0, 0, NULL);

  return(err);
}

int recboat_drive(struct recboat_type *rboat, float port, float stbd, float steer)
{
  int err;
  float d[3];

  d[0] = port;
  d[1] = stbd;
  d[2] = steer;
  err = send_cmd(rboat, CMD_DRIVE, 12, 0, (char *) &d);

  return(err);
}

int recboat_takectrl(struct recboat_type *rboat)
{
  int err;

  err = send_cmd(rboat, CMD_TAKECTRL, 0, 0, NULL);

  return(err);
}

int recboat_llctrl(struct recboat_type *rboat, float port, float stbd, float steer)
{
  int err;
  float d[3];

  d[0] = port;
  d[1] = stbd;
  d[2] = steer;
  err = send_cmd(rboat, CMD_LLCTRL, 12, 0, (char *) &d);

  return(err);
}

int recboat_pid(struct recboat_type *rboat, float p, float i, float d, float acc)
{
  int err;
  float v[4];

  v[0] = p;
  v[1] = i;
  v[2] = d;
  v[3] = acc;

  printf("sending pid: %f %f %f %f\n", p, i, d, acc);

  //  err = send_cmd(rboat, CMD_PID, 16, 0, (char *) &v);

  return(err);
}

int recboat_getfd(struct recboat_type *rboat)
{

  return(rboat->s);
}
