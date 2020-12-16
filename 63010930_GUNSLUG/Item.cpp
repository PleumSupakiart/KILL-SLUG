#include "Item.h"
#include "bulletEnemy.h"
#include <iostream>
#include "Animation.h"
#include "Enemy.h"
#include <vector>
item::item(sf::Texture* texture, float posx, float posy, sf::Vector2u imageCount, float switchTime, std::string type, sf::Vector2f size) :
    animation(texture, imageCount, switchTime)
{
    this->size = size;
    body.setSize(sf::Vector2f(size));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(1.0, 1.0);
    body.setTexture(texture);
    body.setPosition(posx, posy);

    this->type = type;
}
item::~item()
{

}

void item::Update(float deltaTime)
{
    row = 0;
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);


    body.move(velocity * deltaTime);
}

void item::Render(sf::RenderWindow& window)
{
    window.draw(this->body);
}
void item::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

std::string item::getType()
{
    return this->type;
}

