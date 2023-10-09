#include <iostream>
#include "solution.h"
#include "methoods.h"
#include <SFML/Graphics.hpp>

using namespace sf;


double right_part(double x = 0, double u = 0) {// правая часть ДУ
    return -2.5 * u;
}




int main()
{
    double* ic{ new double[2] {0,1} };


    double h = 0.001;

    solution sol1(1,100, &ic[0], h, right_part, em); //порядок, количество шагов, начальные условия, шаг, правая часть, метод
    sol1.start_with_le();
    sol1.print();
    
    RenderWindow window(VideoMode(400, 400), L"Новый проект", Style::Default);

    

    window.setVerticalSyncEnabled(true);

    CircleShape shape(100.f, 3);
    shape.setPosition(100, 100);
    shape.setFillColor(Color::Magenta);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Blue);
        window.draw(shape);
        window.display();
    }

    

    return 0;
}