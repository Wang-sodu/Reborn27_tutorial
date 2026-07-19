#include<iostream>
#include<opencv2/opencv.hpp>
#include<sstream>
#include<iomanip>
using namespace std;
using namespace cv;
void drewPicture(Mat& frame,const Mat& rvec,const Mat& tvec,bool show_euler);