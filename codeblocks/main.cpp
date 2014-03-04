#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include "Character.h"
#include "RenderHandler.h"
#include "AudioHandler.h"
#include "Map.h"



int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window->setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("assets/general/player.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    RenderHandler* renderHandler = new RenderHandler(window);

    //Try Gameobject class
    Character* mainCharacter = new Character();
    mainCharacter->setAnimation(walkingAnimationDown);

    Map* level = new Map();
    if(!level->setScene("Has temporary been disabled for parameter"))
    {
        return 1;
    }
    level->setMapPosition(sf::Vector3f(100,100,0),sf::Vector3f(0,0,0));
    level->addGO(mainCharacter, sf::Vector2f(50,50));


    sf::Clock frameClock;
    sf::Event *event;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    // Test AudioHandler
    AudioHandler* auh = new AudioHandler();
    int s1 = auh->loadSound("assets/audio/Page Turn.wav");
    auh->playMusic("assets/audio/Yosuga No Sora OST 1.wav");
    std::cout << "AudioHandler index used: " << s1 << std::endl;
    std::cout << "Press q to turn a page." << std::endl;
    std::cout << "Press e to play music." << std::endl;
    std::cout << "Press r to pause music." << std::endl;
    std::cout << "Press a to increase volume." << std::endl;
    std::cout << "Press z to decrease volume." << std::endl;



    while (window->isOpen())
    {
        event = new sf::Event();
        while (window->pollEvent(*event))
        {
            if (event->type == sf::Event::Closed)
                window->close();
            if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape)
                window->close();
        }

        sf::Time frameTime = frameClock.restart();

        if(event->type == sf::Event::KeyReleased) {
            if(event->key.code == sf::Keyboard::Q) {
                auh->playSound(s1);
            }
            if(event->key.code == sf::Keyboard::E) {
                auh->playMusic();
            }
            if(event->key.code == sf::Keyboard::R) {
                auh->pauseMusic();
            }
            if(event->key.code == sf::Keyboard::A) {
                auh->setVolume(auh->getVolume() + 5);
                std::cout << "\tVolume is " << auh->getVolume() << "\n";
            }
            if(event->key.code == sf::Keyboard::Z) {
                auh->setVolume(auh->getVolume() - 5);
                std::cout << "\tVolume is " << auh->getVolume() << "\n";
            }
        }

        sf::Vector3f pos = level->getMapPos();


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            level->setMapPosition(sf::Vector3f(pos.x+1,pos.y,pos.z), sf::Vector3f(0,0,0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            level->setMapPosition(sf::Vector3f(pos.x-1,pos.y,pos.z),sf::Vector3f(0,0,0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            level->setMapPosition(sf::Vector3f(pos.x,pos.y-1,pos.z),sf::Vector3f(0,0,0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            level->setMapPosition(sf::Vector3f(pos.x,pos.y+1,pos.z),sf::Vector3f(0,0,0));
        }

        renderHandler->addRender(level);
        renderHandler->update(frameTime);

        delete event;
    }

    delete renderHandler;
    renderHandler = nullptr;

    delete auh;
    auh = nullptr;

    delete level;
    level = nullptr;

    delete mainCharacter;
    mainCharacter = nullptr;

    delete window;
    window = nullptr;

    return 0;
}
