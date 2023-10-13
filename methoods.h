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