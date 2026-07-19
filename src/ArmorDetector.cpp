#include "ArmorDetector.hpp"

vector<RotatedRect> ArmorDetector::detect(const Mat &frame)
{
    Mat channels[3], binary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    split(frame, channels);
    threshold(channels[0], binary, 220, 255, 0);
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<RotatedRect> lightInfo;
    for (int i = 0; i < contours.size(); i++)
    {
        if (contours[i].size() < 5)
            continue;
        double area = contourArea(contours[i]);
        if (area <= 5 || contours[i].size() <= 1)
            continue;
        RotatedRect light_rect = minAreaRect(contours[i]);
        lightInfo.push_back(light_rect);
    }
    return lightInfo;
}
void ArmorDetector::pnp(vector<Point2f>& PPoints,Mat &rvec, Mat &tvec)
{
    
    Mat camera_matrix = (Mat_<double>(3, 3) << 1789.2913422305087, 0, 702.93444417420312, 0, 1789.214342198638, 557.65168675325629, 0, 0, 1);
    Mat distort_coeffs = (Mat_<double>(1, 5) << -0.075551988063684988, 0.13117079840026666, 0.0014612753636792362, -0.001318090407814957, 0);
    vector<Point3f> WPoints = {
        {-67.5, -28, 0},
        {67.5, -28, 0},
        {67.5, 28, 0},
        {-67.5, 28, 0}};
    solvePnP(WPoints, PPoints, camera_matrix, distort_coeffs, rvec, tvec);
}
ArmorDetector::ArmorDetector()
{
}

ArmorDetector::~ArmorDetector()
{
}