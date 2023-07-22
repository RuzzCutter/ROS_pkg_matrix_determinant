#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "matrix_determinant/MatrixDeterminant.h"

bool serviceCallback(matrix_determinant::MatrixDeterminant::Request  &req,
         matrix_determinant::MatrixDeterminant::Response &res)
{
  res.determinant = req.aa * (req.bb * req.cc - req.bc * req.cb) -
  req.ab * (req.ba * req.cc - req.bc * req.ca) +
  req.ac * (req.ba * req.cb - req.bb * req.ca);
  ros::NodeHandle nh;
  ros::Publisher matrix_pub = nh.advertise<std_msgs::Float32>("matrix_pub", 10);
  std_msgs::Float32 msg;
  msg.data = res.determinant;
  matrix_pub.publish(msg);
  return true;
}

void topicCallback(const std_msgs::Float32::ConstPtr& msg)
{
  int det = msg -> data;
  if(det % 2 == 0)
        ROS_INFO("Determinant is odd.");
    else 
        ROS_INFO("Determinant is even.");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "matrix_determinant_server");
  ros::NodeHandle nh;

  ros::Publisher matrix_pub = nh.advertise<std_msgs::Float32>("matrix_pub", 10);
  ros::Subscriber matrix_sub = nh.subscribe("matrix_pub", 10, topicCallback);

  ros::ServiceServer service = nh.advertiseService("matrix_determinant_service", serviceCallback);
    
  ros::spin();

  return 0;
}