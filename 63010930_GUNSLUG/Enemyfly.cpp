#include "Enemyfly.h"
#include "Animation.h"
#include <iostream>
Enemyfly::Enemyfly(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->row = 0;
    this->faceRight = true;

    body.setSize(sf::Vector2f(100, 80));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(1.0, 1.0);
    body.setTexture(texture);
    body.setPosition(position);
    //Sound
    soundJump.loadFromFile("JumpSOUND.wav");
    sJump.setBuffer(soundJump);
    sJump.setVolume(15.0);
    //Jump



}

Enemyfly::~Enemyfly()
{

}

void Enemyfly::Update(float deltaTime)
{
    int r = rand() % 4;


    velocity.y *= 0.0f;


    if (r == 0 || r == 2)
    {
        velocity.y -= speed;

    }
    else if (r == 1 || r == 3)
    {
        velocity.y += speed;
    }



    if (velocity.y != 0.0f)
    {
        row = 0;
        if (velocity.y > 0.0f)
            faceRight = false;
        else
            faceRight = true;
    }
    if (velocity.x != 0.0f)
    {
        row = 0;
        if (velocity.x > 0.0f)
            faceRight = false;
        else
            faceRight = true;
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);

    body.move(velocity * deltaTime);

}
void Enemyfly::onCollision(sf::Vector2f direction)
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

    }
    else if (direction.y > 0.0f)
    {
        velocity.y = 0.0f;
    }
}

void Enemyfly::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Enemyfly::setPosition(float x, float y)
{
    body.setPosition(x, y);
}
void Enemyfly::getPosition(float x, float y)
{
    body.getPosition();
}


