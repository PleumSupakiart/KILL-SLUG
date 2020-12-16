#include "Menu.h"

Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("font/metalslug.ttf"))
	{
		//handel error
	}
	sf::Vector2f posMid = sf::Vector2f(width / 2 - this->playerText.getGlobalBounds().width / 2, height / 2 - this->playerText.getGlobalBounds().height / 2);

    this->leaderboard = new Plane(width/ 2 - 200.f, height/ 2 -200.f, 400.f, 400.f, &this->font, 48, 48);


	this->enter.setString("Press Enter to Start");
	this->enter.setFont(this->font);
	this->enter.setCharacterSize(48);
	this->enter.setOutlineColor(sf::Color::Black);
	this->enter.setOutlineThickness(1.f);
	this->enter.setFillColor(sf::Color::Green);
	this->enter.setPosition(width / 2 - this->enter.getGlobalBounds().width/2 - 40.f, height / 2 - 100.f);

	this->windowSize = sf::Vector2f(width, height);

		this->playerText.setCharacterSize(48);
	this->playerText.setOutlineColor(sf::Color::Black);
	this->playerText.setOutlineThickness(1.f);
	this->playerText.setFillColor(sf::Color::White);
	this->playerText.setFont(this->font);
	this->playerText.setPosition(posMid.x - 180.f + 2.f - 50.f + 5.f, posMid.y );

	this->textBox.setSize(sf::Vector2f(360.f + 20.f, playerText.getGlobalBounds().height + 50.f));
	this->textBox.setOutlineThickness(2.f);
	this->textBox.setOutlineColor(sf::Color::Black);
//	this->textCursor.setFillColor(sf::Color::Black);

	this->textBox.setPosition(sf::Vector2f(posMid.x - 180.f - 50.f - 10.f +5.f, posMid.y+10.f));
//	this->textCursor.setPosition(sf::Vector2f(posMid.x - 300.f + 2.f, posMid.y + 2.f));


	menu[0].setFont(font);
	menu[0].setCharacterSize(60);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(650,  400));

	menu[1].setFont(font);
	menu[1].setCharacterSize(60);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Score Board");
	menu[1].setPosition(sf::Vector2f(550, 500));

	menu[2].setFont(font);
	menu[2].setCharacterSize(60);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(650, 600));

	/*menu[3].setFont(font);
	menu[3].setCharacterSize(60);
	menu[3].setFillColor(sf::Color::Red);
	menu[3].setOutlineColor(sf::Color::Yellow);
	menu[3].setOutlineThickness(3);
	menu[3].setString("ioi");
	menu[3].setPosition(sf::Vector2f(650, 100));*/

	selectedItemIndex = 0;
}

Menu::~Menu()
{

}
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setOutlineColor(sf::Color::Transparent);
		menu[selectedItemIndex].setOutlineThickness(0);
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menu[selectedItemIndex].setOutlineThickness(5);


	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setOutlineColor(sf::Color::Transparent);
		menu[selectedItemIndex].setOutlineThickness(0);
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		menu[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menu[selectedItemIndex].setOutlineThickness(5);

	}
}

void Menu::updateName()
{
	//this->playerText.setPosition(this->windowSize.x/ 2 - this->playerText.getGlobalBounds().width/2, this->windowSize.y/2 - this->playerText.getGlobalBounds().height/2);
	//this->textCursor.setPosition(this->playerText.getPosition().x + this->playerText.getGlobalBounds().width + 2.f, this->textCursor.getPosition().y + 2.f);
}
