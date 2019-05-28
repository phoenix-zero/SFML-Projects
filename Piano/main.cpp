#include <bits/stdc++.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct Sound
{
    Sound(double pitch);
    void play();
    void pause();
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

void handleKeyboard(unsigned short mScale);
void handleEvent(const sf::Event &event, sf::RenderWindow &window, unsigned short &mScale);

int main(int , char **)
{
    sf::RenderWindow window(sf::VideoMode(800,800),"Piano");
    sf::Event event;
    window.setFramerateLimit(60);
    unsigned short mScale=1;
    while (window.isOpen())
    {
        if(window.pollEvent(event))
        {
            handleEvent(event,window,mScale);
            handleKeyboard(mScale);
        }
    }
    return 0;
}

void handleKeyboard(unsigned short mScale)
{
    const static sf::Keyboard::Key keys[12] =
    {
        sf::Keyboard::A,sf::Keyboard::W,
        sf::Keyboard::S,sf::Keyboard::E,
        sf::Keyboard::D,sf::Keyboard::F,
        sf::Keyboard::T,sf::Keyboard::G,
        sf::Keyboard::Y,sf::Keyboard::H,
        sf::Keyboard::U,sf::Keyboard::J
    };
    static Sound frequencies[][12] =
    {
        {130.8128,138.5913,146.8324,155.5635,164.8138,174.6141,184.9972,195.9977,207.6523,220.0000,233.0819,246.9417},
        {261.6256,277.1826,293.6648,311.1270,329.6276,349.2282,369.9944,391.9954,415.3047,440.0000,466.1638,493.8833},
        {523.2511,554.3653,587.3295,622.2540,659.2551,698.4565,739.9888,783.9909,830.6094,880.0000,932.3275,987.7666},
        {1046.502,1108.731,1174.659,1244.508,1318.510,1398.913,1479.978,1567.982,1661.219,1760.000,1864.655,1975.533}
    };
    for(size_t i=0; i<12; i++)
    {
        if(sf::Keyboard::isKeyPressed(keys[i]))
        {
            frequencies[mScale][i].play();
        }
        else
        {
            frequencies[mScale][i].pause();
        }
    }
}

void handleEvent(const sf::Event& event,sf::RenderWindow& window,unsigned short& mScale)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Z:
            if(mScale==0)
                mScale = 3;
            else
                mScale--;
            std::cout << mScale << std::endl;
            break;
        case sf::Keyboard::X:
            mScale++;
            if(mScale>3)
                mScale = 0;
            std::cout << mScale << std::endl;
            break;
        case sf::Keyboard::Num0:
        case sf::Keyboard::Numpad0:
            mScale = 0;
            break;
        case sf::Keyboard::Num1:
        case sf::Keyboard::Numpad1:
            mScale = 1;
            break;
        case sf::Keyboard::Num2:
        case sf::Keyboard::Numpad2:
            mScale = 2;
            break;
        case sf::Keyboard::Num3:
        case sf::Keyboard::Numpad3:
            mScale = 3;
            break;
        default:;
        }
        break;
    default:;
    }
}


Sound::Sound(double pitch)
{
    sf::Int16 raw[44100];
    double increment = pitch/44100, x = 0;
    for(unsigned i=0;i<44100;i++)
    {
        raw[i] = static_cast<sf::Int16>(30000 * sin(x*6.28318));
        x += increment;
    }

    if(!buffer.loadFromSamples(raw,44100,1,44100))
    {
        throw "Can't load buffer!";
    }
    sound.setBuffer(buffer);
    sound.setLoop(false);
}

void Sound::play()
{
    if(sound.getStatus() != sf::Sound::Playing )
        sound.play();
}

void Sound::pause()
{
    sound.stop();
}
