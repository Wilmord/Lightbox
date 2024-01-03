module;

#include <cstdio>
#include <opencv2/opencv.hpp>

export module DisplayManager;

export class DisplayManager {
public:
    DisplayManager(const std::string& imageName)
    {
        std::string imagePath = cv::samples::findFile(imageName);
        mImage = cv::imread(imageName, cv::IMREAD_COLOR);
        if (mImage.empty())
        {
            throw std::invalid_argument("Could not read the image!");
        }
    }
  ~DisplayManager() = default;
  void display();
  void displayWithHistogram();
  void displayTogether(const cv::Mat& imageLeft, const cv::Mat& imageRight);

  void write(const std::string& imageName);
  std::unique_ptr<cv::Mat> getHistogram(const cv::Mat& img);

private:
    cv::Mat mImage;

};

void DisplayManager::display()
{ 
   cv::namedWindow("Display Window", cv::WINDOW_FULLSCREEN);
   cv::imshow("Display Window", mImage);
   cv::waitKey();
 }

void DisplayManager::displayTogether(const cv::Mat& imageLeft, const cv::Mat& imageRight)
{
    cv::Mat finalImage;
    cv::hconcat(imageLeft, imageRight, finalImage);
    cv::imshow("Image with Histogram", finalImage);
    cv::waitKey();
}

void DisplayManager::displayWithHistogram()
{
    auto histImage = getHistogram(mImage);
    displayTogether(mImage, *histImage);
}

void DisplayManager::write(const std::string& imageName)
{
    cv::imwrite(imageName, mImage);
}

std::unique_ptr<cv::Mat> DisplayManager::getHistogram(const cv::Mat& image)
{
    std::vector<cv::Mat> bgr_planes;
    cv::split(image, bgr_planes);

    int histSize = 256; // number of bins
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    
    cv::Mat b_hist, g_hist, r_hist;
    cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);
    
    int hist_w = image.cols, hist_h = image.rows;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    for (int i = 1; i < histSize; i++)
    {
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
            cv::Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
            cv::Scalar(0, 0, 255), 2, 8, 0);
    }
    return std::make_unique<cv::Mat>(histImage);
}

