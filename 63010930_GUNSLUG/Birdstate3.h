#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include <SFML/Audio.hpp>
#include "bulletEnemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
class Birdstate3
{
public:
    Birdstate3(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f scale);
    ~Birdstate3();

    void setHP(int x, bool isBonus);

    int getHP();

    void Update(float deltatime);
    void Draw(sf::RenderWindow& window);

    void setPosition(float x, float y);

    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    sf::Vector2f getPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }




private:
    std::vector<bulletEnemy*> bullets;
    Animation animation;
    unsigned int row;
    unsigned int stop;
    float speed;
    bool faceRight;
    sf::Vector2f scale;
    sf::RectangleShape body;
    sf::RectangleShape bulletTex;
    sf::SoundBuffer soundEnemyShoot;
    sf::Sound sShoot;
    sf::Clock clockShoot;
    sf::Clock damageClock;
    sf::Clock damageBonusClock;

    int hp;
    float speedBullet;
    bool isDead;
    bool isFinishAnim;
    bool red;
    bool blue;

    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;

    sf::Texture bulletTexture;


};

