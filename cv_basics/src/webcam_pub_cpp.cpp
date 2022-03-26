#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
 
int main(int argc, char** argv)
{
    ros::init(argc, argv, "video_pub_cpp");
    ros::NodeHandle nh;  // Default handler for nodes in ROS
 
    const int CAMERA_INDEX = 0;
    cv::VideoCapture capture(CAMERA_INDEX); 
    if (!capture.isOpened()) {
      ROS_ERROR_STREAM("Gagal di camera " << CAMERA_INDEX << "!");
      ros::shutdown();
    }
     
    image_transport::ImageTransport it(nh);
     
    // Publish to the /camera topic
    image_transport::Publisher pub_frame = it.advertise("camera", 1);
     
    cv::Mat frame, image;
    sensor_msgs::ImagePtr msg;
 
    ros::Rate loop_rate(10);
 
    while (nh.ok()) {
      capture >> frame;
      capture.read(image);
      if (frame.empty()) {
        ROS_ERROR_STREAM("gagal capture!");
        ros::shutdown();
      }
 
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub_frame.publish(msg);
      
      cv::imshow("camera_pub", image);
      cv::waitKey(1);
 
      ros::spinOnce();
      loop_rate.sleep();
    }  
 
    capture.release();
}
