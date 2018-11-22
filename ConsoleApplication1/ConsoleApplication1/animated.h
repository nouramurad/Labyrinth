#pragma once
#include "SFML/Graphics.hpp"
#include "renderable.h"
#include <iostream>

class animated : public renderable
{
public:
	animated();
	~animated();

	bool setTexture(std::string fileName, sf::Vector2f scale);
	void setFrame(sf::Time deltaTime, sf::Vector2f direction);
	void setPosition(sf::Vector2f pos);

	void move(sf::Vector2f delta);
	void rotate(float radians);

	sf::Sprite* getSprite() { return &sprite; };
	sf::Vector2f getSize() { return size; };
	void render(sf::RenderWindow* window);


private:

	enum Frames { STOP, RIGHT1, RIGHT2, LEFT1, LEFT2, UP1, UP2, DOWN1, DOWN2, Count };
	Frames currentFrame;
	sf::Time currentFrameTime;
	sf::Sprite sprite;
	std::vector <sf::Texture> textures;
	sf::Vector2f size;
};

