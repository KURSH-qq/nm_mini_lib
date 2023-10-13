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

int main() {
    std::vector<double> ic = { 0,4,1 };
    double h = 0.001;
    double E = 0.0001;
    //DEsolution sol1(1, E, 2, 200, 30, ic, h, f3, rk2);
    SDEsolution sol2(1, E, 2, 10, 10, ic, h, f1, f2, rk2, 1, 1);
    sol2.print_table();
    sol2.print_results();
    sol2.set_params(1, E, 11, 31, 0.001, 0, 4,1,1,1);
    sol2.print_table();
    sol2.print_results();
    //std::cout << sol2.get_table().size() << std::endl;
    //std::cout << sol2.get_table()[0].size() << std::endl;
    //std::cout << sol2.get_names().size() << std::endl;
    //std::cout << sol1.get_table()[0][20] << std:: endl;
}