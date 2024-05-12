#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

double firstFragm(double x){
    double res = -0.93 * x * x - 6.47 * x - 9.2;
    if (abs(res) < 0.000001) {
        res = 0.0;
    }
    return res;
}

double secondFragm(double x){
    double res = -sqrt(4 - x*x);
    if (abs(res) < 0.000001) {
        res = 0.0;
    }
    return res;
}

double thirdFragm(double x){
    double res = log2(x) - 1;
    if (abs(res) < 0.000001) {
        res = 0.0;
    }
    return res;
}

double fourthFragm(double x){
    double res = -2 * x + 18;
    if (abs(res) < 0.000001) {
        res = 0.0;
    }
    return res;
}

int main () {
    double xStart = -6.0;
    double xEnd = 9.0;
    double dx = 0.5;

    ofstream outfile("Output.txt");
    if (!outfile.is_open()) {
        cout << "Error!" << endl;
        return 1;
    }

    for (double x = xStart; x <= xEnd ; x += dx){
        if (abs(x) < 0.000001) {
        x = 0.0;
        }
        if (x >= -6.0 && x < -2.0) {
            outfile << setw(10)  << x << setw(10) << firstFragm(x) << endl;
        }
        if (x >= -2.0 && x < 2.0){
            outfile << setw(10)  << x << setw(10) << secondFragm(x) << endl;
        }
        if (x >= 2.0 && x < 8.0){
            outfile << setw(10)  << x << setw(10) << thirdFragm(x) << endl;
        }
        if (x >= 8.0 && x <= 9.0){
            outfile << setw(10)  << x << setw(10) << fourthFragm(x) << endl;
        }
    }
}