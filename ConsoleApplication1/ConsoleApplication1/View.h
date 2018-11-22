#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Model.h"

class View
{
public:
	View(Model* model);
	~View();

	void render();
	sf::RenderWindow* getWindow() { return window; }
	void addRenderable(renderable* obj);
	//void addActorSprite(sf::Vector2f pos, sf::Vector2f size, int texNum);
	//void addObjectSprite(sf::Vector2f pos, sf::Vector2f size, int texNum);
	void addWorldSprite(sf::Vector2f pos, sf::Vector2f size, int texNum, sf::Color col);
	void addRooms();
	void gameOver();

private:
	sf::RenderWindow* window;
	int winW = 1280;
	int winH = 720;
	sf::Vector2f winSize;
	float centerX = (winW / 2);
	float centerY = (winH / 2);

	Model* model;
	sf::View view;
	sf::Sprite* player;

	sf::VertexArray actorVertices;
	int actorVerticesPos;
	sf::Vector2i actorTexSize;
	sf::Vector2i actorSpriteSheetSize;
	sf::RenderStates actorStates;
	sf::Texture actorTex;

	sf::VertexArray objectVertices;
	int objectVerticesPos;
	sf::Vector2i objectTexSize;
	sf::Vector2i objectSpriteSheetSize;
	sf::RenderStates objectStates;
	sf::Texture objectTex;

	sf::VertexArray worldVertices;
	int worldVerticesPos;
	sf::Vector2i worldTexSize;
	sf::Vector2i worldSpriteSheetSize;
	sf::RenderStates worldStates;
	sf::Texture worldTex;


	//endgame 
	sf::Font font;
	sf::Text text;
	sf::Event event;
	bool gameOverflag = false;

	//std::vector<sf::Sprite> worldSprites;
};

