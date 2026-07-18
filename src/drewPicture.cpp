#include "drewPicture.hpp"

void drewPicture(Mat& frame, const Mat& rvec, const Mat& tvec, bool show_euler) {
    double x = tvec.at<double>(0);
    double y = tvec.at<double>(1);
    double z = tvec.at<double>(2);
    
    double yaw = 0, pitch = 0, roll = 0;
    if (show_euler && !rvec.empty()) {
        Mat R;
        Rodrigues(rvec, R);
        pitch = atan2(-R.at<double>(2,0), 
                      sqrt(R.at<double>(0,0)*R.at<double>(0,0) + 
                           R.at<double>(1,0)*R.at<double>(1,0)));
        yaw = atan2(R.at<double>(1,0), R.at<double>(0,0));
        roll = atan2(R.at<double>(2,1), R.at<double>(2,2));
        yaw = yaw * 180.0 / CV_PI;
        pitch = pitch * 180.0 / CV_PI;
        roll = roll * 180.0 / CV_PI;
    }
    
    vector<string> lines;
    stringstream ss;
    ss << fixed << setprecision(1);
    
    ss.str(""); ss.clear();
    ss << "Position (mm)";
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  X: " << x;
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  Y: " << y;
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  Z: " << z;
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "Angle (deg)";
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  Yaw: " << yaw;
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  Pitch: " << pitch;
    lines.push_back(ss.str());
    
    ss.str(""); ss.clear();
    ss << "  Roll: " << roll;
    lines.push_back(ss.str());
    
    int font_face = FONT_HERSHEY_SIMPLEX;
    double font_scale = 0.6;
    int thickness = 2;
    int line_spacing = 30;
    int margin = 20;
    
    int max_width = 0;
    int total_height = 0;
    for (const string& line : lines) {
        int baseline = 0;
        Size text_size = getTextSize(line, font_face, font_scale, thickness, &baseline);
        if (text_size.width > max_width) max_width = text_size.width;
        total_height += line_spacing;
    }
    
    Point start_point(frame.cols - max_width - margin - 10, margin + 20);
    
    rectangle(frame,
        Point(start_point.x - 10, start_point.y - 10),
        Point(start_point.x + max_width + 20, start_point.y + total_height + 10),
        Scalar(0, 0, 0), FILLED);
    rectangle(frame,
        Point(start_point.x - 10, start_point.y - 10),
        Point(start_point.x + max_width + 20, start_point.y + total_height + 10),
        Scalar(0, 255, 0), 1);
    
    for (size_t i = 0; i < lines.size(); i++) {
        Point text_origin(start_point.x, start_point.y + i * line_spacing);
        Scalar color;
        if (lines[i].find("Position") != string::npos || 
            lines[i].find("Angle") != string::npos) {
            color = Scalar(0, 255, 255);
        } else {
            color = Scalar(255, 255, 255);
        }
        putText(frame, lines[i], text_origin, font_face, font_scale, color, thickness, LINE_AA);
    }
}