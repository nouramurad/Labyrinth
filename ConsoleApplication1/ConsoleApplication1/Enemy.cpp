#pragma once
#include "Enemy.h"
#include "Room.h"
#include"Player.h"
#include "Item.h"

Enemy::Enemy(Room* room, Player* player) {
	animated::setPosition(getPosition());
	this->room = room;
	this->player = player;
	animated::setTexture("data/zombie", sf::Vector2f(1, 1));
	image.loadFromFile("data/zombie_Dead.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	//animated::getSprite()->setRotation(atan2(1, 1)/3.14159265 *180);
	//std::cout << atan2(1, 1)/3.14159265 * 180 << " in room " << room->getRoomNumber() << "\n";
	
}
void Enemy::init(float xpos, float ypos, sf::Vector2f size, float speed, string texLoc) {
	this->speed = speed;
	this -> direction = sf::Vector2f((rand() % 100) -50, (rand() % 100)-50);
	direction = direction / sqrt(direction.x*direction.x + direction.y*direction.y);
	GameObject::init(sf::Vector2f(xpos, ypos), size, texLoc);
	aIState = Patrol;
	health = 2;
	maxHealth = 2;
	strength = 1;
	attackCooldown.restart();
	pickUp(room->pickUpItems());
	animated::getSprite()->setRotation(atan2(direction.x, direction.y) / 3.14159265 * 180);
	healthBar.setPosition(getPosition().x-10, getPosition().y - 40);
	healthBar.setSize(sf::Vector2f(21 / maxHealth, 5));
	healthBar.setFillColor(sf::Color::Yellow);

}

Enemy::~Enemy()
{
}

float Enemy::getSpeed() {
	return speed;
}

// combat
int Enemy::takeDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		die();
	}
	return health;
}
void Enemy::heal(int health) {
	this->health += health;
}
void Enemy::attack() {
	attackCooldown.restart();
	player->takeDamage(strength);
}


void Enemy::playerClose(bool playerClose) {
	if (aIState != Defeated) {
		if (playerClose) {
			aIState = Attack;

		}
		else aIState = Patrol;
	}
}

void Enemy::die() {
	aIState = Defeated;
	shape.setFillColor(sf::Color::Black);
	dropAll();
	image.loadFromFile("data/zombie_Dead.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(getPosition());
}

void Enemy::runAI() {
	if (aIState != Defeated) {
		if (aIState == Patrol) {
			if (room->checkIsInRoom(getPosition() + direction * speed,0, GameObject::getSize())) {
				GameObject::setPosition(getPosition() + direction * speed);
			}
			else {
				direction = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
				direction = direction / sqrt(direction.x*direction.x + direction.y*direction.y);
				//std::cout << atan2(direction.x, direction.y) << " in room " <<room->getRoomNumber() <<"\n";
				//std::cout << direction.x << ", " << direction.y << " in room " <<room->getRoomNumber() <<"\n";
			}
			
			//animated::rotate(90);
		}
		if (aIState == Attack) {
			direction = player->getPosition() - getPosition();
			float distance = sqrt(direction.x*direction.x + direction.y*direction.y);
			direction = direction / distance;
			if (room->checkIsInRoom(getPosition() + direction * speed, 0, GameObject::getSize())) {
				if (distance > 15) {
					GameObject::setPosition(getPosition() + direction * speed);
				}
				else{
					
					if (attackCooldown.getElapsedTime().asMilliseconds() > 2000) {
						cout << "enemy attack " << attackCooldown.getElapsedTime().asMilliseconds() << "\n";
						attack();
					}
				}
			}
			animated::setPosition(getPosition());
			
		}
		//animated::getSprite()->setRotation(atan2(direction.x, direction.y) / 3.14159265 * 180);
		//std::cout << direction.x << ", " << direction.y << "\n";
	}
	
}


void Enemy::pickUp(Item* item) {
	inventory.push_back(item);
}

void Enemy::pickUp(std::vector<Item*> items) {
	for each (Item* i in  items)
	{
		pickUp(i);
	}
}

bool Enemy::hasItem(Item* i) {
	for each (Item* item in inventory)
	{
		if (item == i)
			return true;
	}
	return false;
}

void Enemy::dropAll() {
	player->keyInRoom(inventory.size());
	room->addItems(inventory);
	inventory.clear();
}
void Enemy::update(sf::Time deltaTime)
{
	animated::setFrame(deltaTime, direction*speed);
	healthBar.setPosition(getPosition().x - 10, getPosition().y - 20);
	healthBar.setSize(sf::Vector2f(21 * health / maxHealth, 5));
	animated::setPosition(getPosition());
	animated::getSprite()->setRotation(atan2(direction.x, -direction.y) / 3.14159265 * 180);
	GameObject::getSprite()->setRotation(atan2(direction.x, -direction.y) / 3.14159265 * 180);
	GameObject::getSprite()->setOrigin(animated::getSize().x / 2, animated::getSize().y / 2);
}
void Enemy::render(sf::RenderWindow* window)
{
	if(aIState == Patrol)
		animated::render(window);
	else if (aIState == Attack)
		GameObject::render(window);
	else if (aIState == Defeated)
		window->draw(sprite);

	window->draw(healthBar);
}
