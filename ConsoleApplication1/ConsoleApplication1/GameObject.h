#pragma once
#include "SFML/Graphics.hpp"
#include "updateable.h"
#include "renderable.h"

using namespace std;
class GameObject : public updateable, public renderable
{
public:
	GameObject();
	~GameObject();

	void init(sf::Vector2f position, sf::Vector2f size, string texLoc);
	
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* window);

	//getters
	sf::Texture* getTexture();
	sf::Sprite* getSprite();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();

	//setters
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);

protected:
	sf::Vector2f center;
	sf::Vector2f size;
	sf::Vector2f position;
	float x, y;
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	string texLoc;
	bool imageLoaded;
};

