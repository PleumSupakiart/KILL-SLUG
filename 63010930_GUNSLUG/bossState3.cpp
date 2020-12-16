#include "BossState3.h"
#include "bossState2.h"
#include "Boss.h"
#include "Enemy.h"
#include "Animation.h"
#include "bulletEnemy.h"
#include "Birdstate3.h"

#include <iostream>
BossState3::BossState3(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)

{

    this->initTexture();
    this->speed = speed;
    row = 0;
    faceRight = true;

    this->hp = 40;

    body.setSize(sf::Vector2f(30 * 1.5 * 3 * 1.5, 26 * 1.5 * 4 * 1.5));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(1.0, 1.0);
    body.setTexture(texture);
    body.setPosition(position);
    //Sound
    soundJump.loadFromFile("JumpSOUND.wav");
    sJump.setBuffer(soundJump);
    sJump.setVolume(15.0);

    r = 0;



}

BossState3::~BossState3()
{
    for (auto* i : this->bullets)
    {
        delete i;
    }
}

void BossState3::setHP(int x)
{
    this->hp -= x;
    body.setFillColor(sf::Color(255, 0, 0, 150));
    this->damageClock.restart();
}

int BossState3::getHP()
{
    return this->hp;
}


void BossState3::Update(float deltaTime, Player* player)
{
    srand(time(0));
    r = rand() % 3;




    velocity.x *= 0.0f;
    velocity.y *= 0.0f;
    if (body.getPosition().x - player->getPosition().x >= 0)
    {
        body.setScale(1.0, 1.0);
        body.setOrigin(body.getSize() / 2.0f);
       


         if (r == 1 && clockShoot1.getElapsedTime().asSeconds() >= 0.7)
        {
            clockShoot1.restart();
            velocity.y += speed;
            row = 0;
            bullets.push_back(new bulletEnemy(&bulletTexture, 20.0f, body.getPosition().x, body.getPosition().y, -1.0f, 0.0f, sf::Vector2f(1.5f, 1.5f)));

        }
        else if (r == 2)
        {

            velocity.y += speed;
            velocity.x -= speed;
            row = 2;

        }


    }
    if (body.getPosition().x - player->getPosition().x <= 0)
    {
        body.setScale(-1.0, 1.0);
        body.setOrigin(body.getSize() / 2.0f);
        if (r == 0 /*&& clockShoot2.getElapsedTime().asSeconds() >= 0.7*/)
        {
            /*clockShoot2.restart();*/
            velocity.y -= speed;

            row = 1;
            /* bullets.push_back(new bulletEnemy(&bulletTexture, 20.0f, body.getPosition().x, body.getPosition().y, 1.0f, 0.0f, sf::Vector2f(2.0f, 2.0f)));*/

        }


        else if (r == 1 && clockShoot3.getElapsedTime().asSeconds() >= 0.7)
        {
            clockShoot3.restart();
            velocity.y += speed;
            row = 0;
            bullets.push_back(new bulletEnemy(&bulletTexture, 20.0f, body.getPosition().x, body.getPosition().y, 1.0f, 0.0f, sf::Vector2f(1.f, 1.f)));


        }
        else if (r == 2)
        {

            velocity.y += speed;
            velocity.x += speed;
            row = 2;

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
    for (auto* bird : bird)
    {
        if (player->GetGlobalBounds().intersects(bird->GetGlobalBounds()))
        {

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






    /*if (velocity.x == 0.0f)
    {
        row = 0;
    }*/
    //if (velocity.x != 0.0f)
    //{
    //    /*row = 0;*/
    //    if (velocity.x > 0.0f)
    //        faceRight = false;
    //    else
    //        faceRight = true;
    //}

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    this->updateBullet();
    for (auto* bird : bird)
        bird->Update(deltaTime);

    body.move(velocity * deltaTime);


}

void BossState3::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    this->DrawBullet(window);
}

void BossState3::DrawBullet(sf::RenderWindow& window)
{
    for (auto* bullet : bullets)
        bullet->Render(window);
    for (auto* bullet : bullet)
        bullet->Render(window);
    for (auto* bird : bird)
        bird->Draw(window);
}

void BossState3::onCollision(sf::Vector2f direction)
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

void BossState3::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void BossState3::updateBullet()
{
    for (auto* bullet : bullets)
        bullet->Update();
    for (auto* bullet : bullet)
        bullet->Update();

}



void BossState3::initTexture()
{
    this->bulletTexture.loadFromFile("bulletboss3.png");
   

}




