#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include <SFML/Audio.hpp>

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
    ~Player();

    bool getFaceRight();
    void decreaseHP(int x);
    void setHP(int x);
    void Update(float deltatime);
    void Draw(sf::RenderWindow& window);
    void onCollision(sf::Vector2f direction);
    void setPosition(float x, float y);
    int getHP();
    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    sf::Vector2f getPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }





private:

    Animation animation;
    int HP;
    unsigned int row;
    float speed;
    bool faceRight;
    sf::RectangleShape body;
    sf::SoundBuffer soundJump;
    sf::Sound sJump;
    sf::Clock damageClock;

    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
};