#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/MarkerArray.h>

tf::Vector3 addToOrigin(tf::Vector3 cur_origin, tf::Vector3 offset) {
		cur_origin += offset;
		return cur_origin;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "laser");
  ros::NodeHandle node;
  ros::Publisher vis_pub = node.advertise<visualization_msgs::Marker>( "imu", 0 );
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time();
  marker.ns = "imu";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = 0;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 1;
  marker.scale.y = 0.1;
  marker.scale.z = 0.1;
  marker.color.a = 1.0; // Don't forget to set the alpha!
  marker.color.r = 0.0;
  marker.color.g = 1.0;
  marker.color.b = 0.0;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);
  
  tf::Vector3 origin(0.,0.,0.);
  while (node.ok()){
    transform.setOrigin(origin);
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    std::cout << "[" << origin.x() << ", " << origin.y() << ", " << origin.z() << "]" << std::endl;
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "laser"));
    vis_pub.publish( marker );
    rate.sleep();
    //origin = addToOrigin(origin, tf::Vector3(0.1,0,0));
  }
  return 0;
}
