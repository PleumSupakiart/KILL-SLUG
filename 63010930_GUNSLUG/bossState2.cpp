#include "bossState2.h"
#include "Boss.h"
#include "Enemy.h"
#include "Animation.h"
#include "bulletEnemy.h"

#include <iostream>
bossState2::bossState2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)
{

    this->initTexture();
    this->speed = speed;
    row = 0;
    faceRight = true;

    this->hp = 30;

    body.setSize(sf::Vector2f(120, 300));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(1.5, 1.5);
    body.setTexture(texture);
    body.setPosition(position);
    //Sound
    soundJump.loadFromFile("JumpSOUND.wav");
    sJump.setBuffer(soundJump);
    sJump.setVolume(15.0);




}

bossState2::~bossState2()
{
    for (auto* i : this->bullets)
    {
        delete i;
    }
}

void bossState2::setHP(int x)
{
    this->hp -= x;
    body.setFillColor(sf::Color(255, 0, 0, 150));
    this->damageClock.restart();
}

int bossState2::getHP()
{
    return this->hp;
}


void bossState2::Update(float deltaTime, Player* player)
{
    srand(time(0));
    int r = rand() % 3;
    sf::Time cdShoot = clockShoot.getElapsedTime();
    sf::Time cdShoot1 = clockShoot1.getElapsedTime();

    velocity.x *= 0.0f;
    if (player->getPosition().x + 900 > body.getPosition().x)
    {
        if (r == 0 && clockShoot.getElapsedTime().asSeconds() > 0.5)
        {
            clockShoot.restart();
            int counter = this->bullets.size() - 1;
            while (bullets.size() != 0)
            {
                delete this->bullets.at(counter);
                this->bullets.erase(this->bullets.begin() + counter);
                counter--;
            }

            bullet.push_back(new bulletEnemy(&bulletTexture, 10.f, rand() % 910 + 6100, 0, 0.0f, 1.0f, sf::Vector2f(1.5f, 1.5f)));
            bullet.push_back(new bulletEnemy(&bulletTexture, 10.f, rand() % 910 + 6000, 0, 0.0f, 1.0f, sf::Vector2f(1.5f, 1.5f)));
            bullet.push_back(new bulletEnemy(&bulletTexture, 10.f, rand() % 910 + 5800, 0, 0.0f, 1.0f, sf::Vector2f(1.5f, 1.5f)));
            row = 0;
        }


        else if (r == 1 && clockShoot1.getElapsedTime().asSeconds() > 0.5 || r == 2 && clockShoot1.getElapsedTime().asSeconds() > 1.0)
        {
            clockShoot1.restart();
            row = 0;
            bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 374 + 6200, 600, 0.0f, 0.0f, sf::Vector2f(6.0f, 7.0f)));
            bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 374 + 6350, 600, 0.0f, 0.0f, sf::Vector2f(6.0f, 7.0f)));
            /* bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 374 + 15606, 496, 0.0f, 0.0f, sf::Vector2f(3.0f, 5.0f)));
             bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 374 + 15606, 496, 0.0f, 0.0f, sf::Vector2f(3.0f, 5.0f)));*/
             /*bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 910 + 15194, 496, 0.0f, 0.0f, sf::Vector2f(1.0f, 2.0f)));
             bullets.push_back(new bulletEnemy(&IceTexture, 10.f, rand() % 910 + 15194, 496, 0.0f, 0.0f, sf::Vector2f(1.0f, 2.0f)));*/

        }


    }
    for (auto* bullet : bullet)
    {
        if (player->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
        {
            bullet->setPosition(-50.0f, -50.0f);
            player->decreaseHP(1);
        }

    }
    for (auto* bullet : bullets)
    {
        if (player->GetGlobalBounds().intersects(bullet->GetGlobalBounds()))
        {

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

void bossState2::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    this->DrawBullet(window);
}

void bossState2::DrawBullet(sf::RenderWindow& window)
{
    for (auto* bullet : bullets)
        bullet->Render(window);
    for (auto* bullet : bullet)
        bullet->Render(window);
}

void bossState2::onCollision(sf::Vector2f direction)
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

void bossState2::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void bossState2::updateBullet()
{
    for (auto* bullet : bullets)
        bullet->Update();
    for (auto* bullet : bullet)
        bullet->Update();
}

void bossState2::initTexture()
{
    this->bulletTexture.loadFromFile("boss/green.png");
    this->IceTexture.loadFromFile("boss/smoke.png");
}



