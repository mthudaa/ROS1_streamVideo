#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
   
  try
  { 
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    cv::Mat current_frame = cv_ptr->image;
    cv::imshow("camera_sub", current_frame);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("gagal convert '%s' ke 'bgr8'.", msg->encoding.c_str());
  }
}
 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "frame_listener");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("camera_sub");
}
