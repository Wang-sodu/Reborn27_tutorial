#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class ArmorDetector
{
public:
    ArmorDetector();
    ~ArmorDetector();
    vector<RotatedRect> detect(const Mat &frame);
    void pnp(vector<Point2f>& PPoints,Mat& rvec, Mat& tvec);

public:
    struct LightDescriptor
    {
        float width;
        float height;
        float angle;
        float area;
        Point2f center;

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
};