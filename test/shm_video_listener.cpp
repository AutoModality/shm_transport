#include <iostream>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <sstream>
#include <csignal>
#include <opencv2/opencv.hpp>
#include <shm_transport/shm_topic.hpp>
#include <cv_bridge/cv_bridge.h>
#include <ctime>

std::string node_name_ = "shm_video_listener";
std::string video_sub_topic_ = "/shm_video_talker/image_raw";

void videoCB(const sensor_msgs::Image::ConstPtr & msg)
{
	//ROS_INFO("shm_video_listener: new image is received");
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	if(!cv_ptr->image.empty())
	{
		cv::imshow(node_name_, cv_ptr->image);
		cv::waitKey(1);
	}
}

void signal_handler(int signal)
{
	//deallocate the shared memory
	cv::destroyAllWindows();
	ros::shutdown();
	exit(0);
}
int main(int argc, char** argv)
{
	signal(SIGINT,signal_handler);

	ros::init(argc, argv, node_name_,ros::init_options::NoSigintHandler);

	ros::NodeHandle n;
	shm_transport::Topic t(n);
	shm_transport::Subscriber< sensor_msgs::Image > s = t.subscribe(video_sub_topic_, 60, videoCB);

	ros::spin();
	return 0;
}
