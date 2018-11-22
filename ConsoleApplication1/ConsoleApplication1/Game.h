#pragma once
#include <SFML/Graphics.hpp>
#include "updateable.h"
#include "renderable.h"
#include <stdlib.h>     /* srand, rand */
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "Menu.h"
using namespace std;
class Game
{
public:
	Game();
	~Game();
	void loop();


private:
	Menu* menu;
	Model* model;
	View* view;
	Controller* controller;
	sf::Clock clock;
	sf::Clock timer;
};

