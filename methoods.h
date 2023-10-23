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

double rk4(double(*rp)(double, double), double h, double preX, double preV1) {
    double k1, k2, k3, k4;
    k1 = rp(preX, preV1);
    k2 = rp(preX + 0.5 * h, preV1 + 0.5 * h * k1);
    k3 = rp(preX + 0.5 * h, preV1 + 0.5 * h * k2);
    k4 = rp(preX + h, preV1 +  h * k3);
    return preV1 +   ((k1 + 2 * k2 + 2 * k3 + k4)/6)* h;
}

std::vector<double> rk2(double(*f1)(double, double, double, double, double), double(*f2)(double, double, double, double, double),
    double h, double preX, double preV1, double preV2, double p1, double p2) {
    std::vector<double> result;
    double d1, d2;
    d1 = f1(preX, preV1, preV2, p1, p2);
    d2 = f2(preX, preV1, preV2, p1, p2);
    result.push_back(preV1 + 0.5 * h * (d1 + f1(preX + h, preV1 + h * d1, preV2 + h * d2, p1, p2)));
    result.push_back(preV2 + 0.5 * h * (d2 + f2(preX + h, preV1 + h * d1, preV2 + h * d2, p1, p2)));
    return result;
}

std::vector<double> rk4(double(*f1)(double, double, double, double, double), double(*f2)(double, double, double, double, double),
    double h, double preX, double preV1, double preV2, double p1, double p2) {
    double k11, k12, k21, k22, k13, k23, k14, k24;
    std::vector<double> result;
    k11 = f1(preX, preV1, preV2, p1, p2);
    k21 = f2(preX, preV1, preV2, p1, p2);

    k12 = f1(preX + 0.5 * h, preV1 + 0.5 * h * k11, preV2 + 0.5 * h * k21, p1, p2);
    k22 = f2(preX + 0.5 * h, preV1 + 0.5 * h * k11, preV2 + 0.5 * h * k21, p1, p2);

    k13 = f1(preX + 0.5 * h, preV1 + 0.5 * h * k12, preV2 + 0.5 * h * k22, p1, p2);
    k23 = f2(preX + 0.5 * h, preV1 + 0.5 * h * k12, preV2 + 0.5 * h * k22, p1, p2);

    k14 = f1(preX + h, preV1 + h * k13, preV2 + k23 * h, p1, p2);
    k24 = f2(preX + h, preV1 + h * k13, preV2 + k23 * h, p1, p2);
    result.push_back(preV1 + ((k11 + 2 * k12 + 2 * k13 + k14) / 6) * h);
    result.push_back(preV2 + ((k21 + 2 * k22 + 2 * k23 + k24) / 6) * h);
    return result;
}