#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <pthread.h>
#include <csignal>
#include <sstream>
#include <string>
#include <opencv2/opencv.hpp>
#include<ctime>
#include <shm_transport/shm_topic.hpp>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include<cv_bridge/cv_bridge.h>


#define MSGLEN (1920 * 1080 * 3)
#define HZ (30)

std::string node_name_ = "shm_video_talker";

int device = -1;
pthread_t frame_acquire_thread;
int shmid;
key_t key;
cv::Mat *p_img;
std::size_t memSize; //size of the memory
cv::VideoCapture cap;
int ctrlC_cnt = 0; 
const char *sharedMemoryName = "imageSM";
bool useCameraFlag = true;
int read_cnt = 0;
int data_size = 0;
shm_transport::Publisher p;
std::string video_pub_topic_ = "/" + node_name_ + "/image_raw";

void * distribute_frames(void *in_arg)
{
	//for time analysis
	time_t start, end;
	float accTime = 0.0;
	int numFrame = 0;

	cv::Mat raw_frame;

	//read one frame
	cap >> raw_frame;

	while(useCameraFlag)
	{

		//start the timer
		start = time(NULL);
		if(cap.isOpened())
		{
			cap >> raw_frame;
		} 
		else 
		{
			std::cout << "cannot open the video device." << std::endl;
			pthread_exit(NULL);
			exit(0);
		}
		if(!raw_frame.empty() && p.getNumSubscribers() > 0)
		{
			sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", raw_frame).toImageMsg();
			sensor_msgs::Image img = *msg;
			p.publish(img);

			cv::imshow(node_name_, raw_frame);
		}

		if(cv::waitKey(1) >= 0) ;
		
		numFrame+=1;
	}
}

void signal_handler(int signal)
{
	cv::destroyAllWindows();
	useCameraFlag = false;
	ros::shutdown();
	//kill the thread.
	pthread_kill(frame_acquire_thread,signal);
	std::cout << "received signal: " << signal << std::endl;
	exit(0);
	
}

int main(int argc, char** argv)
{
	

	//setup signal handler for CTRL-C
	signal(SIGINT, signal_handler);
	
	//make sure all video devices are closed
	cap.release();
	std::cout << "releasing all the resources" << std::endl;

	//wait for one second
	sleep(1);
	//open video device 0
	cap.open(device);
	std::cout << "Opened device 0" << std::endl;

	//initilize ros
	ros::init(argc,argv,node_name_,ros::init_options::NoSigintHandler);
	ros::NodeHandle nh_;
	shm_transport::Topic t(nh_);
	p = t.advertise< sensor_msgs::Image >(video_pub_topic_, HZ, 3 * MSGLEN);
	//start the video capturing thread. By this time the frames can be accessed
	pthread_create(&frame_acquire_thread, NULL, distribute_frames, (void *)1);	
	
	ros::spin();

	return 0;
}
