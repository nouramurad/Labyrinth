#pragma once
#include "GameObject.h"
class Room;
class Enemy;
class Item : public GameObject
{
public:
	Item();// TESTING
	Item(Room* room, int numSlots, string description, sf::Color color, sf::Vector2f position, sf::Vector2f size, string texLoc);
	//Item(Enemy* enemy, int numSlots, string description, sf::Color color);
	void init(Room* room, int numSlots, string description, sf::Color color, sf::Vector2f position, sf::Vector2f size, string texLoc);
	~Item();

	int numSlots();
	string getDescription() { return description; };

protected:
	Room* room;
	Enemy* enemy;
	sf::Color color;
	int slots;
	string description;
	
};

