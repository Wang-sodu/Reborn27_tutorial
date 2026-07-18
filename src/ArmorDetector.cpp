#include "drewPicture.hpp"
class LightDescriptor
{
public:
    float width;
    float height;
    float angle;
    float area;
    Point2f center;

public:
    LightDescriptor() {}
    LightDescriptor(const RotatedRect &light)
    {
        width = light.size.width;
        height = light.size.height;
        center = light.center;
        angle = light.angle;
        area = light.size.area();
    }
};
int main()
{
    VideoCapture video;
    video.open("output.avi");
    if (!video.isOpened())
    {
        cout << "视频打开失败！" << endl;
        return -1;
    }
    Mat frame;
    Mat channels[3], binary, Gaussian, dilatee;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    for (;;)
    {
        video >> frame;
        if (frame.empty())
        {
            break;
        }
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

            sort(lightInfo.begin(), lightInfo.end(),
                 [](RotatedRect &a, RotatedRect &b)
                 {
                     return a.center.x < b.center.x;
                 });
        // 左灯条
        Point2f leftVerts[4];
        lightInfo[0].points(leftVerts);
        vector<Point2f> leftVec(leftVerts, leftVerts + 4);
        sort(leftVec.begin(), leftVec.end(),
             [](Point2f a, Point2f b)
             { return a.y < b.y; });
        Point2f left_top = (leftVec[0] + leftVec[1]) / 2;
        Point2f left_bottom = (leftVec[3] + leftVec[2]) / 2;
        // 右灯条
        Point2f rightVerts[4];
        lightInfo[1].points(rightVerts);
        vector<Point2f> rightVec(rightVerts, rightVerts + 4);
        sort(rightVec.begin(), rightVec.end(),
             [](Point2f a, Point2f b)
             { return a.y < b.y; });
        Point2f right_top = (rightVec[0] + rightVec[1]) / 2;
        Point2f right_bottom = (rightVec[3] + rightVec[2]) / 2;
        vector<Point2f> PPoints = {left_top, right_top, right_bottom, left_bottom};
        // 画框
        for (int i = 0; i < 4; i++)
        {
            line(frame, PPoints[i], PPoints[(i + 1) % 4], Scalar(0, 0, 255), 2);
        }
        
        Mat camera_matrix = (Mat_<double>(3, 3) << 1789.2913422305087, 0, 702.93444417420312, 0, 1789.214342198638, 557.65168675325629, 0, 0, 1);
        Mat distort_coeffs = (Mat_<double>(1, 5) << -0.075551988063684988, 0.13117079840026666, 0.0014612753636792362, -0.001318090407814957, 0);
        vector<Point3f> WPoints = {
            {-67.5, -28, 0},
            {67.5, -28, 0},
            {67.5, 28, 0},
            {-67.5, 28, 0}};
        Mat rvec, tvec;
        solvePnP(WPoints, PPoints, camera_matrix, distort_coeffs, rvec, tvec);
        drewPicture(frame, rvec, tvec, true);
        imshow("video", frame);
        waitKey(5);
    }
    video.release();
    destroyAllWindows();
}