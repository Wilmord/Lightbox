// Global module fragment where #includes can happen
module;
#include <cstdio>
#include <opencv2/opencv.hpp>

// first thing after the Global module fragment must be a module command
export module Display;

export class Display {
public:
  Display();
  ~Display();
  void display(const std::string& imageName);
};

Display::Display() = default;
Display::~Display() = default;

void Display::display(const std::string& imageName)
{ 
    cv::Mat image;
    image = cv::imread(imageName, cv::IMREAD_COLOR );
    if ( !image.data )
    {
        printf("No image data \n");
    }
    else
    {
        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
        cv::imshow("Display Image", image);
        cv::waitKey(0);
    }
 }