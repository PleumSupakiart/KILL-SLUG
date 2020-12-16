#pragma once
#include <SFML/Graphics.hpp>
class bulletEnemy
{
public:
    bulletEnemy(sf::Texture* texture, float speed, float posx, float posy, float dirx, float diry, sf::Vector2f scale);

    ~bulletEnemy();

    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }
    void setPosition(float x, float y);
    sf::Vector2f getPosition() { return body.getPosition(); }

    void Update();
    void Render(sf::RenderWindow& window);

private:

    sf::Vector2f scale;
    float speed;
    sf::RectangleShape body;
    sf::Vector2f direction;
    sf::Vector2f velocity;

};

