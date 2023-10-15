#pragma once

double em(double(*f1)(double, double,double,double,double), double(*f2)(double, double, double, double, double),
    double h, double preX, double preV1, double preV2,double p1,double p2) {
    return preV1 + h * f1(preX, preV1, preV2, p1, p2);
}

double em(double(*rp)(double, double), double h, double preX, double preV) {
    return preV + h * rp(preX, preV);
}

                                                                           
double rk2(double(*rp)(double, double), double h, double preX, double preV1) {
    return preV1 + 0.5 * h * (rp(preX,preV1)+rp(preX+h,preV1+h*rp(preX,preV1)));
}

double rk2(double(*f1)(double, double, double, double, double), double(*f2)(double, double, double, double, double),
    double h, double preX, double preV1, double preV2, double p1, double p2) {
    double f = f1(preX, preV1, preV2, p1, p2);
    return preV1 + 0.5 * h * (f+ f1(preX+h,preV1+h*f,preV2+h*f2(preX,preV1,preV2,p1,p2),p1,p2));
}

double rk4(double(*f1)(double, double, double, double, double), double(*f2)(double, double, double, double, double),
    double h, double preX, double preV1, double preV2, double p1, double p2) {
    double k11, k12, k13, k14;
    double k21, k22, k23, k24;
    k11 = f1(preX, preV1, preV2, p1, p2);
    k21 = f2(preX, preV1, preV2, p1, p2);
    k12 = f1(preX + 0.5 * h, preV1 + 0.5 * h * k11, preV2 + 0.5 * k21,p1,p2);
    k22 = f2(preX + 0.5 * h, preV1 + 0.5 * h * k11, preV2 + 0.5 * k21, p1, p2);
    k13 = f1(preX + 0.5 * h, preV1 + 0.5 * h * k12, preV2 + 0.5 * k22, p1, p2);
    k23 = f2(preX + 0.5 * h, preV1 + 0.5 * h * k12, preV2 + 0.5 * k22, p1, p2);
    k14 = f1(preX + h, preV1 + h * k13, preV2 +  k23, p1, p2);
    k24 = f2(preX + h, preV1 + h * k13, preV2 + k23, p1, p2);
    return preV1 + (1/6)*h * (k11 + 2 * k12 + 2 * k13 + k14);
}