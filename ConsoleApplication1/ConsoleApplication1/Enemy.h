#pragma once
#include "GameObject.h"
#include <iostream>
#include "animated.h"

class Room;
class Player;
class Item;
class Enemy : public GameObject, public animated
{
public:
	enum AIState { Patrol, Attack, Defeated};

	Enemy(Room* room, Player* player);
	~Enemy();

	void init(float xpos, float ypos, sf::Vector2f size, float speed, string texLoc);
	float getSpeed();

	// ai
	void runAI();
	void playerClose(bool playerClose);
	// combat
	int takeDamage(int damage); // returns remainging health
	//inventory
	void pickUp(Item* item);
	void pickUp(std::vector<Item*> items);
	bool hasItem(Item* i);
	void update(sf::Time);
	void render(sf::RenderWindow*);

private:

	//funtions
	//inventory
	void dropAll();

	// combat
	void heal(int health);
	void attack();
	void die();


	//variables
	Room* room;
	Player* player;
	std::vector<Item*> inventory;

	//combat
	int health;
	int maxHealth;
	int strength;
	sf::RectangleShape healthBar;

	sf::Clock attackCooldown;
	//movement
	sf::Vector2f direction;
	float speed;
	float heading;

	AIState aIState;

	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};

