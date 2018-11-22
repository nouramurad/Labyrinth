#include "Item.h"
#include <iostream>

Item::Item()
{}
Item::Item(Room* room, int numSlots, string description, sf::Color color, sf::Vector2f position, sf::Vector2f size, string texLoc)
{
	this->room = room;
	this->slots = numSlots;
	this->description = description;
	this->color = color;
	this->position = position;
	this->size = size;
	this->texLoc = texLoc;

	GameObject::init(position, size, texLoc);
	GameObject::setColor(color);
}

/*Item::Item(Enemy* enemy, int numSlots, string description, sf::Color color)
{
	this->enemy = enemy;
	this->slots = numSlots;
	this->description = description;
	this->color = color;
}*/

void Item::init(Room* room, int numSlots, string description, sf::Color color, sf::Vector2f position, sf::Vector2f size, string texLoc) {
	this->room = room;
	this->slots = numSlots;
	this->description = description;
	this->color = color;
	this->position = position; 
	this->size = size;
	this->texLoc = texLoc;
	GameObject::init(position, size, texLoc);
}
Item::~Item()
{
}

int Item::numSlots() { 
	return slots; 
}