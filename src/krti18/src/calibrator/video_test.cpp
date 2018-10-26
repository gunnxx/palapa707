#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv){
	cv::VideoCapture cap("/home/odroid/out.avi");
	
	int lH = 41;
	int hH = 120;
	int lS = 90;
	int hS = 255;
	int lV = 235;
	int hV = 255;
	
	cv::namedWindow("Source", cv::WINDOW_NORMAL);
	cv::namedWindow("Detection", cv::WINDOW_NORMAL);
	
	cv::createTrackbar("Lower H : ", "Detection", &lH , 179);
	cv::createTrackbar("Upper H : ", "Detection", &hH, 179);
	cv::createTrackbar("Lower S : ", "Detection", &lS , 255);
	cv::createTrackbar("Upper S : ", "Detection", &hS, 255);
	cv::createTrackbar("Lower V : ", "Detection", &lV , 255);
	cv::createTrackbar("Upper V : ", "Detection", &hV, 255);
	
	while(true){
		cv::Mat image;
		cv::Mat hsv;
		
		cap.read(image);
		
		cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
		cv::inRange(hsv, cv::Scalar(lH, lS, lV), cv::Scalar(hH, hS, hV), hsv);
		
		cv::erode(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::dilate(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		
		cv::dilate(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::erode(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		
		//cv::rectangle(image, cv::Point(230, 310), cv::Point(250, 330), cv::Scalar(0, 0, 255));
		cv::rectangle(image, cv::Point(310, 230), cv::Point(330, 250), cv::Scalar(0, 0, 255));
		
		cv::Moments oMoments = cv::moments(hsv);

		double M01 = oMoments.m01;
		double M10 = oMoments.m10;
		double Area = oMoments.m00;

		if(Area > 10) std::cout << "X : " << M10/Area << "    Y : " << M01/Area << std::endl;
		
		cv::imshow("Source", image);
		cv::imshow("Detection", hsv);
		
		if(cv::waitKey(10) == 27) break;
	}
	
	return 0;
}
