#pragma once
#include "updateable.h"
#include "renderable.h"
#include "animated.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

class World;
class Item;
class Enemy;
class Motorcycle;
enum MoveState { Walk, Ride, Attack, Dead };
class Player: public updateable,  public renderable, public animated
{
public:
	//yea?
	Player(World* world);
	~Player();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* window);

	// setters
	void setOffset(sf::Vector2f delta);
	void setPosition(sf::Vector2f pos);
	
	void setPickUP(bool b);
	bool pickUp(Item* item);
	std::vector<Item*> pickUp(std::vector<Item*> items);
	
	void setAttack(bool attack);

	void setBreaks(bool breaks);
	void setTrapped(bool b) { trapped = b; };

	//getters
	float getSpeed();
	sf::Vector2f getPosition() { return position; };
	float getRadius() { return radius; };
	sf::Color getColor() { return color; };
	bool hasItem(Item* item);
	float getHeading() {return heading;	}
	void setRiding(int);
	bool getTrapped() { return trapped; };
	bool playerWon() { return wonGame; };
	bool playerLost() { return lostGame; };

	
	// combat
	// returns true if alive
	bool takeDamage(int damage);
	void heal(int health);
	void keyInRoom(int size);
	     
	//Ride
	void Rider(bool);
	void moveUp(bool);
	void moveDown(bool);
	MoveState getState();
	       
private:
	// game over
	bool lostGame;
	bool wonGame;
	bool hasAllKeys();
	int totalKeys = 5;

	//functions
	// combat
	void attack();
	void turn(float radians);
	void walk(sf::Vector2f direction);
	
	//variables
	sf::Vector2f lookAtVector;
	sf::Vector2f position;
	float radius;
	sf::CircleShape shape;
	sf::Color color;
	float speed;

	World* world;

	// input 
	sf::Vector2f offset;
	bool attackFlag;
	bool pickUpFlag;

	// combat
	int strength;
	sf::Clock attackCooldown;

	// health bar
	sf::Clock healthRegen;
	float healthRegenReset;
	float width;
	float hight;
	sf::Vector2f size;
	int health;
	const int MAX_HEALTH = 10;
	sf::RectangleShape healthBar;

	// inventory
	bool keyAvailabe;
	std::vector<Item*> inventory;
	int iventoryCapacity;
	int inventoryUsed;

	// movement
	float maxTurnSpeed; // radians
	float currentTurnSpeed;
	float heading;
	float currentSpeed;
	float maxSpeed;
	float exelSpeed;
	float currentRotation;
	MoveState moveState;
	bool trapped;

	//motorcycle 
	bool isRiding;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f sizeM;
	float decel(float exels);
	float exel(float exels);
	float coast(float exels);
	float breaks(float exels);
	bool breakFlag;

	//instructions
	sf::Font font;
	sf::Text text;
	sf::Text textI;
	sf::Text textM;

	sf::Image imaged;
	sf::Texture textured;
	sf::Sprite sprited;

	sf::Image imagea;
	sf::Texture texturea;
	sf::Sprite spritea;

};

