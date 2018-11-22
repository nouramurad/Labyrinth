#include "Controller.h"



Controller::Controller(Model* model, View* view)
{
	this->model = model;
	this->view = view;
}


Controller::~Controller()
{
}

void Controller::input() {
	
	delta = sf::Vector2f(0, 0);
	spacePressed = false;
	enterPressed = false;
	motorcycleAct = false;
	Wpressed = false;
	Spressed = false;
	while (view->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			view->getWindow()->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//playerPos.y -= playerSpeed;
		delta += sf::Vector2f(0, -1);
		if(model->getPlayer()->getState() == Ride)
			Wpressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//playerPos.y += playerSpeed;
		delta += sf::Vector2f(0, 1);
		if (model->getPlayer()->getState() == Ride)
			Spressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//playerPos.x -= playerSpeed;
		delta += sf::Vector2f(-1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//playerPos.x += playerSpeed;
		delta += sf::Vector2f(1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		spacePressed = true;
		if (model->getPlayer()->getState() == Ride)
		{
			spacePressed = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		enterPressed = true;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		mPressed = true;
		if (motorcycleAct)
		{
			motorcycleAct = false;
		}
		else if (!motorcycleAct)
		{
		//	mPressed = false;
			//if(model->getPlayer()->hasItem(model->getWorld()->getMotorcycle()))
				motorcycleAct = true;
		}
		
	//	model->getPlayer()->Rider(motorcycleAct);
	}
	else if (mPressed == true) {
		mPressed = false;
		if (model->getPlayer()->hasItem(model->getWorld()->getMotorcycle()))
		{
			model->getPlayer()->Rider(mPressed);
			//std::cout << mPressed << "we are here"<< std::endl;
		}

	}

	
	model->getPlayer()->setAttack(spacePressed);
	model->getPlayer()->setBreaks(spacePressed);
	model->getPlayer()->setOffset(delta);
	model->getPlayer()->setPickUP(enterPressed);
//	model->getPlayer()->Rider(motorcycleAct);
	model->getPlayer()->moveDown(Spressed);
	model->getPlayer()->moveUp(Wpressed);
}