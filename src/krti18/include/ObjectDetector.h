#ifndef OBJ_DETECTOR
#define OBJ_DETECTOR

#include <vector>
#include <math.h>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace vision {

class ObjectDetector{
  public:
  	ObjectDetector();
  	void findSquare(const cv::Mat& image,
  					        cv::Vec3f &square);
  	void findCircle(const cv::Mat& image,
  					        cv::Vec3f &circle);
    void findColor(const cv::Mat& image,
                   cv::Vec3f &color,
                   int lH, int hH,
                   int lS, int hS,
                   int lV, int hV);
  	void drawSquare(cv::Mat& image,
  					        const cv::Vec3f &square);
  	void drawCircle(cv::Mat& image,
  					        const cv::Vec3f &circle);
    void markColor(cv::Mat& image,
                   const cv::Vec3f &color);
};

} // namespace obj

#endif
