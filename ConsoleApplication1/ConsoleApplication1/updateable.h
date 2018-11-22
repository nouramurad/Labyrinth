#pragma once
#include <SFML/Graphics.hpp>
class updateable
{
public:
	updateable();
	virtual ~updateable();

	virtual void update(sf::Time deltaTime);
};

