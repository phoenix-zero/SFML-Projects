#include <iostream>
#include <map>
#include <cmath>
#include <stack>
#include <SFML/Graphics.hpp>

static std::map<char,std::string> rules=
{
    //{'F',"FF+[+F-F-F]-[-F+F+F]"},
    {'X', "F+[[X]-X]-F[-FX]+X"},
    {'F', "FF"}
};
static sf::RenderWindow window;
static int length = 400;

void ruleOut(std::string& axiom)
{
    std::string nextSentence = "";
    for(char i : axiom)
    {
        if(rules.count(i))
            nextSentence += rules[i];
        else
            nextSentence += i;
    }
    axiom = nextSentence;
    length*=0.5;
}

void turtle(const std::string& axiom)
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    std::stack<std::array<double,3>> state;
    const double angleRotate = 0.436332; // 25d else M_PI/6
    double x=window.getSize().x/2,y=window.getSize().y;
    double angle=M_PI_2;
    for(char i : axiom)
    {
        if(i=='F')
        {
            lines[0].position = sf::Vector2<float>(float(x), float(y));
            lines[1].position = sf::Vector2<float>(static_cast<float>(x+length*cos(angle)),static_cast<float>(y-length*sin(angle)));
            lines[1].color = sf::Color(255,0,255);
            lines[0].color = sf::Color(255,0,255);
            window.draw(lines);
            x+= length*cos(angle);
            y-= length*sin(angle);
        }
        else if(i=='+')
        {
            angle+=angleRotate;
        }
        else if(i=='-')
        {
            angle-= angleRotate;
        }
        else if(i=='[')
        {
            state.push(std::array<double,3>({x,y,angle}));
        }
        else if(i==']')
        {
            x=state.top()[0];
            y=state.top()[1];
            angle=state.top()[2];
            state.pop();
        }
    }
}

int main()
{
    std::string axiom="X";
    window.create(sf::VideoMode(1000,1000),"Fractal Tree");
    sf::Event event;

    while(window.isOpen())
    {
        window.clear(sf::Color::White);
        turtle(axiom);
        if(window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::MouseButtonPressed:
                ruleOut(axiom);
                break;
            default:;
            }
        window.display();
    }
    return 0;
}
