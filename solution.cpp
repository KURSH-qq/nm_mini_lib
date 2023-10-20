#include "solution.h"


inline double mabs(double d) {
    if (d < 0) {
        return (-1) * d;
    }
    else if (d >= 0) {
        return d;
    }
}

/*
inline double pow(double d, int p) {
    double result = d;
    for (int i = 0; i < p; i++) {
        result *= result;
    }
    return result;
}*/


inline double max(double d1, double d2) {
    if (d1 > d2) {
        return d1;
    }
    return d2;
}

inline double max(const std::vector<double> v) {
    double result = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > result) {
            result = v[i];
        }
    }
    return result;
}

inline double min(const std::vector<double> v) {
    double result = LONG_MAX;
    for (int i = 0; i < v.size(); i++) {
        if ((v[i] < result) && v[i] != 0) {
            result = v[i];
        }
    }
    return result;
}

inline double maxabs(const std::vector<double> v) {
    double result = 0;
    for (int i = 0; i < v.size(); i++) {
        if (mabs(v[i]) > result) {
            result = v[i];
        }
    }
    return result;
}

inline int find(const std::vector<double> v, double d) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == d) {
            return i;
        }
    }
    return -1;
}



DEsolution::DEsolution(unsigned int mod, double _E, int _p, int _steps, double _Xr,
    const std::vector<double>& _ic, double _h,
    double(*_f)(double, double),
    double(*_methood)(double(*)(double, double),
        double, double, double), double(*_solved_du)(double, std::vector<double>)) {
    
    h = _h;
    f = _f;
    p = _p;
    E = _E;
    Xr = _Xr;
    mod_choice = mod;
    methood = _methood;
    steps = _steps;
    solved_du = _solved_du;
    ic = _ic;
    
    start();  
    
    make_table();   
}

void DEsolution::start() {
    
    Xdata.push_back(ic[0]);
    V1data.push_back(ic[1]);
    V2data.push_back(0);
    Udata.push_back(ic[1]);
    Olp.push_back(0);
    I.push_back(0);
    Dub.push_back(0);
    Div.push_back(0);
    Step.push_back(0);
    
    int i = 1;
    real_steps = 1;
    if (mod_choice == 0) {
        
        while (i < steps) {
            if (Xdata[i - 1] + h + E < Xr) {
                real_steps += 1;
                I.push_back(i);
                Xdata.push_back(Xdata[i - 1] + h);
                V1data.push_back(methood(f, h, Xdata[i - 1], V1data[i - 1]));
                Dub.push_back(0);
                Div.push_back(0);
                Step.push_back(h);
                Olp.push_back(0);
                V2data.push_back(0);
                if (solved_du != nullptr) {
                    Udata.push_back(solved_du(Xdata[i - 1] + h, ic));
                }
                else {
                    Udata.push_back(0);
                }               
                i++;
            }
            else {
                break;
            }
        }
    }

    else if (mod_choice == 1) {
        
        while (i < steps) {
            if (Xdata[i - 1] + h + E < Xr) {
                real_steps += 1;
                I.push_back(i);
                Xdata.push_back(Xdata[i - 1] + h);
                V1data.push_back(methood(f, h, Xdata[i - 1], V1data[i - 1]));
                
                lee(i);
                
                Dub.push_back(dublecate_count);
                Div.push_back(div_count);
                if (solved_du != nullptr) {
                    Udata.push_back(solved_du(Xdata[i - 1] + h, ic));
                }
                else {
                    Udata.push_back(0);
                }
                
                i++;
                
            }
            else {
                break;
            }
        }
        
    }
    
}

