#include <iostream>
#include "solution.h"
#include "methoods.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>



double right_part(double x = 0, double u = 0) {
    return -2.5 * u;
}

double rp1(double x = 0, double u = 0) {
    return 1 / u;
}

double sd(double x, std::vector<double> ic) { 
    
    return ic[1] * exp(-2.5 * (x - ic[0]));
}

double f1(double x = 0, double v1 = 0, double v2 = 0, double p1 = 0, double p2 = 0) {
    return v2;
}

double f2(double x = 0, double v2 = 0 ,double v1 = 0,double p1 = 0, double p2 = 0) {
    return p1*v2 * v2 + p2*sin(v1);
}

double f3(double x = 0, double u = 0) {
    double f = (log(x+1)) / (x*x+1);
    return f * u * u + u - u * u * u * sin(10*x);
}





/*
std::vector<double> ic;
std::vector<double> test;
ic.push_back(0);
ic.push_back(4);
test = ic;
test.push_back(1);
double h = 0.001;
double E = 0.001;

SDEsolution sol2( 1, E, 2, 10,10, test, h, f1, f2, rk2,1,1);
//DEsolution sol1(1,E,2, 200, 30 , ic, h, right_part, em, sd);
//DEsolution sol1(0, E, 2, 200, 30, ic, h, right_part, rk2); */

int main() {
    std::vector<double> ic = { 0,4 };
    double h = 0.001;
    double E = 0.0001;
    DEsolution sol1(1, E, 2, 200, 30, ic, h, f3, rk2);
    sol1.print_table();
    sol1.print_results();
}