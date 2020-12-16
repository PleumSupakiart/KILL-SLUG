#include "bulletEnemy.h"
#include <iostream>
#include "Animation.h"
#include "Enemy.h"
#include <vector>
bulletEnemy::bulletEnemy(sf::Texture* texture, float speed, float posx, float posy, float dirx, float diry, sf::Vector2f scale)
{
    this->scale = scale;
    this->speed = speed;
    body.setSize(sf::Vector2f(20, 20));
    body.setOrigin(body.getSize() / 2.0f);
    body.setScale(scale);
    body.setTexture(texture);
    body.setPosition(posx, posy);
    this->direction.x = dirx;
    this->direction.y = diry;
}
bulletEnemy::~bulletEnemy()
{

}

void bulletEnemy::Update()
{
    this->body.move(this->direction * this->speed);
}

void bulletEnemy::Render(sf::RenderWindow& window)
{
    window.draw(this->body);
}
void bulletEnemy::setPosition(float x, float y)
{
    body.setPosition(x, y);
}


