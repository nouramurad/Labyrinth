#pragma once
#include <SFML/Graphics.hpp>
class renderable
{
public:
	renderable();
	virtual ~renderable();

	virtual void render(sf::RenderWindow* window);
};

