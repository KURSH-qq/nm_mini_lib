#pragma once

double em(double(*rp)(double, double), double h, double preX, double preU) {
    return preU + h * rp(preX, preU);
}
