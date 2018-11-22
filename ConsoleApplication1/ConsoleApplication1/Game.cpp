#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{

	model = new Model;
	view = new View(model);
	controller = new Controller(model, view);
	menu = new Menu(view->getWindow());
}


Game::~Game()
{
}


void Game::loop()
{
	if (menu->open()) {

		sf::Time deltaTime;
		sf::Time fpsMovingSum;
		while (view->getWindow()->isOpen()) {
			deltaTime = this->clock.restart();
			if (model->getPlayer()->playerWon() || model->getPlayer()->playerLost()) {
				view->gameOver();
				//break;

			}
			else {
				controller->input();
				model->update(deltaTime);
				view->render();
			}

		}
	}
}

