#pragma once
#include <SFML/Graphics.hpp>


class TextField : public sf::Transformable, public sf::Drawable
{
public:
    TextField(unsigned int maxChars = 10, unsigned int charSize = 15) :
        m_size(maxChars),
        char_size(charSize),
        m_rect(sf::Vector2f(15 * m_size, 20)),
        m_hasfocus(false)
    {
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(this->getPosition());
        m_name = sf::String(L"Имя по умолчанию");
    }

    int isReady()
    {
        return m_text.size() != 0;
    }

    const std::string getText() const
    {
        return m_text;
    }

    double getValue()
    {
        return stod(m_text);
    }

    void setName(sf::String name)
    {
        m_name = name;
    }

    void setPosition(float x, float y)
    {
        sf::Transformable::setPosition(x, y);
        m_rect.setPosition(x, y);
    }

    void setPosition(sf::Vector2f position)
    {
        sf::Transformable::setPosition(position);
        m_rect.setPosition(position);
    }

    bool contains(sf::Vector2f point) const
    {
        return m_rect.getGlobalBounds().contains(point);
    }

    void setFocus(bool focus)
    {
        m_hasfocus = focus;
        if (focus) {
            m_rect.setOutlineColor(sf::Color::Blue);
        }
        else {
            m_rect.setOutlineColor(sf::Color(127, 127, 127));
        }
    }


    void handleInput(sf::Event e)
    {
        if (!m_hasfocus || e.type != sf::Event::TextEntered)
            return;
        if (e.text.unicode == 8) {   // Delete key
            m_text = m_text.substr(0, m_text.size() - 1);
        }
        else if (m_text.size() < m_size) {
            if (e.text.unicode == '.' && m_text.find('.') == std::string::npos)
                m_text += e.text.unicode;
            if (e.text.unicode >= '0' && e.text.unicode <= '9')
                m_text += e.text.unicode;
            if (e.text.unicode == '-' && m_text.size() == 0)
                m_text += e.text.unicode;
        }
    }


    sf::Vector2f getPosition()
    {
        return m_rect.getPosition();
    }

    sf::Vector2f getSize()
    {
        return m_rect.getSize();
    }

    void clear()
    {
        m_text = "";
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Text text_name;
        sf::Vector2 <float> pos = m_rect.getPosition();
        pos.y -= char_size * 1.5;
        pos.x += m_rect.getSize().x / 2 - 7.5;
        text_name.setFont(m_font);
        text_name.setString(m_name);
        text_name.setCharacterSize(char_size);
        text_name.setFillColor(sf::Color::Black);
        text_name.setPosition(pos);
        target.draw(text_name);


        target.draw(m_rect, states);
        sf::Text text;
        text.setFont(m_font);
        text.setString(m_text);
        text.setCharacterSize(char_size);
        text.setFillColor(sf::Color::Black);
        text.setPosition(m_rect.getPosition());
        target.draw(text);
    }

private:
    unsigned int m_size, char_size;
    sf::Font m_font;
    std::string m_text;
    sf::String m_name;
    sf::RectangleShape m_rect;
    bool m_hasfocus;
};

class Table : public sf::Transformable, public sf::Drawable
{
public:
    Table() :
        m_hasfocus(false),
        start_pos(0)
    {
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        table_border.setOutlineThickness(2);
        table_border.setFillColor(sf::Color::White);
        table_border.setOutlineColor(sf::Color(127, 127, 127));
        table_border.setPosition(this->getPosition());
        rows_show = 5;
    }

    void setSize(sf::Vector2f size)
    {
        table_border.setSize(size);
    }

    void setPosition(float x, float y)
    {
        sf::Transformable::setPosition(x, y);
        table_border.setPosition(x, y);
    }

    void setPosition(sf::Vector2f position)
    {
        sf::Transformable::setPosition(position);
        table_border.setPosition(position);
    }

    bool contains(sf::Vector2f point) const
    {
        return table_border.getGlobalBounds().contains(point);
    }

    void setFocus(bool focus)
    {
        m_hasfocus = focus;
        if (focus) {
            table_border.setOutlineColor(sf::Color::Black);
        }
        else {
            table_border.setOutlineColor(sf::Color(127, 127, 127));
        }
    }

