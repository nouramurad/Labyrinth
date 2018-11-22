#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Model.h"
#include "View.h"
class Controller
{
public:
	Controller(Model* model, View* view);
	~Controller();

	void input();

private:
	Model* model;
	View* view;
	sf::Vector2f delta;
	bool spacePressed;
	bool enterPressed;
	bool Wpressed;
	bool Spressed;
	sf::Event event;
	bool motorcycleAct;
	bool mPressed;
};

