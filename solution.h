#pragma once
#include <iostream>
#include <vector>
#include <sstream>

inline double mabs(double d);
inline double max(double d1, double d2);
inline double max(const std::vector<double> v);
inline double min(const std::vector<double> v);
inline double maxabs(const std::vector<double> v);
inline int find(const std::vector<double> v, double d);

class DEsolution {
private:

    double(*f)(double, double,double,double);
    double(*methood)(double(*)(double, double,double,double), double, double, double,double,double);
    double(*solved_du)(double, std::vector<double>);
    double h;
    double p1, p2;

    std::vector<double> ic;
    std::vector<double> Xdata; 
    std::vector<double> V1data; 
    std::vector<double> I; 
    std::vector<double> V2data;
    std::vector<double> Subv;
    std::vector<double> Olp; 
    std::vector<double> Step;
    std::vector<double> Div; 
    std::vector<double> Dub; 
    std::vector<double> Udata;
    std::vector<double> Subuv;

    int steps;
    double E;
    int p;
    int mod_choice = 0;
    std::vector<std::vector<double>> table;
    unsigned int dublecate_count = 0;
    unsigned int div_count  = 0;
    double Xr;
    int real_steps = 0;
    std::vector<std::string> names = { "I" ,"X","V", "V^", "SUBV","OLP",
        "H", "DIV", "DUB","U","SUBUV" };

    void start();
    void lee(int step);
    void make_table();

public:
    
    const enum result {
        N = 0,
        X = 1,
        V1 = 2,
        V2 = 3,
        SUBV = 4,
        OLP = 5,
        H = 6,
        DIV = 7,
        DUB = 8,
        U = 9,
        SUBUV = 10
    };

    DEsolution(unsigned int mod, double _E,int _p,int _steps, double _Xr,
        const std::vector<double>& _ic, double _h,
        double(*_f)(double, double,double,double),
        double(*_methood)(double(*)(double, double,double,double),double, double, double,double,double), double _p1 = 0, double _p2 = 0,
        double(* _solved_du)(double,std::vector<double>) = nullptr);


    void print_table();
    void print_results();
    std::vector<std::vector<double>> get_VX();
    std::vector<std::vector<double>> get_UX();
    std::vector<std::vector<double>> get_table();

    std::vector<std::string> get_names();
    void set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
        const std::vector<double>& _ic, double _p1, double _p2);
    void set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h, double _ic1, double _ic2, double _p1, double _p2);
    std::string get_results();
};



class SDEsolution {
private:
    double(*f1)(double, double, double, double, double);
    double(*f2)(double, double, double,double,double);
    std::vector<double>(*methood)(double(*)(double, double,double,double,double), double(*)(double, double, double, double, double),
        double, double, double, double,double,double);
    double h;

    std::vector<double> ic;
    std::vector<double> Xdata;
    std::vector<double> V1data;
    std::vector<double> V2data;
    std::vector<double> Subv1;
    std::vector<double> Subv2;
    std::vector<double> Ue1data;
    std::vector<double> Ue2data;
    std::vector<double> Olp;
    std::vector<double> I;
    std::vector<double> Step;
    std::vector<double> Dub;
    std::vector<double> Div;

    int steps;
    unsigned int dublicate_count = 0;
    unsigned int div_count = 0;
    int mod_choice;
    double E;
    int p;
    int real_steps = 0;
    unsigned int mod_chice;
    std::vector<std::vector<double>> table;
    double Xr;
    double p1, p2;
    std::vector<std::string> names = { "I","X","V1","V2","V1^","V2^",
        "SUBV1","SUBV2","OLP","H","DIV","DUB" };

    void start();
    void lee(int step);
    void make_table();

public:
    const enum result {
        N = 0,
        X = 1,
        V1 = 2,
        V2 = 3,
        UE1 = 4,
        UE2 = 5,
        SUBV1 = 6,
        SUBV2 = 7,
        OLP = 8,
        H = 9,
        DIV = 10,
        DUB = 11
    };

    SDEsolution(unsigned int mod, double _E, int _p, int _steps, double _Xr, const std::vector<double>& _ic,
        double _h, double(*_f1)(double, double, double,double,double), double(*_f2)(double, double, double,double,double),
        std::vector<double>(*_methood)(double(*)(double, double, double,double,double), double(*)(double, double, double, double, double),
            double,double,double, double, double, double),
        double _p1 =0, double _p2 =0);


    void print_table();
    void print_results();
    std::vector<std::vector<double>> get_VX();
    std::vector<std::vector<double>> get_VdotV();
    std::vector<std::vector<double>> get_table();

    std::vector<std::string> get_names();

    void set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
        const std::vector<double>& _ic, double p1, double p2);
    void set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
        double _ic1, double _ic2, double _ic3, double _p1, double _p2);
    std::string get_results();
};


class SSDEsolution {
private:
public:
};