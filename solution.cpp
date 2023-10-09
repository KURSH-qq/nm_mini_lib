#include "solution.h"

inline double mabs(double d) {
    if (d < 0) {
        return (-1) * d;
    }
    return d;
}

solution::solution(int _p,int _steps, double* _ic, double _h,
    double(*_f)(double, double),
    double(*_methood)(double(*)(double, double),
        double, double, double)) {
    h = _h;
    f = _f;
    p = _p;
    methood = _methood;
    steps = _steps;
    Xdata = new double[steps];
    Udata = new double[steps];
    ic[0] = _ic[0];
    ic[1] = _ic[1];
}

void solution::start() {
    Xdata[0] = ic[0];
    Udata[0] = ic[1];
    for (int i = 1; i < steps; i++) {
        Xdata[i] = Xdata[i - 1] + h;
        Udata[i] = methood(f, h, Xdata[i - 1], Udata[i - 1]);
    }
}

void solution::start_with_le() { // исправить лок погрешность
    double ue;
    double s;

    Xdata[0] = ic[0];
    Udata[0] = ic[1];
    for (int i = 1; i < steps; i++) {
        Xdata[i] = Xdata[i - 1] + h;
        Udata[i] = methood(f, h, Xdata[i - 1], Udata[i - 1]);

        ue = methood(f, h / 2, Xdata[i - 1], Udata[i - 1]);
        ue = methood(f, h / 2, Xdata[i - 1] + (h / 2), ue);
        s = (ue - Udata[i]) / ((2 ^ p) - 1);
        if (mabs(s) < (E / (2 ^ (p + 1)))) {
            h *= 2;
        }
        else if (mabs(s) > E) {
            h /= 2;
            Xdata[i] = Xdata[i - 1] + h;
            Udata[i] = methood(f, h, Xdata[i - 1], Udata[i - 1]);
        }

    }
}

void solution::print() {
    for (int i = 0; i < steps; i++) {
        std::cout << "i: " << i << " x: " << Xdata[i] << " u: " << Udata[i] << std::endl;
    }
}

solution::~solution() {
    delete[] ic;
    delete[] Xdata;
    delete[] Udata;
}