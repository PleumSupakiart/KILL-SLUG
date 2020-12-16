#include "RestartMenu.h"


RestartMenu::RestartMenu(float width, float height)
{
	if (!font.loadFromFile("font/metalslug.ttf"))
	{
		//handel error
	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(60);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Restart");
	menu[0].setPosition(sf::Vector2f(630, 500));

	menu[1].setFont(font);
	menu[1].setCharacterSize(60);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(680, 600));



	selectedItemIndex = 0;
}

RestartMenu::~RestartMenu()
{

}
void RestartMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
void RestartMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setOutlineThickness(0);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Transparent);
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menu[selectedItemIndex].setOutlineThickness(5);

	}
}
void RestartMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setOutlineThickness(0);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Transparent);
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menu[selectedItemIndex].setOutlineThickness(5);

	}
}
