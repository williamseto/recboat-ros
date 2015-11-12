/**********
 * main.cpp - Recboat SPAN pose
 * Jeff McMahill (jmcm@nrec.ri.cmu.edu)
 * National Robotics Engineering Center, Carnegie Mellon University
 * Copyright (c) 2015 Carnegie Mellon University
 * All rights reserved.
 **********/

#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <math.h>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "span_pose/span_pose.h"

#include "latLong-UTMConversion.h"

#define SPAN_PORT  1531

#define DEG2RAD(x)  ((x)*M_PI / 180.0)

const char *pos2str(int pos)
{
  static char unkstr[30];

  if (pos == 0) return("None");
  else if (pos == 1) return("Fixed Pos");
  else if (pos == 16) return("Single");
  else if (pos == 17) return("PSRDiff");
  else if (pos == 32) return("L1_Float");
  else if (pos == 34) return("Narrow_Float");
  else if (pos == 48) return("L1_Int");
  else if (pos == 49) return("Wide_Int");
  else if (pos == 50) return("Narrow_Int");

  sprintf(unkstr, "unknown (%d)", pos);
  return(unkstr);
}

const char *sol2str(int sol)
{
  static char unkstr[30];

  if (sol == 0) return("Computed");
  else if (sol == 1) return("Insufficient_Obs");

  sprintf(unkstr, "unknown (%d)", sol);
  return(unkstr);
}

const char *stat2str(int stat)
{
  static char unkstr[30];

  if (stat == 0) return("Inactive");
  else if (stat == 1) return("Aligning");
  else if (stat == 3) return("Solution_Good");
  else if (stat == 6) return("Bad_GPS_Agreement");
  else if (stat == 7) return("Alignment_Complete");

  sprintf(unkstr, "unknown (%d)", stat);
  return(unkstr);
}

static void copy_pose(uint8_t *buf, int len, span_pose::span_pose *out)
{
  int n = 0, i;
  unsigned short msg_type;
  double lat, lon, z, roll, pitch, yaw;
  double north, east;
  UTM_ZONE_TYPE zone;
  int stat, ret;
  unsigned short msg_id;
  double north_vel, east_vel;
  int h;

  /* TODO: timestamp */

  if (buf[0] == 0xaa && buf[1] == 0x44 && buf[2] == 0x12) {
    /* long header */
    h = 28;

    msg_id = (buf[5] << 8) | buf[4];
    //          printf("got msg: %d\n", msg_id);
    if (msg_id == 423) {  /* bestgpspos */
      //      int sol_status, pos_type;

      //      sol_status = buf[28];
      //      pos_type = buf[32];

      out->sol = buf[h+0];
      out->sol_str = sol2str(out->sol);

      out->pos = buf[h+4];
      out->pos_str = pos2str(out->pos);

      out->nsat = buf[h+64];

    }
  }

  /* short header */
  if (buf[0] == 0xaa && buf[1] == 0x44 && buf[2] == 0x13) {

    h = 12;
    msg_id = (buf[5] << 8) | buf[4];

    if (msg_id == 508) {  /* inspva */
      memcpy(&lat, &buf[h+12], 8);
      memcpy(&lon, &buf[h+20], 8);
      memcpy(&z, &buf[h+28], 8);

      memcpy(&north_vel, &buf[h+36], 8);
      memcpy(&east_vel, &buf[h+44], 8);

      memcpy(&roll, &buf[h+60], 8);
      memcpy(&pitch, &buf[h+68], 8);
      memcpy(&yaw, &buf[h+76], 8);

      LLtoUTM(23, lat, lon, north, east, zone);

      memcpy(&stat, &buf[h+84], 4);

      out->lat = lat;
      out->lon = lon;
      out->north = north;
      out->east = east;
      out->z = z;

      out->vel = sqrt(north_vel*north_vel + east_vel*east_vel);

      out->roll = DEG2RAD(roll);  /* rh around y */
      out->pitch = DEG2RAD(pitch); /* rh around x */
      out->yaw = DEG2RAD(yaw);  /* lh around z, clockwise from north */

      out->ins_stat = stat;
      out->ins_str = stat2str(out->ins_stat);

    }
  }

}

int span_init(int port)
{
  int s;
  struct protoent *pt;
  struct sockaddr_in sa;
  struct hostent *he;

  pt = getprotobyname("udp");
  if (!pt) {
	 fprintf(stderr, "span_init: Cannot map udp to protocol number.\n");
	 return(-1);
  }

  s = socket(PF_INET, SOCK_DGRAM, pt->p_proto);

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;

  sa.sin_port = htons((u_short) port);

  if (bind(s, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
	 fprintf(stderr, "span_init: bind failed.\n");
    return(-1);
  }

  return(s);
}

int main(int argc, char **argv)
{
  span_pose::span_pose pose_msg;
  struct pollfd pfd[1];
  int ret, rlen, s;
  uint8_t buf[1024];

  s = span_init(SPAN_PORT);

  if (s <= 0) {
    std::cout << "Error connecting to SPAN!" << std::endl;
    exit(-1);
  }

  ros::init(argc, argv, "span_pose");

  ros::NodeHandle n;

  ros::Publisher pose_pub = n.advertise<span_pose::span_pose>("recboat/span_pose", 10);

  while (ros::ok())
  {

    pfd[0].fd = s;
    pfd[0].events = POLLIN;
    ret = poll(&pfd[0], 1, 10);
    if (ret > 0 && (pfd[0].revents & POLLIN)) {
		rlen = recv(s, buf, sizeof(buf), 0);
		if (rlen <= 0) {
			printf("recv error (%d)\n", rlen);
			perror("error: ");
		}
		else {
        if (buf[0] != 0x11) {
          printf("invalid header?! [%02x]\n", buf[0]);
        } else if ((buf[1] == 10) && (buf[2] == 2)) {
          copy_pose(&buf[8], rlen-10, &pose_msg);
          pose_msg.header.stamp = ros::Time::now();
          pose_pub.publish(pose_msg);
        }
      }
    }

    ros::spinOnce();

  }

  return 0;
}
