#pragma once
#include "Room.h"
//#include "Motorcycle.hpp"
#include <stdlib.h>
#include <iostream>
#include "Motorcycle.hpp"
class Player;
// dungeon generation tutorial
//http://gamedevelopment.tutsplus.com/tutorials/create-a-procedurally-generated-dungeon-cave-system--gamedev-10099

class World : public updateable, public renderable
{
public:
	World();
	~World();

	//creation
	void addRoom(Room* room);
	void addRoom(sf::Color color, sf::Vector2f position, sf::Vector2f size, int roomNumber);
	void placeRooms(sf::Color playerColor);
	void createCorridor(sf::Vector2f pointA, sf::Vector2f pointB, sf::Color color,int roomNumber);
	void addCorridor(Room* corridor);
	void placeEnemies();
	void placeMotorcycle();

	// collision
	bool checkPlayerIsInRoom(sf::Vector2f position, sf::Vector2f* direction, sf::Vector2f size);
	bool checkIsInRoom(sf::Vector2f position, float angle, sf::Vector2f size);
	Room* findRoom(sf::Vector2f position, float radius);
	void unlockRoom(Room* room);

	// getters
	Room* randomRoom();
	Room* firstRoom();
	Room* getCurrentRoom();
	int getNumLockedRooms() { return lockedCount; };
	std::vector<Room*>* getRooms() { return &rooms; };
	std::vector<Room*>* getCorridors() { return &corridors; };

	Motorcycle* getMotorcycle() { return motorcycle; };

	// setters
	void setPlayer(Player* player) { this->player = player; };

	Room* getCurrentRoom(sf::Vector2f position, float angle, sf::Vector2f size);

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* window);

private:
	std::vector<Room*> rooms;
	std::vector<Room*> corridors;
	const int MIN_ROOM_SIZE = 200;
	const int MAX_ROOM_SIZE = 350;
	const int WORLD_WIDTH = 3500;
	const int WORLD_HEIGHT = 2000;
	const int NUM_ROOMS = 50;
	const float CORRIDOR_SIZE = 60;
	const int CHANCELOCKED = 33; // (out of 100) higher means more likely that rooms are locked 

	// collision
	void handleCollision(sf::Vector2f* direction);
	bool checkPoint(Room* room, sf::Vector2f position);
	sf::Vector2f topLeft, topRight, bottomLeft, bottomRight, front;
	bool  topLeftB, topRightB, bottomLeftB, bottomRightB;
	sf::Transform downMat, rightMat, rotMat;
	sf::Vector2f origin;
	Room* topLeftRoom;
	Room* topRightRoom;
	Room* bottomLeftRoom;
	Room* bottomRightRoom;

	Player* player;
	int lockedCount;

	Room* previousRoom;
	Room* currentRoom;

	Motorcycle* motorcycle;
};

