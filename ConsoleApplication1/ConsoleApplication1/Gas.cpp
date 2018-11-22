#include "Gas.hpp"
#include "Room.h"
#include "Player.h"


Gas::Gas(Room* room)
{
	Item::init(room, 1, "Gas ", room->getColor(), room->getCenter(), sf::Vector2f(1, 1), "data/gas.png"); // testing
	Fuel = 5*abs(room->getRoomNumber());
}


Gas::~Gas()
{
}
float Gas::getFuel()
{
	return Fuel;
}
