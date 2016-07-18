#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"

geometry_msgs::PoseStamped cur_pose;
ros::Publisher pose_pub;// = n.advertise<geometry_msgs::Pose>("slam_pose", 1000);
ros::Subscriber imu_sub;// = n.subscribe("data", 1000, imuCallback);
ros::Subscriber position_sub;// = n.subscribe("slam_out_pose", 1000, positionCallback);

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
  cur_pose.pose.orientation = msg->orientation;
}

void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  cur_pose.header = msg->header;
  cur_pose.pose.position = msg->pose.position;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  imu_sub = n.subscribe("data", 1000, imuCallback);
  position_sub = n.subscribe("slam_out_pose", 1000, positionCallback);
  pose_pub = n.advertise<geometry_msgs::PoseStamped>("slam_pose", 1000);
  while (ros::ok()) {
	pose_pub.publish(cur_pose);
	ros::spinOnce();
  }

  return 0;
}
