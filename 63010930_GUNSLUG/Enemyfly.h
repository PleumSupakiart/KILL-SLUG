#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include <SFML/Audio.hpp>
class Enemyfly
{
public:
    Enemyfly(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
    ~Enemyfly();

    void Update(float deltatime);
    void Draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void getPosition(float x, float y);
    void onCollision(sf::Vector2f direction);
    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    sf::Vector2f getPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }
    sf::RectangleShape body;
    sf::SoundBuffer soundJump;
    sf::Sound sJump;




private:

    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;

    sf::Vector2f velocity;

};