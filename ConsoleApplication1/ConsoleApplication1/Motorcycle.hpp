#pragma once
#include "Item.h"
class Room;
class Player;
class Motorcycle : public Item
{
public:
	Motorcycle();
	Motorcycle(Room* room);
	~Motorcycle();
	string getDescription();
	void setSpeed(float speed);
	void update(sf::Time deltaTime);
	float getFuel();
	void addFuel(float);
private:
	void updateFuel(float speed);
	float Fuel;
	string describtion;
	float currentSpeed;

};

