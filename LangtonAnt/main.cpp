#include <iostream>
#include <bitset>
#include <SFML/Graphics.hpp>

#define FLIP_BOOL(x) x = !x


const size_t width = SCREENSIZE, height = SCREENSIZE, areaH = height/6, areaW = width/6;
enum class Direction
{
    START_OF_LIST,
    Left,
    Up,
    Right,
    Down,
    END_OF_LIST
};
Direction& operator++( Direction &c ) {
    using IntType = typename std::underlying_type<Direction>::type;
    c = static_cast<Direction>( static_cast<IntType>(c) + 1 );
    if ( c == Direction::END_OF_LIST )
        c = static_cast<Direction>(1);
    return c;
}
Direction operator++( Direction &c, int ) {
    Direction result = c;
    ++c;
    return result;
}
Direction& operator--( Direction &c ) {
    using IntType = typename std::underlying_type<Direction>::type;
    c = static_cast<Direction>( static_cast<IntType>(c) - 1 );
    if ( c == Direction::START_OF_LIST )
        c = static_cast<Direction>(4);
    return c;
}
Direction operator--( Direction &c, int ) {
    Direction result = c;
    --c;
    return result;
}


void initialize(std::array<std::bitset<areaH>,areaW>& area,sf::Shape& ant)
{
    ant.setOrigin(6,6);
    ant.setPosition(width/2,height/2);
    ant.setFillColor(sf::Color::Red);
    srand(uint(time(nullptr)));
    for(size_t i=0;i<areaH;i++)
        for(size_t j=0;j<areaW;j++)
            area[i][j]=false;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(width,height),"Ant");
    sf::Event event;
    sf::CircleShape dot(3), ant(6);
    std::array<std::bitset<areaH>,areaW> area;
    Direction curDir = Direction::Up;
    size_t y=areaH/2,x=areaW/2;
    dot.setFillColor(sf::Color::White);
    initialize(area,ant);
    while (window.isOpen())
    {
        if(window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                initialize(area,ant);
                break;
            default:;
            }
        window.clear(sf::Color::Black);
        for(size_t i=0;i<areaH;i++)
            for(size_t j=0;j<areaW;j++)
                if(area[j][i])
                {
                    dot.setPosition(6*j,6*i);
                    window.draw(dot);
                }
        window.draw(ant);
        window.display();
        switch (curDir)
        {
        case Direction::Up:
            y--;
            break;
        case Direction::Left:
            x--;
            break;
        case Direction::Right:
            x++;
            break;
        case Direction::Down:
            y++;
            break;
        default:
            std::cout << "And what went wrong?\n" << std::endl;
        }
        x+= areaW; y+= areaH; x%= areaW; y%= areaH;
        ant.setPosition(6*x,6*y);
        area[x][y] = !area[x][y];
        if(area[x][y])
            curDir++;
        else
            curDir--;
    }
    return 0;
}
