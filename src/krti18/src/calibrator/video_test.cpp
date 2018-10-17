#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv){
	cv::VideoCapture cap(0);
	
	int lowH  = 40;
	int highH = 120;
	int lowS  = 35;
	int highS = 255;
	int lowV  = 220;
	int highV = 255;

	cv::namedWindow("Source", cv::WINDOW_NORMAL);
	cv::namedWindow("Detection", cv::WINDOW_NORMAL);
	
	cv::createTrackbar("Lower H : ", "Detection", &lowH , 179);
	cv::createTrackbar("Upper H : ", "Detection", &highH, 179);
	cv::createTrackbar("Lower S : ", "Detection", &lowS , 255);
	cv::createTrackbar("Upper S : ", "Detection", &highS, 255);
	cv::createTrackbar("Lower V : ", "Detection", &lowV , 255);
	cv::createTrackbar("Upper V : ", "Detection", &highV, 255);
	
	while(true){
		cv::Mat image;
		cv::Mat hsv;
		
		cap.read(image);
		
		cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
		cv::inRange(hsv, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), hsv);
		
		cv::erode(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::dilate(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		
		cv::dilate(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::erode(hsv, hsv, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		
		cv::imshow("Source", image);
		cv::imshow("Detection", hsv);
		
		if(cv::waitKey(10) == 27) break;
	}
	
	return 0;
}
