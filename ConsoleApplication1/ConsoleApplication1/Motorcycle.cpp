#include "Motorcycle.hpp"
#include "Room.h"
#include "Player.h"
#include <iostream>



Motorcycle::Motorcycle(Room* room)
{
	Fuel = 10.0;
	describtion = "MotorCycle \nFuel: " + std::to_string(Fuel) + "% \nCurrentSpeed: " + std::to_string(currentSpeed);
	Item::init(room, 1, describtion, room->getColor(), room->getCenter(), sf::Vector2f(0.15, 0.2), "data/motorcycle.png"); // testing
}

Motorcycle::Motorcycle()
{
	
}

Motorcycle::~Motorcycle()
{
}
string Motorcycle::getDescription()
{
  return describtion;
}
void Motorcycle::setSpeed(float speed)
{
	currentSpeed = speed;
}
float Motorcycle::getFuel()
{
	return Fuel;
}
void Motorcycle::updateFuel(float speed)
{
	if (Fuel > 0)
		Fuel -= 0.005 *abs(speed);
	else {
		Fuel = 0;
		currentSpeed = 0;
	}
}
void Motorcycle::addFuel(float gas)
{
	Fuel += gas;
	if (Fuel > 100)
		Fuel = 100;
}
void Motorcycle::update(sf::Time deltaTime)
{
	updateFuel(currentSpeed);
	describtion = "MotorCycle \nFuel: " + std::to_string(Fuel) + "% \nCurrentSpeed: " + std::to_string(abs(currentSpeed));
}

