#include "Keys.h"
#include "Room.h"
Keys::Keys()
{
}
Keys::Keys(Room* room)
{
	Item::init(room, 1, "Key ",room->getColor(), room->getCenter(), sf::Vector2f(1,1), "data/keydemo.png"); // testing
}
Keys::~Keys()
{
}

