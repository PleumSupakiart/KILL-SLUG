#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class item
{
public:
    item(sf::Texture* texture, float posx, float posy, sf::Vector2u imageCount, float switchTime, std::string type, sf::Vector2f size);

    ~item();

    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    void setPosition(float x, float y);
    sf::Vector2f getPosition() { return body.getPosition(); }
    std::string getType();


    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);

private:

    Animation animation;

    std::string type;
    unsigned int row;
    unsigned int stop;
    sf::Vector2f size;
    float speed;
    bool faceRight;
    sf::RectangleShape body;
    sf::Vector2f direction;
    sf::Vector2f velocity;

};