    sf::Vector2f getPosition()
    {
        return table_border.getPosition();
    }

    sf::Vector2f getSize()
    {
        return table_border.getSize();
    }

    void setRows(size_t rows)
    {
        rows_show = rows;
    }

    void setNames(std::vector<std::string> names)
    {
        this->names = names;
    }

    void setData(std::vector<std::vector<double>> data)
    {
        this->data = data;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(table_border, states);

        sf::Vector2f size = table_border.getSize();
        sf::Vector2f pos = table_border.getPosition();



        sf::RectangleShape line(sf::Vector2f(size.x, 2));
        line.setFillColor(table_border.getOutlineColor());

        for (size_t i = 1; i < rows_show; i++)
        {
            line.setPosition(pos.x, pos.y + i * (size.y / rows_show));
            target.draw(line, states);
        }

        line.setSize(sf::Vector2f(size.y, 2));
        line.setRotation(90);



        sf::Text text;
        text.setFont(m_font);
        text.setCharacterSize(char_size);
        text.setFillColor(sf::Color::Black);


        target.draw(text);
        for (size_t i = 1; i < names.size(); i++)
        {
            line.setPosition(pos.x + i * (size.x / names.size()), pos.y);
            target.draw(line, states);
        }

        for (size_t i = 0; i < names.size(); i++)
        {
            text.setString(names[i]);
            text.setPosition(pos.x + 10 + i * (size.x / names.size()), pos.y + (size.y / rows_show) / 2 - char_size / 2);
            target.draw(text, states);
        }

        for (size_t i = 0; i < rows_show - 1; i++)
        {
            for (size_t j = 0; j < data[i].size(); j++)
            {
                text.setString(std::to_string(data[i + start_pos][j]));
                text.setPosition(pos.x + j * (size.x / names.size()) + 5, pos.y + (size.y / rows_show) * 1.5 - char_size / 2 + i * (size.y / rows_show));
                target.draw(text, states);
            }
        }


    }


    void handleInput(sf::Event e)
    {
        if (!m_hasfocus || e.type != sf::Event::MouseWheelScrolled)
            return;

        if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            start_pos -= (int)e.mouseWheelScroll.delta;
        if (start_pos < 0)
            start_pos = 0;
        if (start_pos > data.size() - rows_show + 1)
            start_pos = data.size() - rows_show + 1;
    }

private:
    sf::RectangleShape table_border;
    bool m_hasfocus;
    sf::Font m_font;
    size_t rows_show;
    int start_pos;

    std::vector<std::string> names;
    std::vector<std::vector<double>> data;

    unsigned int char_size = 10;
};

class Button : public sf::Transformable, public sf::Drawable
{
public:
    Button(sf::String name = "set_name") :
        m_text(name),
        m_rect(sf::Vector2f(10 * name.getSize(), 20)),
        m_hasfocus(false)
    {
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(this->getPosition());
    }

    void setName(sf::String name = "set_name")
    {
        m_text = name;
        m_rect.setSize(sf::Vector2f(10 * name.getSize(), 20));
        m_hasfocus = false;
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf"); 
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(this->getPosition());
    }

    bool isReady()
    {
        return m_hasfocus;
    }


    void setPosition(float x, float y)
    {
        sf::Transformable::setPosition(x, y);
        m_rect.setPosition(x, y);
    }

    sf::Vector2f getPosition()
    {
        return m_rect.getPosition();
    }

    sf::Vector2f getSize()
    {
        return m_rect.getSize();
    }

    bool contains(sf::Vector2f point) const
    {
        return m_rect.getGlobalBounds().contains(point);
    }

    void tuch(bool focus)
    {
        m_hasfocus = focus;
        if (focus) {
            m_rect.setOutlineColor(sf::Color::Blue);
        }
        else {
            m_rect.setOutlineColor(sf::Color(127, 127, 127));
        }
    }

