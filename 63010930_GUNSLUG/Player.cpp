#include "Player.h"
#include "Animation.h"
#include <iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    this->canJump = false;
    this->row = 0;
    this->faceRight = true;
    this->HP = 100;




    body.setSize(sf::Vector2f(120,120));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(0.f, 0.f);
    body.setScale(1.0, 1.0);
    body.setTexture(texture);
    //Sound
    soundJump.loadFromFile("JumpSOUND.wav");
    sJump.setBuffer(soundJump);
    sJump.setVolume(15.0);
    //Jump



}

Player::~Player()
{

}

bool Player::getFaceRight()
{
    return this->faceRight;
}

void Player::decreaseHP(int x)
{
    this->HP -= x;
    if (x >= 0)
    {
        body.setFillColor(sf::Color(255, 0, 0, 100));
    }

    if (x < 0)
    {

        body.setFillColor(sf::Color(0, 255, 0, 100));
    }
    this->damageClock.restart();
}

void Player::setHP(int x)
{
    this->HP = x;
}

void Player::Update(float deltaTime)
{
    std::cout << body.getPosition().x << " " << body.getPosition().y << "\n";

    velocity.x *= 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;

        if (velocity.y > 0 || velocity.y < 0)
        {
            row = 2;
        }

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
        if (velocity.y > 0 || velocity.y < 0)
        {
            row = 2;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump)
    {

        sJump.play();
        velocity.y = -sqrt(5.0f * 980.0f * jumpHeight);
        canJump = false;

    }
    velocity.y += 3 * 981.0f * deltaTime;


    if (velocity.x == 0.0f)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            row = 3;
        }

        else
        {
            row = 0;
        }
    }
    if (velocity.x != 0.0f)
    {
        row = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            row = 4;
        }
        if (velocity.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    if (this->damageClock.getElapsedTime().asSeconds() >= 0.2f)
    {
        body.setFillColor(sf::Color(255, 255, 255, 255));

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        row = 2;
    }




    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);

    body.move(velocity * deltaTime);

}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Player::onCollision(sf::Vector2f direction)
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

void Player::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

int Player::getHP()
{
    return this->HP;
}
