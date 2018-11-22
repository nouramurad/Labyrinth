#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "SFML/Graphics.hpp"
class Menu
{
public:
	Menu(sf::RenderWindow* w);
	~Menu();

	bool open();

private:
	void drawButtons();
	void controls();
	void story();
	void objective();
	void about();

	bool clicked(sf::RectangleShape button,  sf::Vector2i point);

	
	sf::RectangleShape startButton;
	sf::RectangleShape quitButton;
	sf::RectangleShape controlsButton;
	sf::RectangleShape storyButton;
	sf::RectangleShape objectiveButton;
	sf::RectangleShape aboutButton;
	sf::RectangleShape backButton;

	sf::Text startText;
	sf::Text quitText;
	sf::Text controlsText;
	sf::Text storyText;
	sf::Text objectiveText;
	sf::Text aboutText;
	sf::Text backText;

	sf::Text titleText;
	sf::Text text;

	sf::Vector2f buttonSize;
	
	sf::RenderWindow* window;
	int winW = 1280;
	int winH = 720;
	sf::Vector2f winSize;
	float centerX = (winW / 2);
	float centerY = (winH / 2);

	sf::Font font;
	sf::Font font2;
	//sf::Text text;
	sf::Event event;

	float offtext;

};

