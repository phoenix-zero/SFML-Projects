#include <iostream>
#include <bitset>
#include <SFML/Graphics.hpp>


const size_t width = 600, height = 600, areaH = height/6, areaW = width/6;

unsigned no_of_neighbours(std::array<std::bitset<areaH>,areaW> area,size_t i,size_t j)
{
    unsigned total=0;
    if(i!=0) total += (area[i-1][j]?1:0); else total += (area[areaW-1][j]);
    if(j!=0) total += (area[i][j-1]?1:0); else total += (area[i][areaH-1]);
    if(i!=areaW-1) total += (area[i+1][j]?1:0); else total += (area[0][j]);
    if(j!=areaH-1) total += (area[i][j+1]?1:0); else total += (area[i][0]);
    if(i!=0 && j!=0) total += (area[i-1][j-1]?1:0); else total += (area[areaH-1][areaW-1]);
    if(i!=areaW-1 && j!=areaW) total += (area[i+1][j+1]?1:0); else total += (area[0][0]);
    if(i!=areaW-1 && j!=0) total += (area[i+1][j-1]?1:0); else total += (area[0][areaH-1]);
    if(i!=0 && j!=areaH) total += (area[i-1][j+1]?1:0); else total += (area[areaW-1][0]);
    return total;
}

void initialize(std::array<std::bitset<areaH>,areaW>& area)
{
    for(size_t i=0;i<areaH;i++)
        for(size_t j=0;j<areaW;j++)
            area[i][j] = false;
#ifdef RANDOM
    srand(uint(time(nullptr)));
    for(size_t i=0;i<areaH;i++)
        for(size_t j=0;j<areaW;j++)
            area[i][j]=area[i][j] = !(random()%9);
#else
    area[1][5]=area[2][5]=area[1][6]=area[2][6]=
       area[36][4]=area[36][3]=area[35][3]=area[35][4]=
       area[11][5]=area[11][6]=area[11][7]=area[11][5]=area[12][4]=
       area[12][8]=area[13][3]=area[13][9]=area[14][9]=area[14][3]=area[18][6]=
       area[15][6]=area[16][8]=area[16][4]=area[17][5]=area[17][6]=area[17][7]=
       area[21][5]=area[21][4]=area[21][3]=area[22][5]=area[22][4]=area[22][3]=
       area[23][2]=area[23][6]=area[25][6]=area[25][2]=area[25][1]=area[25][7]=true;
#endif
}

void calculateGOL(std::array<std::bitset<areaH>,areaW>& area,
                  std::array<std::bitset<areaH>,areaW> areaCopy)
{
    unsigned n;
    for(size_t i=0;i<areaW;i++)
        for(size_t j=0;j<areaH;j++)
        {
            n=no_of_neighbours(areaCopy,i,j);
            if(areaCopy[i][j] && (n<2 || n>3))
                area[i][j] = false;
            else if(!areaCopy[i][j] && n==3)
                area[i][j]=true;
        }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width,height),"GOL");
    sf::Event event;
    sf::RectangleShape dot(sf::Vector2f(6,6));
    std::array<std::bitset<areaH>,areaW> area;
    dot.setFillColor(sf::Color::White);
    initialize(area);
    while (window.isOpen())
    {
        if(window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                initialize(area);
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
        calculateGOL(area,area);
        window.display();
    }
    return 0;
}
