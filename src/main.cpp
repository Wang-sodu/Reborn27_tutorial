#include "ArmorDetector.hpp"
#include "drewPicture.hpp"
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
    ArmorDetector ad;
    for (;;)
    {
        video >> frame;
        if (frame.empty())
        {
            break;
        }
        vector<RotatedRect> lightInfo = ad.detect(frame);

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
        Mat rvec, tvec;
        ad.pnp(PPoints,rvec, tvec);
        drewPicture(frame, rvec, tvec, true);
        imshow("video", frame);
        waitKey(5);
    }
    video.release();
    destroyAllWindows();
}