void DEsolution::lee(int step) {
    int i = step;
    double ue;
    double s;
    ue = methood(f, h / 2, Xdata[i - 1], V1data[i - 1]);
    ue = methood(f, h / 2, Xdata[i - 1] + (h / 2), ue);
    s = (ue - V1data[i]) / (pow(2, p) - 1);
    if (mabs(s) < (E / (pow(2, p + 1)))) {
        h *= 2;
        dublecate_count += 1;
    }
    while (mabs(s) > E) {
        h /= 2;
        div_count += 1;
        Xdata[i] = Xdata[i - 1] + h;
        V1data[i] = methood(f, h, Xdata[i - 1], V1data[i - 1]);
        ue = methood(f, h / 2, Xdata[i - 1], V1data[i - 1]);
        ue = methood(f, h / 2, Xdata[i - 1] + (h / 2), ue);
        s = (ue - V1data[i]) / (pow(2, p) - 1);

    }

    V2data.push_back(ue);
    Step.push_back(h);
    Olp.push_back(s);
}


void DEsolution::make_table() {
    
    for (int i = 0; i < real_steps; i++) {
        Subv.push_back(V1data[i] - V2data[i]);  
        if (solved_du != nullptr) {
            Subuv.push_back(mabs(Udata[i] - V1data[i]));
        }
        else {
            Subuv.push_back(0);
        }
    }   
    table.clear();
    table.push_back(I);
    table.push_back(Xdata);
    table.push_back(V1data);
    table.push_back(V2data);
    table.push_back(Subv);
    table.push_back(Olp);
    table.push_back(Step);
    table.push_back(Div);
    table.push_back(Dub);
    table.push_back(Udata);
    table.push_back(Subuv);  
}

void DEsolution::print_results() {
    std::cout << "max n = " << I.back() << std::endl;
    std::cout << "b - xn = " << Xr - Xdata.back() << std::endl;
    std::cout << "max|OLP| = " << maxabs(Olp) << std::endl;
    std::cout << "dublicates: " << dublecate_count << std::endl;
    std::cout << "divs: " << div_count << std::endl;
    std::cout << "max h: " << max(Step) << " x: " << Xdata[find(Step,max(Step))] << std::endl;
    std::cout << "min h: " << min(Step) << " x: " << Xdata[find(Step, min(Step))] <<std::endl;
    std::cout << "max |u-v|: " << maxabs(Subuv) << " x: " << Xdata[find(Subuv, maxabs(Subuv))] << std::endl;
}

std::vector<std::vector<double>> DEsolution::get_table() {
    return table;
}

std::vector<std::vector<double>> DEsolution::get_UX() {
    std::vector<std::vector<double>> result;
    result.push_back(Xdata);
    result.push_back(Udata);
    return result;
}

