#include <iostream>
#include <cmath>
using namespace std;
int main(){
    double z_real=0.25;
    double z_temp=0.25;
    double z_error=1;
    while(abs(z_error)>=0.00001){
        double sin=z_temp/sqrt(pow(z_temp,2)+25);
        double cos=5/sqrt(pow(z_temp,2)+25);
        double t=(exp(0.0089*5)-1)/(0.0089*17*(cos));
        double z_actual=17*(sin)*t-0.5*10*pow(t,2);
        z_error=z_real-z_actual;
        z_temp=z_temp+z_error;
        cout << z_temp << endl;
    }
}
    