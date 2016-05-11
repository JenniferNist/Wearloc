#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

tf::Vector3 addToOrigin(tf::Vector3 cur_origin, tf::Vector3 offset) {
		cur_origin += offset;
		return cur_origin;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "laser");
  ros::NodeHandle node;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);
  
  tf::Vector3 origin(0.,0.,0.);
  while (node.ok()){
    transform.setOrigin(origin);
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    std::cout << "[" << origin.x() << ", " << origin.y() << ", " << origin.z() << "]" << std::endl;
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "laser"));
    rate.sleep();
    origin = addToOrigin(origin, tf::Vector3(0.1,0,0));
  }
  return 0;
}
