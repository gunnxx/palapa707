#ifndef OBJ_DETECTOR_KRTI18
#define OBJ_DETECTOR_KRTI18

#include <vector>
#include <math.h>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace vision {

class ObjectDetector{
  public:
  	ObjectDetector();
  	void findSquares(const cv::Mat& image,
  					         cv::Vec3f &square);
  	void findCircles(const cv::Mat& image,
  					         cv::Vec3f &circle);
  	void drawSquares(cv::Mat& image,
  					         const cv::Vec3f &square);
  	void drawCircles(cv::Mat& image,
  					         const cv::Vec3f &circle);
};

} // namespace obj

#endif