#include "ObjectDetector.h"

using namespace vision;

/*  ===============
    HELPER FUNCTION
    ===============  */
// One side imfill equivalent to Matlab imfill + Canny
// Keyword in google : imfill learnopencv
void imfill(cv::Mat src, cv::Mat &dst){
	dst = src.clone();
	cv::floodFill(dst, cv::Point(0,0), cv::Scalar(255));
	cv::bitwise_not(dst, dst);
	dst = (src | dst);
  cv::Canny(dst, dst, 10, 30, 3);
}

// All side imfill + Canny
void imfill_all_side(cv::Mat src, cv::Mat &dst){
  cv::Mat s1, s2, s3, s4;
  s1 = src.clone();
  s2 = src.clone();
  s3 = src.clone();
  s4 = src.clone();

  cv::floodFill(s1, cv::Point(         0,          0), cv::Scalar(255));
  cv::floodFill(s2, cv::Point(src.rows-1,          0), cv::Scalar(255));
  cv::floodFill(s3, cv::Point(         0, src.rows-1), cv::Scalar(255));
  cv::floodFill(s4, cv::Point(src.rows-1, src.rows-1), cv::Scalar(255));

  cv::bitwise_not(s1, s1);
  cv::bitwise_not(s2, s2);
  cv::bitwise_not(s3, s3);
  cv::bitwise_not(s4, s4);

  cv::Canny(s1, s1, 10, 30, 3);
  cv::Canny(s2, s2, 10, 30, 3);
  cv::Canny(s3, s3, 10, 30, 3);
  cv::Canny(s4, s4, 10, 30, 3);

  dst = (src | s1 | s2 | s3 | s4);
}

// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/std::sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

/*  ================
    CLASS DEFINITION
    ================  */

// Constructor does nothing
ObjectDetector::ObjectDetector(){};

/*
  Find smallest square

  Draw a circle out of 4 points of the smallest square (to find the center point)
  Mutate the "cv::Vec3f square" (as return value replacement)

  Why smallest?
  According to observation, the best detected square is the smallest one
*/
void ObjectDetector::findSquares(const cv::Mat& image,
                                 cv::Vec3f &square){
  int thresh = 50, N = 11;

  std::vector<cv::Point> best_approx;
  cv::Point2f center;
  float radius;
  float best_radius=350.;

  cv::Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    //cv::pyrDown(image, pyr, cv::Size(image.cols/2, image.rows/2));
    //cv::pyrUp(pyr, timg, image.size());
    cv::medianBlur(image, timg, 9);
    std::vector<std::vector<cv::Point> > contours;

    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        cv::mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                cv::Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }

            // find contours and store them all as a list
            cv::findContours(gray, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

            std::vector<cv::Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                    std::fabs(cv::contourArea(cv::Mat(approx))) > 1000 &&
                    cv::isContourConvex(cv::Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = std::fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 ){
                      // Find smallest square
                      cv::minEnclosingCircle(approx, center, radius);

                      if(radius < best_radius){
                        best_radius = radius;
                        square[0] = center.x;
                        square[1] = center.y;
                        square[2] = radius;
                      }
                    }
                }
            }
        }
    }
}

/*
  Find smallest circle

  Why smallest?
  According to observation, the best detected circle is the smallest one
*/
void ObjectDetector::findCircles(const cv::Mat& image,
                                 cv::Vec3f &circle){
    // Variables init
    cv::Mat gray, res;
    const int morph_size = 2;
    const int d = 10, sigma_color = 80, sigma_space = 80;
    const int low_canny_th = 10;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                        cv::Size( 2*morph_size + 1, 2*morph_size+1 ),
                        cv::Point( morph_size, morph_size ));

    // Preprocess (filtering)
    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    cv::bilateralFilter(gray, res, d, sigma_color, sigma_space);
    cv::Canny(res, res, low_canny_th, low_canny_th*3, 3);
    cv::morphologyEx(res, res, cv::MORPH_CLOSE, element);
    //imfill(res, res);
    //cv::Canny(res, res, low_canny_th, low_canny_th*3, 3);
    imfill_all_side(res, res);

    // Detect circle
    std::vector <cv::Vec3f> circles;
    cv::HoughCircles(res, circles, cv::HOUGH_GRADIENT, 1, image.rows/8, 30, 30, 0, 0);
    
    // Take only the smallest circle
    float best_radius=350.;

    for(size_t i=0; i<circles.size(); ++i){
      float current_radius = circles[i][2];
      if(current_radius < best_radius){
        best_radius = current_radius;
        circle = circles[i];
      }
    }
}

/*
*/
void ObjectDetector::drawSquares(cv::Mat& image,
                                 const cv::Vec3f &square){
  cv::Point center(std::round(square[0]), std::round(square[1]));
  int radius = std::round(square[2]);
  cv::circle(image, center, 3, cv::Scalar(0,255,0), -1, 8, 0);
  cv::circle(image, center, radius, cv::Scalar(0,0,255), 3, 8, 0);
}

void ObjectDetector::drawCircles(cv::Mat& image,
                                 const cv::Vec3f &circle){
  cv::Point center(std::round(circle[0]),std::round(circle[1]));
  int radius = std::round(circle[2]);
  cv::circle(image, center, 3, cv::Scalar(0,255,0), -1, 8, 0);
  cv::circle(image, center, radius, cv::Scalar(0,0,255), 3, 8, 0);
}
