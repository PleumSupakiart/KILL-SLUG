#include "Birdstate3.h"
#include "Enemy.h"
#include "Animation.h"
#include "bulletEnemy.h"

#include <iostream>
Birdstate3::Birdstate3(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f scale) :
    animation(texture, imageCount, switchTime)
{


    this->speed = speed;
    this->scale = scale;
    row = 0;
    faceRight = true;
    this->speedBullet = 20.f;
    this->hp = 3;
    this->isDead = false;
    this->red = false;
    this->blue = false;
    body.setSize(sf::Vector2f(80, 80));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(scale);
    body.setTexture(texture);
    body.setPosition(position);






}

Birdstate3::~Birdstate3()
{
    for (auto* i : this->bullets)
    {
        delete i;
    }
}






void Birdstate3::Update(float deltaTime)
{
    if (body.getPosition().x >= 0)
    {
        row = 0;
        body.setScale(-0.4, 0.4);
        body.setOrigin(body.getSize() / 2.0f);
        velocity.x = speed;
    }
    else
    {

        body.setScale(0.4, 0.4);
        body.setOrigin(body.getSize() / 2.0f);
        velocity.x -= speed;
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);


    body.move(velocity * deltaTime);

}

void Birdstate3::Draw(sf::RenderWindow& window)
{
    window.draw(body);

}




void Birdstate3::setPosition(float x, float y)
{
    body.setPosition(x, y);
}




