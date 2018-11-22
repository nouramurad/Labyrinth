#include "Room.h"
#include "Player.h"
#include <iostream>
Room::Room(sf::Color color, sf::Vector2f position, sf::Vector2f size,int roomNumber)
{
	room.setPosition(position);
	room.setSize(size);
	this->color = color;
	room.setFillColor(sf::Color::Transparent);

	x1 = position.x;
	x2 = position.x + size.x;
	y1 = position.y;
	y2 = position.y + size.y;
	height = size.y;
	width = size.x;

	center = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);
	this->size = size;
	topLeft = position;

	numEnemies = 0;
	locked = false;
	this->roomNumber = roomNumber;

	this->key = new Keys(this);


	this->gas = new Gas(this);

	this->healthPack = new HealthPack(this);
	
	//room.setOutlineThickness(5);
	room.setOutlineColor(sf::Color::Green);
	
}

Room::~Room()
{
	for each (GameObject* obj in items)
	{
		obj->~GameObject();
	}
	for each (GameObject* obj in enemies)
	{
		obj->~GameObject();
	}
}

/*void Room::addWall(sf::RectangleShape wall) {
walls.push_back(wall);
}

void Room::addDoor(sf::RectangleShape door) {
doors.push_back(door);
}

void Room::addWall(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
sf::RectangleShape wall;
wall.setPosition(position);
wall.setSize(size);
wall.setFillColor(color);
addWall(wall);
}

void Room::addDoor(sf::Vector2f position, sf::Vector2f size) {
sf::RectangleShape door;
door.setPosition(position);
door.setSize(size);
door.setFillColor(sf::Color::Red);
addDoor(door);
}

bool Room::checkCollision(sf::Vector2f position, float radius) {
bool ret;
for (int i = 0; i < walls.size(); i++) {
if (walls.at(i).getPosition().x < position.x + radius &&
walls.at(i).getPosition().x + walls.at(i).getSize().x > position.x &&
walls.at(i).getPosition().y < position.y + radius &&
walls.at(i).getPosition().y + walls.at(i).getSize().y > position.y) {
return true;
}

}
return false;
}*/

void Room::setRoom(sf::RectangleShape room) {
	this->room = room;
}

void Room::setRoom(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
	room.setPosition(position);
	room.setSize(size);
	this->color = color;
	room.setFillColor(sf::Color::Transparent);
	//room.setFillColor(sf::Color::Transparent);

	x1 = position.x;
	x2 = position.x + size.x;
	y1 = position.y;
	y2 = position.y + size.y;
	height = size.y;
	width = size.x;

	center = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);
	this->size = size;
	topLeft = position;



	
}

void Room::lock(bool b) {
	locked = b;
	if (locked) {
		room.setOutlineThickness(10);
		room.setOutlineColor(sf::Color::White);
	}
	else
		room.setOutlineThickness(0);
}

bool Room::checkIsInRoom(sf::Vector2f position, float angle, sf::Vector2f size) {

	sf::Transform downMat = sf::Transform::Identity;
	sf::Transform rightMat = sf::Transform::Identity;
	sf::Transform rotMat = sf::Transform::Identity;
	rotMat.rotate(angle);
	downMat.translate(sf::Vector2f(0, size.y));
	rightMat.translate(sf::Vector2f(size.x, 0));
	sf::Vector2f origin =sf::Vector2f(0, 0);

	return (checkIsInRoom(position ) &&// top left
		checkIsInRoom(rightMat*rotMat *origin + position) && // top right
		checkIsInRoom(downMat*rightMat*rotMat *origin + position) && //btoom right
		checkIsInRoom(downMat*rotMat *origin + position));// bottom left
}

bool Room::checkIsInRoom(sf::Vector2f position) {
	if (room.getPosition().x < position.x &&
		room.getPosition().x + room.getSize().x > position.x &&
		room.getPosition().y < position.y &&
		room.getPosition().y + room.getSize().y > position.y) {
		return true;
	}
	return false;
}

void Room::playerEntered(Player* player) {
	//bool playerHasKey = false;
	if (!player->hasItem(key)) {
		lock(true);
		enemies.at(0)->pickUp(key);
		player->setTrapped(true);
	}

}

bool Room::intersects(Room* otherRoom) {
	return (x1 <= otherRoom->x2 && x2 >= otherRoom->x1 &&
		y1 <= otherRoom->y2 && otherRoom->y2 >= otherRoom->y1);
}

void Room::addEnemy(Enemy* enemy) {
	numEnemies++;
	enemies.push_back(enemy);
	
}

Enemy* Room::getFirstEnemy() {
	return enemies.front();
}

void Room::updateEnemyAi(bool playerClose) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->playerClose(playerClose);
	}
}

void Room::addItem(Item* item) {
	items.push_back(item);
	item->setPosition(center);
	
}

void Room::addItems(std::vector<Item*> coll) {
	for each (Item* item in coll)
	{
		addItem(item);
	}
}

bool Room::removeItem(Item* item) {
	for (int i=0; i < items.size(); i++) {
		if (items.at(i) == item) {
			items.erase(items.begin() + i);
			return true;
		}

	}
	return false;
}

std::vector<Item*> Room::pickUpItems() {
	std::vector<Item*> i = items;
	items.clear();
	return i;
}


void Room::update(sf::Time deltaTime) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->runAI();
		enemies.at(i)->update(deltaTime);
	}
}

void Room::render(sf::RenderWindow* window) {
	window->draw(room);

	sf::RectangleShape outline;
	outline.setPosition(topLeft);

	for (int i = 0; i < items.size(); i++) {
		items.at(i)->render(window);
	}

	for (int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->render(window);
	}
}