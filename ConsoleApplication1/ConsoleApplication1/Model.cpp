#include "Model.h"

Model::Model()
{
	updateables = new std::vector<updateable*>();
	renderables = new std::vector<renderable*>();
	world = new World();
	
	player = new Player(world);
	world->setPlayer(player);
	while (world->getNumLockedRooms() < 5) {
		cout << "palceRooms\n";
		world->placeRooms(player->getColor());
	}
	
	world->placeEnemies();

	updateables->push_back(world->getMotorcycle());
	updateables->push_back(world);
	renderables->push_back(world);
	updateables->push_back(player);
	renderables->push_back(player);
	
	player->setPosition(world->getCurrentRoom()->getCenter());

	player->pickUp(world->getCurrentRoom()->getKey());

	cout << world->getCurrentRoom()->getCenter().x << ", " << world->getCurrentRoom()->getCenter().y << "\n";
}


Model::~Model()
{
}

std::vector<renderable*>* Model::getRenderables() {
	return renderables;
}

void Model::addRenderable(renderable* obj) {
	renderables->push_back(obj);
}

std::vector<updateable*>* Model::getUpdatables() {
	return updateables;
}

void Model::addUpdateable(updateable* obj) {
	updateables->push_back(obj);
}

void Model::update(sf::Time deltaTime) {
	for each (updateable* obj in *updateables)
	{
		obj->update(deltaTime);
	}
	//cout << world->getMotorcycle()->getDescription() << endl;

}