#include "Menu.h"
#include <iostream>



Menu::Menu(sf::RenderWindow* w)
{
	font.loadFromFile("ariali.ttf");
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setCharacterSize(20);
	font2.loadFromFile("PARCHM.ttf");
	

	window = w;

	offtext = 30;
	winSize = sf::Vector2f(winW, winH);

	buttonSize = sf::Vector2f(winW /10, winW/25);

	float xpos = (winW / 2) - (buttonSize.x / 2);

	startButton.setPosition(	xpos,	winH / 3 + 0 * winH / 11);
	quitButton.setPosition(		xpos,	winH / 3 + 1 * winH / 11);
	controlsButton.setPosition(	xpos,	winH / 3 + 2 * winH / 11);
	storyButton.setPosition(	xpos,	winH / 3 + 3 * winH / 11);
	objectiveButton.setPosition(xpos,	winH / 3 + 4 * winH / 11);
	aboutButton.setPosition(	xpos,	winH / 3 + 5 * winH / 11);
	backButton.setPosition(		xpos,	winH / 3 + 6 * winH / 11);

	startButton.setSize (buttonSize);
	quitButton.setSize(buttonSize);
	controlsButton.setSize(buttonSize);
	storyButton.setSize(buttonSize);
	objectiveButton.setSize(buttonSize);
	aboutButton.setSize(buttonSize);
	backButton.setSize(buttonSize);

	startButton.setFillColor(sf::Color::Red);
	quitButton.setFillColor(sf::Color::Red);
	controlsButton.setFillColor(sf::Color::Red);
	storyButton.setFillColor(sf::Color::Red);
	objectiveButton.setFillColor(sf::Color::Red);
	aboutButton.setFillColor(sf::Color::Red);
	backButton.setFillColor(sf::Color::Red);

	startText.setStyle(sf::Text::Bold);
	quitText.setStyle(sf::Text::Bold);
	controlsText.setStyle(sf::Text::Bold);
	objectiveText.setStyle(sf::Text::Bold);
	storyText.setStyle(sf::Text::Bold);
	aboutText.setStyle(sf::Text::Bold);
	backText.setStyle(sf::Text::Bold);

	startText.setFont(font2);
	quitText.setFont(font2);
	controlsText.setFont(font2);
	objectiveText.setFont(font2); 
	storyText.setFont(font2);
	aboutText.setFont(font2);
	backText.setFont(font2);
	titleText.setFont(font2);

	startText.setPosition(startButton.getPosition().x+offtext, startButton.getPosition().y- offtext/2);
	quitText.setPosition(quitButton.getPosition().x+offtext, quitButton.getPosition().y - offtext / 2);
	controlsText.setPosition(controlsButton.getPosition().x + offtext / 4, controlsButton.getPosition().y-offtext/2);
	objectiveText.setPosition(objectiveButton.getPosition().x + offtext / 8, objectiveButton.getPosition().y - offtext / 2);
	storyText.setPosition(storyButton.getPosition().x+offtext/1.5, storyButton.getPosition().y - offtext / 2);
	aboutText.setPosition(aboutButton.getPosition().x+offtext/2, aboutButton.getPosition().y - offtext / 2);
	backText.setPosition(backButton.getPosition().x+offtext, backButton.getPosition().y - offtext / 2);
	titleText.setPosition(sf::Vector2f(winW/4, 0));
	text.setPosition(sf::Vector2f(winW/4, winH/3));

	startText.setCharacterSize(50);
	quitText.setCharacterSize(50);
	controlsText.setCharacterSize(50);
	objectiveText.setCharacterSize(50);
	storyText.setCharacterSize(50);
	aboutText.setCharacterSize(50);
	backText.setCharacterSize(50);
	titleText.setCharacterSize(180);
	text.setCharacterSize(30);

	startText.setString("Start");
	quitText.setString("Quit");
	controlsText.setString("Controls");
	objectiveText.setString("Objective");
	storyText.setString("Story");
	aboutText.setString("About");
	backText.setString("Back");
	titleText.setString("The  Labyrinth");

	startText.setColor(sf::Color(192,192,192));
	quitText.setColor(sf::Color(192,192,192));
	controlsText.setColor(sf::Color(192,192,192));
	objectiveText.setColor(sf::Color(192,192,192));
	storyText.setColor(sf::Color(192,192,192));
	aboutText.setColor(sf::Color(192,192,192));
	backText.setColor(sf::Color(192,192,192));
	titleText.setColor(sf::Color::Red);
	text.setColor(sf::Color::Red);
}


