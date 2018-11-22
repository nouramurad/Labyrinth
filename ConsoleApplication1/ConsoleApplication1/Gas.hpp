#pragma once
#include "Item.h"
class Room;
class Player;
class Gas : public Item
{
public:
	Gas(Room* room);
	~Gas();
	float getFuel();
private:
	float Fuel;
};

