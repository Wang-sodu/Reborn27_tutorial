#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<double> estimate={30000};
    vector<double> predict;
    vector<double> v_estimate={40};
    vector<double> v_predict;
    vector<double> measure={30171,30353,30756,30799,31018,31278,31276,31379,31748,32175};
    for(int i=0;i<measure.size();i++){
        double temp=estimate[i]+v_estimate[i]*5;
        predict.push_back(temp);
        v_predict.push_back(v_estimate[i]);
        temp=predict[i]+0.1*(measure[i]-predict[i]);
        estimate.push_back(temp);
        temp=v_predict[i]+0.2*(measure[i]-predict[i])/5;
        v_estimate.push_back(temp);
    }
    for(int i=0;i<estimate.size();i++){
        cout << estimate[i] << " ";
    }

}