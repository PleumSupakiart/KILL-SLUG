#pragma once
#include "Plane.h"

#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 3
class Menu
{
public:
	Menu(float width, float height);
	~Menu();


	Plane* leaderboard;
	sf::Text playerText;
	sf::Text enter;
	sf::RectangleShape textBox;
	sf::RectangleShape textPlane;
	sf::RectangleShape textCursor;

	sf::Vector2f windowSize;
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void updateName();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;


	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

