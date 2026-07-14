#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class LightDescriptor{
public:
    float width;
    float height;
    float angle;
    float area;
    Point2f center;
public:
    LightDescriptor(){}
    LightDescriptor(const RotatedRect& light){
        width=light.size.width;
        height=light.size.height;
        center=light.center;
        angle=light.angle;
        area=light.size.area();
    }
    
};
int main(){
    Mat frame;
    Mat channels[3],binary,Gaussian,dilatee;
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
    frame=imread("image.png");
    split(frame,channels);
    threshold(channels[0],binary,220,255,0);
    findContours(binary,contours,hierarchy,RETR_TREE,CHAIN_APPROX_NONE);
    vector<RotatedRect>lightInfo;
    for(int i=0;i<contours.size();i++){
        double area=contourArea(contours[i]);
        if(area<=5||contours[i].size()<=1)
        continue;
        RotatedRect light_rect=fitEllipse(contours[i]);
        if(light_rect.size.width/light_rect.size.height>0.25)
        continue;
        lightInfo.push_back(light_rect);
    }
    /*imshow("binary",Gaussian);
    waitKey(0);
    return 0;*/
    Point2f vertices1[4],vertices2[4];
    lightInfo[0].points(vertices1);
    Point2f point1=Point2f((vertices1[0].x+vertices1[3].x)/2,(vertices1[0].y+vertices1[3].y)/2);
    Point2f point2=Point2f((vertices1[1].x+vertices1[2].x)/2,(vertices1[1].y+vertices1[2].y)/2);
    lightInfo[1].points(vertices2);
    Point2f point4=Point2f((vertices2[0].x+vertices2[3].x)/2,(vertices2[0].y+vertices2[3].y)/2);
    Point2f point3=Point2f((vertices2[1].x+vertices2[2].x)/2,(vertices2[1].y+vertices2[2].y)/2);
    Point2f vertices[4]={point1,point2,point3,point4};
    for(int i=0;i<4;i++){
        line(frame,vertices[i],vertices[(i+1)%4],Scalar(0,0,255),2);
    }
    imshow("frame",frame);
    waitKey(0);
    destroyAllWindows();
    return 0;

}