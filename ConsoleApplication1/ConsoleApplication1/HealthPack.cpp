#include "HealthPack.hpp"
#include "Room.h"
#include "Player.h"


HealthPack::HealthPack(Room* room)
{
	Item::init(room, 1, "health ", room->getColor(), room->getCenter(), sf::Vector2f(1, 1), "data/HealthPack.png"); // testing
	health = 5;
}


HealthPack::~HealthPack()
{
}
float HealthPack::getHealth()
{
	return health;
}
