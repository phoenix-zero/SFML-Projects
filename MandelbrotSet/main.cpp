#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>

static unsigned width=1000,height=1000;
static double rangeMinX=-100,rangeMaxX=100,rangeMinY=-100,rangeMaxY=100;

double map(double inValue, unsigned minSource, unsigned maxSource, double minDest, double maxDest)
{
    return (inValue-minSource)/(maxSource-minSource)*(maxDest-minDest) + minDest;
}

sf::Color hsv(int hue, float sat, float val)
{
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(sf::Uint8(val*255), sf::Uint8(t*255), sf::Uint8(p*255));
    case 1: return sf::Color(sf::Uint8(q*255), sf::Uint8(val*255), sf::Uint8(p*255));
    case 2: return sf::Color(sf::Uint8(p*255), sf::Uint8(val*255), sf::Uint8(t*255));
    case 3: return sf::Color(sf::Uint8(p*255), sf::Uint8(q*255), sf::Uint8(val*255));
    case 4: return sf::Color(sf::Uint8(t*255), sf::Uint8(p*255), sf::Uint8(val*255));
    case 5: return sf::Color(sf::Uint8(val*255), sf::Uint8(p*255), sf::Uint8(q*255));
  }
}

void computeMandelbrotSet(std::vector<unsigned char> &pixels)
{

    unsigned pix=0,n;
    unsigned short hue;
    std::complex<double> pixel,c;
    float sat=0,val=0;
    for(unsigned x=0;x<width;x++)
    {
        for(unsigned y=0;y<height;y++)
        {
            n=0;
            sat=1; val=1;
            c=pixel = std::complex<double>(map(x,0,width,rangeMinX,rangeMaxX),
                                           map(y,0,height,rangeMinY,rangeMaxY));
            while(n<500)
            {
                pixel = std::pow(pixel,4);
                pixel += c;
                if(std::abs(pixel)>16)
                    break;
                n++;
            }
            hue = static_cast<unsigned char>(map(sqrt(map(n,0,500,0,1)),0,1,0,360));
            val = static_cast<float>(map(n,0,500,1,0));
            if(n==500)
                val=0;
            else if(n==0)
                val=0;

            pix= (x+y*width)*4;
            pixels[pix] = hsv(hue,sat,val).r;
            pixels[pix+1] = hsv(hue,sat,val).g;
            pixels[pix+2] = hsv(hue,sat,val).b;
            pixels[pix+3] = 255;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width,height),"Mandelbrot");
    sf::Event event;
    std::vector<unsigned char> pixels(width*height*4);
    sf::Texture texture;
    texture.create(width,height);
    sf::Sprite sprite(texture);

    double rangeX = static_cast<unsigned>(rangeMaxX-rangeMinX),rangeY =
            static_cast<unsigned>(rangeMaxY-rangeMinY),mouseX,mouseY;

    computeMandelbrotSet(pixels);

    while(window.isOpen())
    {
        if(window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::Resized:
                computeMandelbrotSet(pixels);
                break;
            case sf::Event::EventType::MouseButtonPressed:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    rangeMinX=-2;
                    rangeMaxX=2;
                    rangeMinY=-2;
                    rangeMaxY=2;
                    rangeX = static_cast<unsigned>(rangeMaxX-rangeMinX);
                    rangeY = static_cast<unsigned>(rangeMaxY-rangeMinY);
                    computeMandelbrotSet(pixels);
                    break;
                }
                mouseX=map(static_cast<unsigned int>(sf::Mouse::getPosition(window).x),0,
                           width,rangeMinX,rangeMaxX);
                mouseY=map(static_cast<unsigned int>(sf::Mouse::getPosition(window).y),0,
                           height,rangeMinY,rangeMaxY);
                rangeMinX=mouseX-rangeX/3;
                rangeMaxX=mouseX+rangeX/3;
                rangeMinY=mouseY-rangeY/3;
                rangeMaxY=mouseY+rangeY/3;
                rangeX = static_cast<unsigned>(rangeMaxX-rangeMinX);
                rangeY = static_cast<unsigned>(rangeMaxY-rangeMinY);
                computeMandelbrotSet(pixels);
                break;
            default:;
            }
        window.clear(sf::Color::Black);

        texture.update(&pixels[0]);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