    void setPosition(sf::Vector2f position)
    {
        sf::Transformable::setPosition(position);
        m_rect.setPosition(position);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_rect, states);
        sf::Text text;
        text.setFont(m_font);
        text.setString(m_text);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        sf::Vector2f pos = m_rect.getPosition();
        pos.x += 5;
        text.setPosition(pos);
        target.draw(text);
    }

private:
    sf::Font m_font;
    sf::String m_text;
    sf::RectangleShape m_rect;
    bool m_hasfocus;
};

class boolField : public sf::Transformable, public sf::Drawable
{
public:
    boolField(sf::String name = "set_name") :
        m_text(name)
    {
        m_rect.setSize(sf::Vector2f(10, 10)); 
        m_hasfocus = false;
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        m_rect.setOutlineThickness(1);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color::Black);
        m_rect.setPosition(this->getPosition());
    }

    void setName(sf::String name = "set_name")
    {
        m_text = name;
        m_hasfocus = false;
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(this->getPosition());
    }

    bool isReady()
    {
        return m_hasfocus;
    }


    void setPosition(float x, float y)
    {
        sf::Transformable::setPosition(x, y);
        m_rect.setPosition(x, y);

    }



    bool contains(sf::Vector2f point) const
    {
        return m_rect.getGlobalBounds().contains(point);
    }

    void tuch()
    {
        m_hasfocus = !m_hasfocus;
        if (m_hasfocus) {
            m_rect.setFillColor(sf::Color::Black);
        }
        else {
            m_rect.setFillColor(sf::Color::White);
        }
    }

    void setPosition(sf::Vector2f position)
    {
        sf::Transformable::setPosition(position);
        m_rect.setPosition(position);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_rect, states);
        sf::Text text;
        text.setFont(m_font);
        text.setString(m_text);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        sf::Vector2f pos = m_rect.getPosition();
        pos.y -= text.getCharacterSize() + 3;
        text.setPosition(pos);
        target.draw(text);
    }

private:
    sf::Font m_font;
    sf::String m_text;
    sf::RectangleShape m_rect;
    bool m_hasfocus;
};

class OXY : public sf::Drawable
{
public:
    OXY()
    {
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
        pos_o = sf::Vector2f(0, 500);
        color = sf::Color::Black;

    }
    ~OXY() {}