void DEsolution::print_table() { 

    for (int i = 0; i < real_steps; i++) {
        for (int j = 0; j < table.size(); j++) {
            std::cout << table[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>> DEsolution::get_VX() {
    std::vector<std::vector<double>> result;
    result.push_back(Xdata);
    result.push_back(V1data);
    return result;
}

void DEsolution::set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
    const std::vector<double>& _ic) {
    Xdata.clear();
    Udata.clear();
    V1data.clear();
    V2data.clear();
    I.clear();
    Subv.clear();
    Div.clear();
    Dub.clear();
    Subuv.clear();
    Olp.clear();
    Step.clear();
    mod_choice = _mod;
    E = _E;
    steps = _steps;
    Xr = _Xr;
    h = _h;
    ic = _ic;
    dublecate_count = 0;
    div_count = 0;
    start();
    make_table();
}

void DEsolution::set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h, double _ic1, double _ic2) {
    Xdata.clear();
    Udata.clear();
    V1data.clear();
    V2data.clear();
    I.clear();
    Subv.clear();
    Div.clear();
    Dub.clear();
    Subuv.clear();
    Olp.clear();
    Step.clear();
    mod_choice = _mod;
    E = _E;
    steps = _steps;
    Xr = _Xr;
    h = _h;
    ic[0] = _ic1;
    ic[1] = _ic2;
    dublecate_count = 0;
    div_count = 0;
    start();
    make_table();
}

std::vector<std::string> DEsolution::get_names() {
    return names;
}

SDEsolution::SDEsolution(unsigned int mod, double _E, int _p, int _steps, double _Xr,
    const std::vector<double>& _ic,
    double _h, double(*_f1)(double, double, double,double,double), double(*_f2)(double, double, double,double,double),
    std::vector<double>(*_methood)(double(*)(double, double,double,double,double), double(*)(double, double, double, double, double),
        double,double, double, double, double,double),
    double _p1, double _p2) {

    mod_chice = mod;
    E = _E;
    p = _p;
    steps = _steps;
    f1 = _f1;
    f2 = _f2;
    h = _h;
    methood = _methood;
    ic = _ic;
    Xr = _Xr;
    p1 = _p1;
    p2 = _p2;
    start();  
    make_table();

}
void SDEsolution::start() {

    Xdata.push_back(ic[0]);
    V1data.push_back(ic[1]);
    V2data.push_back(ic[2]);
    I.push_back(0);
    Olp.push_back(0);
    Div.push_back(0);
    Dub.push_back(0);
    Ue1data.push_back(0);
    Ue2data.push_back(0);
    Step.push_back(0);
    std::vector<double> cur_data;
    real_steps = 1;
    int i = 1;
    
    if (mod_chice == 0) {
        while (i < steps) {           
            cur_data.clear();
            if (Xdata[i - 1] + h + E < Xr) {
                real_steps += 1;
                I.push_back(i);              
                cur_data = methood(f1, f2, h, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
                V1data.push_back(cur_data[0]);
                V2data.push_back(cur_data[1]);
                Xdata.push_back(Xdata[i - 1] + h);
                Div.push_back(0);
                Dub.push_back(0);
                Step.push_back(h);
                Olp.push_back(0);
                Ue1data.push_back(0);
                Ue2data.push_back(0);
                i++;
            }
            else {
                break;
            }
        }
    }
    else if (mod_chice == 1) {
        while (i < steps) {           
            cur_data.clear();        
            if ((Xdata[i - 1] + h + E < Xr && Xr>0) || (Xdata[i-1]+h-E>Xr && Xr<0)) { 
                real_steps += 1;               
                I.push_back(i);               
                cur_data = methood(f1, f2, h, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
                V1data.push_back(cur_data[0]);
                V2data.push_back(cur_data[1]);
                Xdata.push_back(Xdata[i - 1] + h);
                lee(i);
                Div.push_back(div_count);
                Dub.push_back(dublicate_count);
                i++;
            }
            else {
                break;
            }
        }
    }
}


void SDEsolution::lee(int step) {
    int i = step;
    double s;
    std::vector<double> cur_data1,cur_data, cur_data2;
    cur_data1 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
    cur_data1 = methood(f1, f2, h / 2, Xdata[i - 1] + h / 2, cur_data1[0], V2data[i - 1], p1, p2);
    cur_data2 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
    cur_data2 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], cur_data2[1], p1, p2);
    s = max(mabs((cur_data2[1] - V2data[i]) / (pow(2, p) - 1)), mabs((cur_data1[0] - V1data[i]) / (pow(2, p) - 1)));
    if (mabs(s) < (E / (pow(2, p + 1)))) {
        h *= 2;
        dublicate_count += 1;
    }
    while (mabs(s) > E) {
        if ((Xdata[i - 1] + h / 2 + E < Xr && Xr>0) || (Xdata[i - 1] + h / 2 - E > Xr && Xr < 0)) {
            h /= 2;
            div_count += 1;
            Xdata[i] = Xdata[i - 1] + h;
            cur_data = methood(f1, f2, h, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
            V1data[i] = cur_data[0];
            V2data[i] = cur_data[1];
            cur_data1 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
            cur_data1 = methood(f1, f2, h / 2, Xdata[i - 1] + h / 2, cur_data1[0], V2data[i - 1], p1, p2);
            cur_data2 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], V2data[i - 1], p1, p2);
            cur_data2 = methood(f1, f2, h / 2, Xdata[i - 1], V1data[i - 1], cur_data2[1], p1, p2);
            s = max(mabs((cur_data2[1] - V2data[i]) / (pow(2, p) - 1)), mabs((cur_data1[0] - V1data[i]) / (pow(2, p) - 1)));
        }
        else {
            break;
        }
    }
    Ue1data.push_back(cur_data1[0]);
    Ue2data.push_back(cur_data2[1]);
    Olp.push_back(s);
    Step.push_back(h);
}


void SDEsolution::make_table() {
    
    for (int i = 0; i < real_steps; i++) {
        Subv1.push_back(mabs(V1data[i] - Ue1data[i]));
        Subv2.push_back(mabs(V2data[i] - Ue2data[i])); 
    }
    Subv1[0] = 0;
    Subv2[0] = 0;
    
    table.clear();
    table.push_back(I);
    table.push_back(Xdata);
    table.push_back(V1data);
    table.push_back(V2data);
    table.push_back(Ue1data);
    table.push_back(Ue2data);
    table.push_back(Subv1);
    table.push_back(Subv2);
    table.push_back(Olp);
    table.push_back(Step);
    table.push_back(Div);
    table.push_back(Dub);
    
}

std::vector<std::vector<double>> SDEsolution::get_table() {
    return table;
}


void SDEsolution::print_table() { 
    for (int i = 0; i < real_steps; i++) {      
        for (int j = 0; j < table.size(); j++) {
            std::cout << table[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

void SDEsolution::print_results() {
    std::cout << "max n = " << I.back() << std::endl;
    std::cout << "b - xn = " << Xr - Xdata.back() << std::endl;
    std::cout << "max|OLP| = " << maxabs(Olp) << std::endl;
    std::cout << "dublicates: " << dublicate_count << std::endl;
    std::cout << "divs: " << div_count << std::endl;
    std::cout << "max h: " << max(Step) << " x: " << Xdata[find(Step, max(Step))] << std::endl;
    std::cout << "min h: " << min(Step) << " x: " << Xdata[find(Step, min(Step))] << std::endl;
    std::cout << "max |v1-v1^|: " << maxabs(Subv1) << " x: " << Xdata[find(Subv1, maxabs(Subv1))] << std::endl; 
    std::cout << "max |v2-v2^|: " << maxabs(Subv2) << " x: " << Xdata[find(Subv2, maxabs(Subv2))] << std::endl;
}

std::vector<std::vector<double>> SDEsolution::get_VX() {
    std::vector<std::vector<double>> result;
    result.push_back(Xdata);
    result.push_back(V1data);
    return result;
}

std::vector<std::vector<double>> SDEsolution::get_VdotV() {
    std::vector<std::vector<double>> result;
    result.push_back(V1data);
    result.push_back(V2data);
    return result;
}

void SDEsolution::set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
    const std::vector<double>& _ic, double _p1, double _p2) {
    Xdata.clear();
    V1data.clear();
    V2data.clear();
    Subv1.clear();
    Subv2.clear();
    Ue1data.clear();
    Ue2data.clear();
    Olp.clear();
    I.clear();
    Step.clear();
    Dub.clear();
    Div.clear();
    mod_chice = _mod;
    E = _E;
    steps = _steps;
    Xr = _Xr;
    h = _h;
    ic = _ic;
    p1 = _p1;
    p2 = _p2;
    dublicate_count = 0;
    div_count = 0;
    start();
    make_table();
}

void SDEsolution::set_params(unsigned int _mod, double _E, int _steps, double _Xr, double _h,
    double _ic1, double _ic2, double _ic3, double _p1, double _p2) {
    Xdata.clear();
    V1data.clear();
    V2data.clear();
    Subv1.clear();
    Subv2.clear();
    Ue1data.clear();
    Ue2data.clear();
    Olp.clear();
    I.clear();
    Step.clear();
    Dub.clear();
    Div.clear();
    mod_chice = _mod;
    E = _E;
    steps = _steps;
    Xr = _Xr;
    h = _h;
    dublicate_count = 0;
    div_count = 0;
    ic[0] = _ic1;
    ic[1] = _ic2;
    ic[2] = _ic3;
    p1 = _p1;
    p2 = _p2;
    start();
    make_table();
}

std::vector<std::string> SDEsolution::get_names() {
    return names;
}
