#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 2
class RestartMenu
{
public:
	RestartMenu(float width, float height);
	~RestartMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;


	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

