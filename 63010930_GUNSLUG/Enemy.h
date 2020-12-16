#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include <SFML/Audio.hpp>
#include "bulletEnemy.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
class Enemy
{
public:
    Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f scale);
    ~Enemy();

    void setHP(int x, bool isBonus);

    int getHP();

    void Update(float deltatime, Player* player, sf::Texture* bullTexture);
    void Draw(sf::RenderWindow& window);
    void DrawBullet(sf::RenderWindow& window);
    void onCollision(sf::Vector2f direction);
    void setPosition(float x, float y);
    void deadAnimation();
    void updateBullet();

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
    sf::SoundBuffer soundEnemyHit;
    sf::Sound sHit;
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

    void initTexture();
};