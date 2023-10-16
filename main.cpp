#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "solution.h"
#include "methoods.h"
#include "graphics.h"



double right_part(double x = 0, double u = 0) { // func 1
    return -2.5 * u;
}

double sd(double x, std::vector<double> ic) {

    return ic[1] * exp(-2.5 * (x - ic[0]));
}

double f1(double x = 0, double v1 = 0, double v2 = 0, double p1 = 0, double p2 = 0) { // func sdu(1)
    return v2;
}

double f2(double x = 0, double v2 = 0, double v1 = 0, double p1 = 0, double p2 = 0) {// func sdu(2)
    return p1 * v2 * v2 + p2 * sin(v1);
}

double f3(double x = 0, double u = 0) { // func 2
    double f = (log(x + 1)) / (x * x + 1);
    return f * u * u + u - u * u * u * sin(10 * x);
}


std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> vector)
{
    std::vector<std::vector<double>> vector_t;

    std::vector<double> row;

    for (size_t i = 0; i < vector[0].size(); i++)
    {
        row.clear();
        row.push_back(i);
        for (size_t j = 1; j < vector.size(); j++)
        {
            row.push_back(vector[j][i]);
        }
        vector_t.push_back(row);
    }
    return vector_t;
}




const double p1 = 1, p2 = 1;


