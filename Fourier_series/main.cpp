#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

int main()
{
    std::vector<float> waveHeight;
    sf::RenderWindow window(sf::VideoMode(1000,500),"Fourier");
    sf::Event e;
    sf::CircleShape circle(50),point(2);
    sf::VertexArray line(sf::LineStrip,2),wave(sf::LineStrip,2),joint(sf::LineStrip,2);
    float time = 0,x,y,prevX,prevY;
    float radius=0;
    unsigned n=0;
    circle.setFillColor(sf::Color(255,0,0,0));
    circle.setPosition(300,200);
    circle.setOutlineColor(sf::Color::Yellow);
    circle.setOutlineThickness(1);
    circle.setOrigin(50,50);
    point.setOrigin(2,2);
    line[1].position = {200,200};
    wave[0].color = sf::Color::Green;
    wave[1].color = sf::Color::Green;
    while(window.isOpen())
    {
        window.clear(sf::Color::Red);
        if(window.pollEvent(e))
            switch (e.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:;
            }
        prevX=0; prevY=0;
        x=200; y=200;
        for(size_t i=0;i<n;i++)
        {
            prevX =x; prevY =y;
            radius = 100 * (4/static_cast<float>((i*2 + 1 )*M_PI));
            x += radius*cos((i*2 + 1)*time);
            y += radius*sin((i*2 + 1)*time);
            line[0].position = {prevX,prevY};
            line[1].position = {x,y};
            circle.setRadius(radius);
            circle.setOrigin(radius,radius);
            circle.setPosition(prevX,prevY);
            window.draw(circle);
            window.draw(line);
        }
        waveHeight.insert(waveHeight.begin(),y);
        point.setPosition(x,y);
        joint[0].position = {x,y};
        joint[1].position = {400,waveHeight[0]};
        joint[0].color = joint[1].color = sf::Color::Blue;
        for(size_t i=0;i<waveHeight.size()-1;i++)
        {
            wave[0].position = {400 + float(i)/10,waveHeight[i]};
            wave[1].position = {400 + float(i+1)/10,waveHeight[i+1]};
            window.draw(wave);
        }
        window.draw(wave);
        window.draw(point);
        window.draw(joint);
        window.display();
        time += 0.01f;
        if(waveHeight.size() > 10000)
            waveHeight.pop_back();
        n = static_cast<unsigned>(((sf::Mouse::getPosition(window).x%1000) * 15.0 / window.getSize().x));
    }
    return 0;
}
