#pragma once
#include <iostream>

inline double mabs(double d);

class solution {
private:

    double(*f)(double, double);
    double(*methood)(double(*)(double, double), double, double, double);
    double h;
    double* ic = new double[2];
    double* Xdata;
    double* Udata;
    int steps;
    double E = 10 ^ (-7);
    int p;

public:
    solution(int _p,int _steps, double* _ic, double _h,
        double(*_f)(double, double),
        double(*_methood)(double(*)(double, double),
            double, double, double));
    void start();
    void start_with_le();
    void print();
    ~solution();
};