    void setColor(sf::Color color)
    {
        this->color = color;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Vertex lin[] =
        {
            sf::Vertex(sf::Vector2f(0,0)),
            sf::Vertex(sf::Vector2f(0,0))
        };

        sf::Text text;
        text.setFont(m_font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        sf::Vector2f pos;


        for (int i = -1; i < target.getSize().x / pixel_on_x + 1; i++)
        {
            lin[0].color = sf::Color(127, 127, 127, 150);
            lin[1].color = sf::Color(127, 127, 127, 150);
            lin[0].position = sf::Vector2f(((int)pos_o.x % (int)pixel_on_x) + i * pixel_on_x, 0);
            lin[1].position = sf::Vector2f(((int)pos_o.x % (int)pixel_on_x) + i * pixel_on_x, target.getSize().y);
            target.draw(lin, 2, sf::Lines);
            text.setString(std::to_string(-(int)(pos_o.x / pixel_on_x) + i));
            text.setPosition(lin[0].position.x, target.getSize().y - 20);
            target.draw(text);

            if (pixel_on_x >= 200)
            {
                lin[0].color = sf::Color(127, 127, 127, 50);
                lin[1].color = sf::Color(127, 127, 127, 50);
                for (int j = (int)pos_o.x % (int)pixel_on_x + i * pixel_on_x; j < (int)pos_o.x % (int)pixel_on_x + (i + 1) * pixel_on_x; j += 40)
                {
                    lin[0].position = sf::Vector2f(j, 0);
                    lin[1].position = sf::Vector2f(j, target.getSize().y);
                    target.draw(lin, 2, sf::Lines);
                }
            }
        }

        for (int i = -1; i < target.getSize().y / pixel_on_x + 1; i++)
        {
            lin[0].color = sf::Color(127, 127, 127, 150);
            lin[1].color = sf::Color(127, 127, 127, 150);
            lin[0].position = sf::Vector2f(0, ((int)pos_o.y % (int)pixel_on_x) + i * pixel_on_x);
            lin[1].position = sf::Vector2f(target.getSize().x, ((int)pos_o.y % (int)pixel_on_x) + i * pixel_on_x);
            target.draw(lin, 2, sf::Lines);
            text.setString(std::to_string((int)(pos_o.y / pixel_on_x) - i));
            text.setPosition(lin[0].position);
            target.draw(text);

            if (pixel_on_x >= 200)
            {
                lin[0].color = sf::Color(127, 127, 127, 50);
                lin[1].color = sf::Color(127, 127, 127, 50);
                for (int j = (int)pos_o.y % (int)pixel_on_x + i * pixel_on_x; j < (int)pos_o.y % (int)pixel_on_x + (i + 1) * pixel_on_x; j += 40)
                {
                    lin[0].position = sf::Vector2f(0, j);
                    lin[1].position = sf::Vector2f(target.getSize().x, j);
                    target.draw(lin, 2, sf::Lines);
                }
            }
        }

        lin[0].color = color;
        lin[1].color = color;
        for (size_t i = 0; i < gr.size() - 1; i++)
        {
            lin[0].position = sf::Vector2f(gr[i].x * pixel_on_x, -gr[i].y * pixel_on_x) + pos_o;
            lin[1].position = sf::Vector2f(gr[i + 1].x * pixel_on_x, -gr[i + 1].y * pixel_on_x) + pos_o;
            target.draw(lin, 2, sf::Lines);
        }
    }


    void handleInput(sf::Event e)
    {
        if (e.type != sf::Event::MouseButtonPressed && e.type != sf::Event::MouseMoved &&
            e.type != sf::Event::MouseButtonReleased && e.type != sf::Event::MouseWheelScrolled)
            return;


        if (e.type == sf::Event::MouseWheelScrolled)
        {
            e.mouseWheelScroll.delta;
            if (e.mouseWheelScroll.delta > 0)
            {
                if (pixel_on_x < 500)
                {
                    pixel_on_x *= 2;

                    pos_o.x += pos_o.x - e.mouseWheelScroll.x;
                    pos_o.y += pos_o.y - e.mouseWheelScroll.y;
                }
            }
            else
            {
                if (pixel_on_x > 40)
                {
                    pixel_on_x /= 2;
                    pos_o.x = 0.5 * (pos_o.x + e.mouseWheelScroll.x);
                    pos_o.y = 0.5 * (pos_o.y + e.mouseWheelScroll.y);
                }
            }
        }


        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button)
            {
                status_r = true;
            }
            else
            {
                status_l = true;
                last_pos.x = e.mouseButton.x;
                last_pos.y = e.mouseButton.y;
            }
        }

        if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == 0)
            status_l = false;


        if (status_l && e.type == sf::Event::MouseMoved)
        {
            move(sf::Vector2f(e.mouseMove.x - last_pos.x, e.mouseMove.y - last_pos.y));
            last_pos.x = e.mouseMove.x;
            last_pos.y = e.mouseMove.y;
        }
    }

    void move(sf::Vector2f m)
    {
        pos_o += m;
    }

    void add(std::vector<sf::Vector2f> line)
    {
        gr = line;
    }

    void add(std::vector<double> t, std::vector<double> x)
    {
        for (size_t i = 0; i < t.size(); i++)
        {
            gr.push_back(sf::Vector2f(t[i], x[i]));
        }
    }


private:
    sf::Font m_font;
    sf::Vector2f pos_o, last_pos;
    double pixel_on_x = 100;
    bool status_r = false, status_l = false;
    std::vector<sf::Vector2f> gr;
    sf::Color color;
};

void graph(std::vector<std::vector<double>> line_)
{
    sf::RenderWindow wind({ 900, 900 }, "graph", sf::Style::Close);


    OXY ox;
    ox.add(line_[0], line_[1]);
    ox.setColor(sf::Color::Red);





    while (wind.isOpen())
    {
        for (sf::Event event; wind.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                wind.close();


            ox.handleInput(event);

            wind.clear(sf::Color::White);

            wind.draw(ox);
            wind.display();
        }
    }
}
