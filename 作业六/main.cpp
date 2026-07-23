#include <iostream>
#include <fstream>
#include "extended_kalman_filter/extended_kalman_filter.hpp"
#include <sstream>
using namespace std;
using namespace Eigen;
using namespace tools;
int main(){
    ifstream file("armor_data.csv");
    string line;
    bool isHeader=true;
    vector<vector<double>> data;
    while(getline(file,line)){
        if(isHeader){
            isHeader=false;
            continue;
        }
        stringstream ss(line);
        string temp;
        vector<double> temp_vec;
        while(getline(ss,temp,',')){
            temp_vec.push_back(stod(temp));
        }
        data.push_back(temp_vec);
    }
    file.close();
    double dt=1;
    MatrixXd F(8,8);
    F=MatrixXd::Identity(8,8);
    F(0,4)=dt;
    F(1,5)=dt;
    F(2,6)=dt;
    F(3,7)=dt;
    MatrixXd H(4,8);
    H(0,0)=1;
    H(1,1)=1;
    H(2,2)=1;
    H(3,3)=1;
    MatrixXd Q(8,8);
    Q.setZero();
    for(int i=0;i<4;i++){
        Q(i,i)=0.001;
    }
    for(int i=4;i<8;i++){
        Q(i,i)=0.01;
    }
    VectorXd x(8);;
    x.setZero();
    for(int i=0;i<4;i++){
        x(i)=data[0][i];
    }
    MatrixXd P(8, 8);
    P.setZero();    
    P(0, 0) = 10;   
    P(1, 1) = 10;   
    P(2, 2) = 10;   
    P(3, 3) = 10;   
    P(4, 4) = 1000; 
    P(5, 5) = 1000; 
    P(6, 6) = 1000; 
    P(7, 7) = 1000; 
    MatrixXd R(4, 4);
    for(int i=0;i<4;i++){
        R(i,i)=0.005;
    }
    ExtendedKalmanFilter kf(x,P);
    vector<VectorXd> filter_results;
    for(int i=0;i<data.size();i++){
        kf.predict(F,Q);
        VectorXd z(4);
        for(int j=0;j<data[i].size();j++){
            z(j)=data[i][j];
        }
        auto result=kf.update(z,H,R);
        filter_results.push_back(result);
    }
    ofstream outfile("filter_result.csv");
    outfile<<"estimate_x,estimate_y,estimate_z,estimate_Yaw"<<endl;
    for(int i=0;i<data.size();i++){
        for(int j=0;j<4;j++){
            outfile << filter_results[i](j);
            if(j<3)outfile<< ',';
        }
        outfile << endl;
    }
    outfile.close();




    

     

    
}