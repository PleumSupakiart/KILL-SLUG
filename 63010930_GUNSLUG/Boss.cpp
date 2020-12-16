#include "Boss.h"
#include "Enemy.h"
#include "Animation.h"
#include "bulletEnemy.h"

#include <iostream>


Boss::Boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)
{

    this->initTexture();
    this->speed = speed;
    row = 0;
    faceRight = true;

    this->hp = 30;

    body.setSize(sf::Vector2f(65 * 2, 46 * 2));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(1.5, 1.5);
    body.setTexture(texture);
    body.setPosition(position);
    //Sound
    soundJump.loadFromFile("Player/Electric01.wav");
    sJump.setBuffer(soundJump);
    sJump.setVolume(30.0);




}

Boss::~Boss()
{
    for (auto* i : this->bullets)
    {
        delete i;
    }
}

void Boss::setHP(int x)
{
    this->hp -= x;
    body.setFillColor(sf::Color(255, 0, 0, 150));
    this->damageClock.restart();
}

int Boss::getHP()
{
    return this->hp;
}


void Boss::Update(float deltaTime, Player* player)
{
    srand(time(0));
    int r = rand() % 3;
    sf::Time cdShoot = clockShoot.getElapsedTime();
    sf::Time cdShoot1 = clockShoot1.getElapsedTime();

    velocity.x *= 0.0f;
    if (player->getPosition().x + 800 > body.getPosition().x)
    {
        if (r == 0)
        {
            clockShoot.restart();
            /*if (faceRight == false)
                bullets.push_back(new bulletEnemy(&bulletTexture, 20.f, body.getPosition().x, body.getPosition().y, 1.0f, 0.0f));
            if (faceRight == true)*/
            bullets.push_back(new bulletEnemy(&bulletTexture, 20.f, body.getPosition().x, body.getPosition().y, -1.0f, 0.0f, sf::Vector2f(4.5f, 1.0f)));
            row = 0;
        }


        else if (r == 1 && clockShoot1.getElapsedTime().asSeconds() > 0.5 || r == 2 && clockShoot1.getElapsedTime().asSeconds() > 0.5)
        {
            clockShoot1.restart();
            row = 1;
            sJump.play();
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5500, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5400, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5300, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5200, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5100, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 5000, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 4900, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 4800, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 4700, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
            bullets.push_back(new bulletEnemy(&thunderTexture, 10.f, rand() % 910 + 4600, 0, 0.0f, 1.0f, sf::Vector2f(1.0f, 2.0f)));
        }


    }
    for (auto* bullet : bullets)
    {
        if (player->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
        {
            bullet->setPosition(-50.0f, -50.0f);
            player->decreaseHP(1);
        }

    }
    if (this->damageClock.getElapsedTime().asSeconds() >= 0.1f)
    {
        body.setFillColor(sf::Color(255, 255, 255, 255));
    }

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        sJump.play();
        velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
        canJump = false;

    }*/

    /* velocity.y += 981.0f * deltaTime;*/


     /*if (velocity.x == 0.0f)
     {
         row = 0;
     }*/
     /*if (velocity.x != 0.0f)
     {
         row = 0;
         if (velocity.x > 0.0f)
             faceRight = false;
         else
             faceRight = true;
     }*/

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    this->updateBullet();

    body.move(velocity * deltaTime);


}

void Boss::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    this->DrawBullet(window);
}

void Boss::DrawBullet(sf::RenderWindow& window)
{
    for (auto* bullet : bullets)
        bullet->Render(window);
}

void Boss::onCollision(sf::Vector2f direction)
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

void Boss::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Boss::updateBullet()
{
    for (auto* bullet : bullets)
        bullet->Update();
}

void Boss::initTexture()
{
    this->bulletTexture.loadFromFile("bulletboss1.png");
    this - thunderTexture.loadFromFile("missile.png");
}


