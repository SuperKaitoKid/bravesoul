#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Attack.h"

class GameObject{

public:
    GameObject();
    virtual ~GameObject();

    Animation getAnimation();
    void setAnimation(Animation s);

    AnimatedSprite* getAnimatedSprite();

    sf::Vector3f getPosition();
    void setPosition(sf::Vector3f vect);
    void setPosition(sf::Vector2f vect);

private:
    // Should position be stored in GO as well?
    AnimatedSprite* spr;
    Animation anim;
    std::vector<enum_effect>effects;
    sf::Vector3f position;

};

#endif // GAMEOBJECT_H
