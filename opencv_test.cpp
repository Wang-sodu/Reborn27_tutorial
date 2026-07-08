#include<opencv2/opencv.hpp>
int main() {
 // Create a black image
 cv::Mat image = cv::Mat::zeros(400, 400, CV_8UC3);
 // Draw a red circle in the center
 cv::circle(image, cv::Point(200, 200), 50, cv::Scalar(0, 0, 255), 
-1);
 // Display the image
 cv::imshow("Circle", image);
 cv::waitKey(0);
 
 return 0;
}