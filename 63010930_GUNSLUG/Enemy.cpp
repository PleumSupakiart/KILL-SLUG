#include "Enemy.h"
#include "Animation.h"
#include "bulletEnemy.h"

#include <iostream>
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f scale) :
    animation(texture, imageCount, switchTime)
{

    this->initTexture();
    this->speed = speed;
    this->scale = scale;
    row = 0;
    faceRight = true;
    this->speedBullet = 20.f;
    this->hp = 8;
    this->isDead = false;
    this->red = false;
    this->blue = false;
    body.setSize(sf::Vector2f(110, 110));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(scale);
    body.setTexture(texture);
    body.setPosition(position);


    //Sound
    soundEnemyShoot.loadFromFile("Player/EnemySound.wav");
    sShoot.setBuffer(soundEnemyShoot);
    sShoot.setVolume(10.0);
    soundEnemyHit.loadFromFile("Player/EnemyHit.wav");
    sHit.setBuffer(soundEnemyHit);
    sHit.setVolume(800.0);



}

Enemy::~Enemy()
{
    for (auto* i : this->bullets)
    {
        delete i;
    }
}

void Enemy::setHP(int x, bool isBonus)
{
    this->hp -= x;
    sHit.play();
    if (isBonus)
    {
        body.setFillColor(sf::Color(100, 100, 250, 200));
        speed -= speed / 2;
        speedBullet = speedBullet / 3;
        blue = true;
    }

    else
    {
        body.setFillColor(sf::Color(255, 0, 0, 150));
        red = true;
    }

    this->damageBonusClock.restart();
    this->damageClock.restart();
}

int Enemy::getHP()
{
    return this->hp;
}


void Enemy::Update(float deltaTime, Player* player, sf::Texture* bullTexture)
{
    int r = rand() % 3;
    sf::Time cdShoot = clockShoot.getElapsedTime();

    velocity.x *= 0.0f;
    if (player->getPosition().x + 700 > body.getPosition().x)
    {
        if (r == 0)
        {
            velocity.x -= speed;

        }
        else if (r == 1)
        {
            velocity.x += speed;
        }
        else if (r == 2 && cdShoot.asSeconds() >= 0.2)
        {
            clockShoot.restart();
            if (faceRight == false)
                bullets.push_back(new bulletEnemy(bullTexture, this->speedBullet, body.getPosition().x, body.getPosition().y, 1.0f, 0.0f, sf::Vector2f(1.f, 1.0f)));
            if (faceRight == true)
                bullets.push_back(new bulletEnemy(bullTexture, this->speedBullet, body.getPosition().x, body.getPosition().y, -1.0f, 0.0f, sf::Vector2f(1.f, 1.0f)));
            row = 1;
            sShoot.play();
        }
    }
    velocity.y += 981.0f * deltaTime;
    for (auto* bullet : bullets)
    {
        if (player->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
        {
            bullet->setPosition(-50.0f, -50.0f);
            player->decreaseHP(1);
        }

    }


    if (velocity.x != 0.0f)
    {
        row = 0;
        if (velocity.x > 0.0f)
            faceRight = false;
        else
            faceRight = true;
    }

    if (this->damageClock.getElapsedTime().asSeconds() >= 0.2f && red == true)
    {
        body.setFillColor(sf::Color(255, 255, 255, 255));
        red == false;
    }
    if (this->damageBonusClock.getElapsedTime().asSeconds() >= 3.0f && blue == true)
    {
        body.setFillColor(sf::Color(255, 255, 255, 255));
        speed = 100.f;
        speedBullet = 20.f;
        blue == false;
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    this->updateBullet();

    body.move(velocity * deltaTime);

}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    this->DrawBullet(window);
}

void Enemy::DrawBullet(sf::RenderWindow& window)
{
    for (auto* bullet : bullets)
        bullet->Render(window);
}

void Enemy::onCollision(sf::Vector2f direction)
{
    if (direction.x < 0.0f)
    {
        velocity.x = 0.0f;
    }
    else if (direction.x > 0.0f)
    {
        velocity.x = 0.0f;
    }
    if (direction.y < 0.0f)
    {
        velocity.y = 0.0f;
        canJump = true;
    }
    else if (direction.y > 0.0f)
    {
        velocity.y = 0.0f;
    }
}

void Enemy::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Enemy::deadAnimation()
{

}

void Enemy::updateBullet()
{
    for (auto* bullet : bullets)
        bullet->Update();
}

void Enemy::initTexture()
{
    this->bulletTexture.loadFromFile("bulletenemy.png");
}
