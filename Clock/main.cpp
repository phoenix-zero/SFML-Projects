#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(600,600),"Clock");
    sf::Event event;
    std::time_t timeNow;
    std::tm* now;
    sf::VertexArray arc(sf::LinesStrip,360);
    sf::RectangleShape rect;
    while(window.isOpen())
    {
        if(window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:;
            }
        timeNow = std::time(nullptr);
        now = std::localtime(&timeNow);
        window.clear();
        for(size_t i=0;i<360;i++)
        {
            arc[i].position = sf::Vector2f(300+210*cos(i*0.017453293f),300+210*sin(i*0.017453293f));
            arc[i].color = (now->tm_hour < 12 ? sf::Color::Yellow : sf::Color::Black);
        }
        window.draw(arc);
        for(size_t i=0;i<360;i++)
        {
            arc[i].position = sf::Vector2f(300+200*cos(i*0.017453293f),300+200*sin(i*0.017453293f));
            arc[i].color = ((i+90)%360 < static_cast<size_t>(now->tm_hour%12)*30? sf::Color::Blue : sf::Color::Black);
        }
        window.draw(arc);
        for(size_t i=0;i<360;i++)
        {
            arc[i].position = sf::Vector2f(300+180*cos(i*0.017453293f),300+180*sin(i*0.017453293f));
            arc[i].color = ((i+90)%360 < static_cast<size_t>(now->tm_sec)*6? sf::Color::Green : sf::Color::Black);
        }
        window.draw(arc);
        for(size_t i=0;i<360;i++)
        {
            arc[i].position = sf::Vector2f(300+190*cos(i*0.017453293f),300+190*sin(i*0.017453293f));
            arc[i].color = ((i+90)%360 < static_cast<size_t>(now->tm_min)*6? sf::Color::Red : sf::Color::Black);
        }
        window.draw(arc);
        window.display();
    }

    return 0;
}
