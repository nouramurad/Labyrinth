#pragma once
#include "updateable.h"
#include "renderable.h"
#include "World.h"
#include "Player.h"
#include "Motorcycle.hpp"
class Room;
class Model
{
public:
	Model();
	~Model();
	
	void update(sf::Time deltaTime);
	Player* getPlayer() { return player; }
	std::vector<renderable*>* getRenderables();
	void addRenderable(renderable* obj);

	std::vector<updateable*>* getUpdatables();
	void addUpdateable(updateable* obj);
	World* getWorld() { return world; }

private:
	Player* player;
	//Room room;

	World* world;


	std::vector<updateable*>* updateables;
	std::vector<renderable*>* renderables;
	
};

