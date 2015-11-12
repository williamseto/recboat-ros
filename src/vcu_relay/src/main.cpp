
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include "vcu_relay/vcu_status.h"
#include "vcu_relay/vcu_cmd_stop.h"
#include "vcu_relay/vcu_cmd_drive.h"

#include "recboat.h"
#include "recboat_interface.h"

#define RECBOAT_IP    "192.168.2.20"
#define RECBOAT_PORT  1507

static struct recboat_type *rboat = NULL;

void cmd_drive_cb(const vcu_relay::vcu_cmd_drive::ConstPtr& msg)
{

  //  ROS_INFO("got drive! [%f %f %f]", msg->port, msg->stbd, msg->steer);

  if (rboat)
    recboat_drive(rboat, msg->port, msg->stbd, msg->steer);

}

void cmd_stop_cb(const vcu_relay::vcu_cmd_stop::ConstPtr& msg)
{

  //  ROS_INFO("got stop! [%d]", msg->stop);

  if (rboat)
    recboat_stop(rboat, msg->stop);
}

static void copy_status(uint8_t *buf, int len, vcu_relay::vcu_status *out)
{
  struct recboat_status *stat;

  if (len < sizeof(struct recboat_status)) {
    printf("copy_status: recv size mismatch?! [%d / %d]\n", len, sizeof(struct recboat_status));
    return;
  }

  stat = (struct recboat_status *) buf;

  out->ver = stat->ver;
  out->sec = stat->sec;
  out->usec = stat->usec;

  out->state = stat->state;

  out->port_throttle = stat->port_throttle;
  out->stbd_throttle = stat->stbd_throttle;
  out->port_shift = stat->port_shift;
  out->stbd_shift = stat->stbd_shift;

  out->port_throttle_out = stat->port_throttle_out;
  out->stbd_throttle_out = stat->stbd_throttle_out;

  out->steer_angle = stat->steer_angle;

  out->hci_switch = stat->hci_switch;
  out->port_ind = stat->port_ind;
  out->stbd_ind = stat->stbd_ind;

  out->remote_select = stat->remote_select;
  out->autoled = stat->autoled;

  out->have_ctrl = stat->have_ctrl;

  out->steer_angle_req = stat->steer_angle_req;
  out->steer_mode = stat->steer_mode;

  out->rt_amps = stat->rt_amps;
  out->rt_bamps = stat->rt_bamps;
  out->rt_ff = stat->rt_ff;
  out->rt_fm = stat->rt_fm;
  out->rt_fs = stat->rt_fs;
  out->rt_power = stat->rt_power;
  out->rt_temp = stat->rt_temp;
  out->rt_volt = stat->rt_volt;

}

int main(int argc, char **argv)
{
  vcu_relay::vcu_status status_msg;
  struct pollfd pfd[1];
  int ret, rlen, s;
  uint8_t buf[1024];

  rboat = recboat_init(RECBOAT_IP, RECBOAT_PORT);

  if (!rboat) {
    std::cout << "Error connecting to VCU!" << std::endl;
    exit(-1);
  }

  ros::init(argc, argv, "vcu_relay");

  ros::NodeHandle n;

  ros::Publisher status_pub = n.advertise<vcu_relay::vcu_status>("recboat/vcu_status", 10);

  ros::Subscriber stop_sub = n.subscribe("recboat/vcu_cmd_stop", 10, cmd_stop_cb);
  ros::Subscriber drive_sub = n.subscribe("recboat/vcu_cmd_drive", 10, cmd_drive_cb);

  s = recboat_getfd(rboat);

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
        } else if ((buf[1] == 0) && (buf[2] == 100)) {
          if (sizeof(struct recboat_status) != rlen-10)
            printf("struct: %d, recv: %d(-4)\n", sizeof(struct recboat_status), rlen);
          copy_status(&buf[8], rlen-10, &status_msg);
          status_msg.header.stamp = ros::Time::now();
          status_pub.publish(status_msg);
        }
      }
    }

    ros::spinOnce();

  }

  return 0;
}