int main()
{
    std::vector<double> ic = { 0,-1,1 };
    DEsolution sol1(1, 0.0001, 4, 200, 30, ic, 0.001, right_part, rk4, sd);
    DEsolution sol2(1, 0.0001, 4, 200, 30, ic, 0.001, f3, rk4);

    std::vector<double> ic2 = { 0,4, 1 };
    SDEsolution sol3(1, 0.0001, 2, 200, 30, ic2, -0.001, f1, f2, rk2, 1, 1);




    sf::RenderWindow window({ 1200, 500 }, "SFML", sf::Style::Close);
    Button f1, f2, f3;

    Table table;
    TextField E, h1, Xr, v, x, v_1, steps;
    Button button_calc, button_gr_vx, button_gr_v2v;
    boolField b1;

    bool ready = false;


    E.setPosition(30, 70);
    E.setName(sf::String(L"E"));

    sf::Vector2f pos = E.getPosition();
    pos.x += E.getSize().x + 15;
    h1.setPosition(pos);
    h1.setName(sf::String(L"h"));


    pos = h1.getPosition();
    pos.x += h1.getSize().x + 15;
    Xr.setPosition(pos);
    Xr.setName(sf::String(L"X_r"));

    pos = Xr.getPosition();
    pos.x += Xr.getSize().x + 15;
    steps.setPosition(pos);
    steps.setName(sf::String(L"steps"));

    pos = E.getPosition();
    pos.y += E.getSize().y + 25;
    x.setPosition(pos);
    x.setName("x");


    pos = x.getPosition();
    pos.x += x.getSize().x + 15;
    v.setName("v");
    v.setPosition(pos);

    pos = v.getPosition();
    pos.x += v.getSize().x + 15;
    v_1.setName("v_1");
    v_1.setPosition(pos);


    pos = x.getPosition();
    pos.y += x.getSize().y + 25;
    b1.setPosition(pos);
    b1.setName("step control");


    pos.y -= 10;
    pos.x += v.getSize().x + 15;
    button_calc.setName("calculate");
    button_calc.setPosition(pos);

    pos = button_calc.getPosition();
    pos.x += button_calc.getSize().x + 15;
    button_gr_vx.setName("show graph v(x)");
    button_gr_vx.setPosition(pos);


    pos = button_gr_vx.getPosition();
    pos.x += button_gr_vx.getSize().x + 15;
    button_gr_v2v.setName("show graph vdot(v)");
    button_gr_v2v.setPosition(pos);


    pos = b1.getPosition();
    pos.y += 25;
    table.setPosition(pos);
    table.setSize(sf::Vector2f(1000, 300));
    table.setRows(7);


    pos = sf::Vector2f(30, 15);
    f1.setPosition(pos);
    f1.setName("test");

    pos.x += f1.getSize().x + 15;
    f2.setPosition(pos);
    f2.setName("main 1");

    pos.x += f2.getSize().x + 15;
    f3.setPosition(pos);
    f3.setName("main 2");






    f1.tuch(true);

    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = sf::Mouse::getPosition(window);
                if (f1.contains(sf::Vector2f(pos))) {

                    f1.tuch(true);
                    f2.tuch(false);
                    f3.tuch(false);
                }
                if (f2.contains(sf::Vector2f(pos))) {
                    f1.tuch(false);
                    f2.tuch(true);
                    f3.tuch(false);
                }
                if (f3.contains(sf::Vector2f(pos))) {
                    f1.tuch(false);
                    f2.tuch(false);
                    f3.tuch(true);
                }
            }



            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = sf::Mouse::getPosition(window);
                if (button_calc.contains(sf::Vector2f(pos))) {
                    button_calc.tuch(true);
                    if ((f1.isReady() || f2.isReady()) && (E.isReady() + h1.isReady() + Xr.isReady() + v.isReady() + x.isReady() + steps.isReady()) == 6)
                    {
                        if (f1.isReady())
                        {
                            sol1.set_params(b1.isReady(), E.getValue(), steps.getValue(), Xr.getValue(), h1.getValue(), x.getValue(), v.getValue());
                            table.setNames(sol1.get_names());
                            table.setData(transpose(sol1.get_table()));
                        }
                        if (f2.isReady())
                        {
                            sol2.set_params(b1.isReady(), E.getValue(), steps.getValue(), Xr.getValue(), h1.getValue(), x.getValue(), v.getValue());
                            table.setNames(sol2.get_names());
                            table.setData(transpose(sol2.get_table()));
                        }
                        ready = true;
                    }
                    else if (f3.isReady() && (E.isReady() + h1.isReady() + Xr.isReady() + v.isReady() + x.isReady() + v_1.isReady() + steps.isReady()) == 7)
                    {
                        if (f3.isReady())
                        {
                            sol3.set_params(b1.isReady(), E.getValue(), steps.getValue(), Xr.getValue(), h1.getValue(), x.getValue(), v.getValue(), v_1.getValue(), p1, p2);
                            table.setNames(sol3.get_names());
                            table.setData(transpose(sol3.get_table()));
                        }
                        ready = true;
                    }
                    else
                        ready = false;
                }
                if (button_gr_vx.contains(sf::Vector2f(pos))) {
                    button_gr_vx.tuch(true);
                    if (f1.isReady())
                        graph(sol1.get_VX());
                    if (f2.isReady())
                        graph(sol2.get_VX());
                    if (f3.isReady())
                        graph(sol3.get_VX());
                }
                if (button_gr_v2v.contains(sf::Vector2f(pos))) {
                    button_gr_vx.tuch(true);
                    if (f3.isReady())
                        graph(sol3.get_VdotV());
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                button_calc.tuch(false);
                button_gr_vx.tuch(false);
                auto pos = sf::Mouse::getPosition(window);


                E.setFocus(false);
                h1.setFocus(false);
                Xr.setFocus(false);
                v.setFocus(false);
                v_1.setFocus(false);
                steps.setFocus(false);
                x.setFocus(false);
                table.setFocus(false);



                if (E.contains(sf::Vector2f(pos)))
                    E.setFocus(true);
                if (h1.contains(sf::Vector2f(pos)))
                    h1.setFocus(true);
                if (Xr.contains(sf::Vector2f(pos)))
                    Xr.setFocus(true);
                if (v.contains(sf::Vector2f(pos)))
                    v.setFocus(true);
                if (x.contains(sf::Vector2f(pos)))
                    x.setFocus(true);
                if (steps.contains(sf::Vector2f(pos)))
                    steps.setFocus(true);
                if (table.contains(sf::Vector2f(pos)))
                    table.setFocus(true);
                if (b1.contains(sf::Vector2f(pos)))
                    b1.tuch();
                if (f3.isReady() && v_1.contains(sf::Vector2f(pos)))
                    v_1.setFocus(true);



            }
            else {
                E.handleInput(event);
                h1.handleInput(event);
                Xr.handleInput(event);
                v.handleInput(event);
                steps.handleInput(event);
                x.handleInput(event);
                table.handleInput(event);
                v_1.handleInput(event);
            }

            window.clear(sf::Color::White);

            window.draw(f1);
            window.draw(f2);
            window.draw(f3);


            window.draw(b1);
            window.draw(E);
            window.draw(h1);
            window.draw(Xr);
            window.draw(v);
            window.draw(x);
            window.draw(steps);
            window.draw(button_calc);

            if (ready)
            {
                window.draw(table);
                window.draw(button_gr_vx);
            }

            if (f3.isReady())
            {
                if (ready)
                {
                    window.draw(button_gr_v2v);
                }
                window.draw(v_1);
            }

            window.display();
        }
    }
    return 0;
}