Menu::~Menu()
{
}

bool Menu::open() {

	drawButtons();
	//wait for player to click

	sf::Vector2i point;

	while (true) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point = sf::Mouse::getPosition() - window->getPosition() - sf::Vector2i(0,30);

			if (clicked(startButton, point))
				return true;
			if (clicked(quitButton, point))
				return false;
			if (clicked(controlsButton, point))
				controls();
			if (clicked(storyButton, point))
				story();
			if (clicked(objectiveButton, point))
				objective();
			if (clicked(aboutButton, point))
				about();
		}	

	}

	//sf::sleep(sf::seconds(3));
	return true;
}

void Menu::drawButtons() {
	window->clear();
	window->draw(startButton);
	window->draw(quitButton);
	window->draw(controlsButton);
	window->draw(storyButton);
	window->draw(objectiveButton);
	window->draw(aboutButton);

	window->draw(startText);
	window->draw(quitText);
	window->draw(controlsText);
	window->draw(storyText);
	window->draw(objectiveText);
	window->draw(aboutText);
	window->draw(titleText);

	window->display();
}

void Menu::controls() {
	window->clear();
	window->draw(backButton);
	window->draw(backText);
	window->draw(titleText);
	// todo
	text.setString("W/S to move forward/backward.\n A/D to turn left/right.\nSpace to attack/break (when on motorcycle).\n M to enter or exit the motocycle.\nEnter to pick up Items");
	window->draw(text);
	window->display();
	sf::Vector2i point;
	while (true) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point = sf::Mouse::getPosition() - window->getPosition();
			if (clicked(backButton, point))
				break;
		}
	}
	drawButtons();
}

void Menu::story() {
	window->clear();
	window->draw(backButton);
	window->draw(backText);
	window->draw(titleText);
	// todo
	text.setString("While walking through a grassy field you fell \ninto an old mineshaft. When you landed \nyou noticed the door was locked behind you, \nand now you must find 5 keys to leave.");
	window->draw(text);
	window->display();
	sf::Vector2i point;
	while (true) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point = sf::Mouse::getPosition() - window->getPosition();
			if (clicked(backButton, point))
				break;
		}
	}
	drawButtons();

}

void Menu::objective() {
	window->clear();
	window->draw(backButton);
	window->draw(backText);
	window->draw(titleText);
	// todo
	text.setString("You must collect keys to enter locked rooms\n(outined in White).\nReturn to the start room with 5 keys to win");
	window->draw(text);
	window->display();
	sf::Vector2i point;
	while (true) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point = sf::Mouse::getPosition() - window->getPosition();
			if (clicked(backButton, point))
				break;
		}
	}
	drawButtons();
	
}

void Menu::about() {
	window->clear();
	window->draw(backButton);
	window->draw(backText);
	window->draw(titleText);
	// todo
	text.setString("Game made by Jason Kemp \nand Noura Murad for \nCOMP2501 at Carleton University");
	window->draw(text);
	window->display();
	sf::Vector2i point;
	while (true) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			point = sf::Mouse::getPosition() - window->getPosition();
			if (clicked(backButton, point))
				break;
		}
	}
	drawButtons();
	
}

bool Menu::clicked(sf::RectangleShape button, sf::Vector2i point) {
	sf::Vector2f pos = button.getPosition();
	sf::Vector2f size = button.getSize();

	std::cout << point.x << ", " << point.y << " pos = " << pos.x << ", " << pos.y << " size = " << size.x << ", " << size.y << "\n";
	if(point.x < pos.x)
		return false;
	if (point.y < pos.y)
		return false;
	if (point.x > pos.x + size.x)
		return false;
	if (point.y > pos.y + size.y)
		return false;
	std::cout << point.x << ", " << point.y << " pos = " << pos.x << ", " << pos.y << " size = " << size.x << ", " << size.y << "\n";
	return true;
}