#pragma once
#include "Item.h"
class Room;
class Keys : public Item
{
public:
	Keys();
	Keys(Room* room);
	~Keys();
	
};

