#include "GameObject.h"
#include <iostream>


GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::init(sf::Vector2f position, sf::Vector2f size, string texLoc) {
	this->position = position;
	imageLoaded = this->texture.loadFromFile(texLoc);
	this->size = size;
	this->texLoc = texLoc;

	if (!imageLoaded) {
		shape.setPosition(getPosition());
		size = sf::Vector2f(size.x * 10, size.y * 10);
		shape.setSize(size);
		shape.setFillColor(sf::Color::Green);
	}

	center = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);

	sprite.setPosition(position);
	sprite.setScale(size);
	sprite.setTexture(texture);

}

void GameObject::setPosition(sf::Vector2f position) {
	this->position = position;
	center = sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2);
	if (!imageLoaded)
		shape.setPosition(position);
	sprite.setPosition(position);
}

void GameObject::setColor(sf::Color color) {
	sprite.setColor(color);
	sprite.setTexture(texture);
}

sf::Texture* GameObject::getTexture() {
	return &texture;
}

sf::Sprite* GameObject::getSprite() {
	return &sprite;
}
sf::Vector2f GameObject::getSize() {
	return size;
}
sf::Vector2f GameObject::getPosition() {
	return position;
}

void GameObject::update(sf::Time deltaTime) {
	shape.setPosition(getPosition());
}
void GameObject::render(sf::RenderWindow* window) {
	if (!imageLoaded) {
		window->draw(shape);
	}
	else {
		window->draw(sprite);
	}
}