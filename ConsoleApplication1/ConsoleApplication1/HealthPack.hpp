#pragma once
#include "Item.h"
class Room;
class Player;
class HealthPack : public Item
{
public:
	HealthPack(Room* room);
	~HealthPack();
	float getHealth();
private:
	float health;
};

