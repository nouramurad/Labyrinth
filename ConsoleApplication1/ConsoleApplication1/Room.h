#pragma once
#include <stdlib.h>  
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Keys.h"
#include "Motorcycle.hpp"
#include "Enemy.h"
#include "Gas.hpp"
#include "HealthPack.hpp"
//#include "Motorcycle.hpp"
using namespace std;
class Room : public updateable, public renderable
{
public:
	Room(sf::Color color, sf::Vector2f position, sf::Vector2f size, int roomNumber);
	~Room();

	void setRoom(sf::RectangleShape room);
	void setRoom(sf::Color color, sf::Vector2f position, sf::Vector2f size);

	bool checkIsInRoom(sf::Vector2f position, float angle, sf::Vector2f size);
	bool Room::checkIsInRoom(sf::Vector2f position);
	bool intersects(Room* otherRoom);

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* window);
	// getters
	sf::Vector2f getCenter() { return  center; };
	sf::Vector2f getSize() { return  size; };
	sf::Vector2f getPosition() { return  topLeft; };
	sf::Color getColor() { return color; };
	int getRoomNumber() { return roomNumber;	};
	bool isLocked() { return locked; };
	std::vector<Enemy*> getEnemies() { return enemies; };

	// setters
	void lock(bool b);

	// Enemy
	void addEnemy(Enemy* enemy);
	Enemy* getFirstEnemy();
	void updateEnemyAi(bool playerClose);

	//Iems
	void addItem(Item* item);
	void addItems(std::vector<Item*> item);
	bool removeItem(Item* item);
	Keys* getKey() { return key; };
	
	std::vector<Item*> pickUpItems();
	void playerEntered(Player* player);

	Gas* getGas() { return gas; };
	HealthPack* getHealthPack() { return healthPack; };

	int getInventorySize() { return items.size(); };

private:
	sf::Color color;
	sf::RectangleShape room;
	float x1, x2, y1, y2;
	float height, width;

	sf::Vector2f center;
	sf::Vector2f size;
	sf::Vector2f topLeft;

	int roomNumber;
	std::vector<Item*> items;
	std::vector<Enemy*> enemies;
	Keys* key;
	//Motorcycle* motorcycle;
	bool locked;
	Gas* gas;

	//Health
	HealthPack* healthPack;
	
	int numEnemies;
};

