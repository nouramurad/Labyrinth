#include "Player.h"
#include "World.h"
#include "Enemy.h"
#include "Motorcycle.hpp"



Player::Player(World* world)
{
	lostGame = false;
	wonGame = false;
	color = sf::Color::Yellow;

	position.x = 30;
	position.y = 30;
	animated::setPosition(position);
	moveState = Walk;
	radius = 10;

	shape.setFillColor(color);
	shape.setRadius(radius);

	maxSpeed = 3;
	currentSpeed = 0;
	heading = 0;
	exelSpeed = 0.05f;

	

	maxTurnSpeed = 150 * 3.14159265 / 180;
	currentTurnSpeed = maxTurnSpeed;
	this->offset = sf::Vector2f(0, 0);
	this->world = world;
	this->iventoryCapacity = 20;

	// health bar
	health = MAX_HEALTH;//deacreases if the player was hit
	width = 1280 / MAX_HEALTH;
	hight = 7;
	size = sf::Vector2f(width*health, hight);
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setSize(size);

	this->strength = 1;
	attackCooldown.restart();
	healthRegenReset = 10;

	animated::setTexture("data/man", sf::Vector2f(1,1));
	keyAvailabe = false;

	font.loadFromFile("ariali.ttf");
	text.setString("press ENTER to pick up the item");
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setCharacterSize(20);
	textI.setString("Inventory");
	textI.setColor(sf::Color::White);
	textI.setFont(font);
	textI.setCharacterSize(20);
	
	image.loadFromFile("data/motorcycle.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.scale(0.2, 0.2);
	
	sizeM.x = texture.getSize().x / 2 ;
	sizeM.y = texture.getSize().y / 2 ;
	sprite.setOrigin(sizeM);
	breakFlag = false;

	imaged.loadFromFile("data/man_Dead.png");
	textured.loadFromImage(imaged);
	sprited.setTexture(textured);
	sprited.setOrigin(textured.getSize().x / 2, textured.getSize().y / 2);

	imagea.loadFromFile("data/man_Attack.png");
	texturea.loadFromImage(imagea);
	spritea.setTexture(texturea);
	spritea.setOrigin(texturea.getSize().x / 2, texturea.getSize().y / 2);

}

Player::~Player()
{
}
void Player::Rider(bool ride)
{
	if (moveState == Walk)
	{
		moveState = Ride;
		maxSpeed = 0;
	}
	else if (moveState == Ride)
	{
		moveState = Walk;
		maxSpeed = 3;
	}
}
void Player::moveUp(bool U)
{
	if(U)
		if (maxSpeed <10)
			maxSpeed = maxSpeed + exelSpeed;
}
void Player::moveDown(bool D)
{
	if(D)
		if (maxSpeed <10)
			maxSpeed = maxSpeed + exelSpeed;
}

void Player::setOffset(sf::Vector2f delta) {
	offset = delta;
	//currentRotation = delta.x * currentTurnSpeed;
	if (moveState == Walk)
	{
		currentSpeed = delta.y * maxSpeed;
		currentRotation = delta.x * currentTurnSpeed;
	}
	else if (moveState == Ride)
	{
		if (world->getMotorcycle()->getFuel() > 0)
		{
		if (breakFlag)
		{
			//cout << breakFlag << endl;
			currentSpeed = breaks(2*exelSpeed);
		}
		else if (delta.y < 0)
		{
			currentSpeed = decel(exelSpeed);
		}
		else if (delta.y == 0)
		{
			currentSpeed = coast(exelSpeed/2);
		}
		else if (delta.y > 0)
		{
			currentSpeed = exel(exelSpeed);
		}
		world->getMotorcycle()->setSpeed(currentSpeed);
	}
		else
		{
			currentSpeed = breaks(2 * exelSpeed);
		}
		if (currentSpeed != 0)
			currentRotation = delta.x * currentTurnSpeed;
		else if (currentSpeed == 0)
		{
			currentRotation = 0;
		}

	}


	
}
float Player::decel(float exels)
{
	
	currentSpeed = max(-maxSpeed, currentSpeed - exels);
	return currentSpeed;
}
float Player::exel(float exels)
{
	
	currentSpeed = min(maxSpeed / 2, currentSpeed + exels);
	return currentSpeed;
}
float Player::coast(float exels)
{
	if (currentSpeed > 0.25)
	{
		currentSpeed = max(-maxSpeed / 2, currentSpeed - exels);
	}
	else if (currentSpeed < -0.25)
	{
		currentSpeed = exel(exels);
	}
	else
	{
		currentSpeed = 0;
	}
	return currentSpeed;
}
float Player::breaks(float exels)
{
	currentSpeed = coast(2*exels);
	return currentSpeed;
}
void Player::setBreaks(bool breaks)
{
	if (breaks == true)
	{
		breakFlag = true;
	}
	else
	{
		breakFlag = false;
	}
}

void Player::setAttack(bool attack) {
	this->attackFlag = attack;
	if (attack == true)
	{
		spritea.setPosition(position);
	}
}
void Player::setPickUP(bool b) {
	pickUpFlag = b;
}
void Player::setPosition(sf::Vector2f pos) {
	this->position = pos;
}
void Player::setRiding(int check)
{
	if (check == 0)
	{
		isRiding = false;
	}
	else if (check == 1)
	{
		isRiding = true;
		//	animated::setTexture("data/alienGreen", sf::Vector2f(0.25, 0.25));
	}

}

float Player::getSpeed() {
	return currentSpeed;
}
MoveState Player::getState()
{
	return moveState;
}

bool Player::pickUp(Item* item) {
	
	if (inventoryUsed + item->numSlots() < iventoryCapacity) {
		inventory.push_back(item);
		inventoryUsed += item->numSlots();
		std::cout << "pick up " << item->getDescription() << "\n";
		return true;
	}
	std::cout << "pick up failed " << item->getDescription() << "\n";
	keyAvailabe = false;
	return false;
	
}

std::vector<Item*> Player::pickUp(std::vector<Item*> items) {
	std::vector<Item*> remaining;
	for each (Item* i in  items)
	{
		if (!pickUp(i))
			remaining.push_back(i);
	}
	keyAvailabe = false;
	return remaining;
	
}

bool Player::hasItem(Item* item) {
	for each (Item* i in inventory)
	{
		if (i == item) { 
			return true;

		}
	}
	return false;
}

// combat
bool Player::takeDamage(int damage) {
	if (health == MAX_HEALTH)
		healthRegen.restart();
	health -= damage;
	//cout << "damaged to " << health << "\n";
	return health > 0;
	
}
void Player::heal(int heal) {
	this->health = min(this->health + heal, MAX_HEALTH);
//	cout << "healed to " << health << "\n";
}
void Player::attack() {
	if (moveState == Walk) {
		attackCooldown.restart();
		for each (Enemy* enemy in world->getCurrentRoom()->getEnemies())
		{
			sf::Vector2f direction = sf::Vector2f(enemy->getPosition() - position);
			float distance = sqrt(direction.x*direction.x + direction.y*direction.y);
			if (distance < 15) {
				int enemyHealth = enemy->takeDamage(strength);
				cout << "enemy has " << enemyHealth << "health remaining\n";
				break;
			}
		}
	}
	
}

void Player::turn(float radians) {
	if (moveState == Walk)
	{
		heading += radians;
		//cout << "radians " << heading << "\n";
		shape.setRotation(heading);
		animated::rotate(radians);

		sprite.rotate(radians);
		spritea.rotate(radians);
	}
	else if (moveState == Ride)
	{
		heading += 0.5*radians;
		//cout << "radians " << heading << "\n";
		shape.setRotation(heading);
		animated::rotate(0.5*radians);

		sprite.rotate(0.5*radians);
		spritea.rotate(0.5*radians);
	}
		
	
}

void Player::walk(sf::Vector2f direction) {
	if (moveState == Walk)
	{
		shape.move(direction);
		//animated::move(direction);
		position += direction;
	}
	else if (moveState = Ride)
	{
		shape.move(direction);
		//animated::move(direction);
		position += direction;
	}
	
}
void Player::keyInRoom(int size)
{
	if (size > 0)
		keyAvailabe = true;
	else
		keyAvailabe = false;
}
bool Player::hasAllKeys() {
	int count = 0;
	for each (Item* item in inventory)
	{
		if (item->getDescription() == "Key ")
			count++;
	}
	//cout << count << '\n';
	return (count >= totalKeys);
}

void Player::update(sf::Time deltaTime) {
	// combat

	if (attackFlag && attackCooldown.getElapsedTime().asMilliseconds() > 2000){
		attack();
	}
	// movement
	sf::Vector2f direction = sf::Vector2f(
		sin(getSprite()->getRotation()*3.14159265 / 180) * -1,
		cos(getSprite()->getRotation()*3.14159265 / 180));

	lookAtVector = direction / sqrt(direction.x*direction.x + direction.y*direction.y);
	direction = sf::Vector2f(direction.x * currentSpeed, direction.y * currentSpeed);

	if (moveState == Walk)
	{
		if (world->checkPlayerIsInRoom(position + direction - sf::Vector2f(animated::getSize().x / 2, animated::getSize().y / 2), &direction, animated::getSize())) {
			if (currentSpeed != 0)
				walk(direction);
			if (currentRotation != 0)
				turn(currentRotation);
		}
		else {
			//cout << "locked\n";
		}
	}
	if (moveState == Ride)
	{
		if (world->checkPlayerIsInRoom(position + direction - sf::Vector2f(animated::getSize().x / 2, animated::getSize().y / 2), &direction, animated::getSize())) {//scaling problem since the scale is too tiny and the size is huge!
			if (direction.x == 0 && direction.y == 0) {
			currentSpeed =	breaks(1.5*exelSpeed);
			//	cout << "COLISSIONNN\n";
			}
			
			
			if (currentSpeed != 0)
				walk(direction);
			if (currentRotation != 0)
				turn(currentRotation);
		}
		else {
			//cout << "locked\n";
		currentSpeed = 	breaks(2*exelSpeed);


		}

	}
	// inventory
	keyInRoom(world->getCurrentRoom()->getInventorySize());

	if (pickUpFlag) {
		pickUp(world->getCurrentRoom()->pickUpItems());
	}

	// Game Over Tests
	if (health <= 0) {
		moveState = Dead;
		sprited.setPosition(position);
		lostGame = true;
		
	}
	if (world->getCurrentRoom()->getRoomNumber() == 0 && hasAllKeys()) {
		wonGame = true;
	}



	// regen health
/*	if (healthRegen.getElapsedTime().asSeconds() >= healthRegenReset) {
		heal(1);
		healthRegen.restart();
	}*/
	// healthbar
	healthBar.setPosition(position.x - 640, position.y - 360);
	size = sf::Vector2f(width*health, hight);
	healthBar.setSize(size);

	for (int i = 0; i < inventory.size(); i++) {
		sf::Vector2f positionItem(position.x - 640 + i * 20, position.y + 300);
		inventory.at(i)->setPosition(positionItem);
	}

	//animation
	animated::setFrame(deltaTime, offset);
	shape.setPosition(position);
	animated::setPosition(position);
	sprite.setPosition(position);
	text.setPosition(position.x-130, position.y - 50);

	textI.setPosition(position.x - 640, position.y + 270);
	textM.setPosition(position.x - 640, position.y + 200);

	if (hasItem(world->getMotorcycle()))
	{
		textM.setString(world->getMotorcycle()->getDescription());
		textM.setColor(sf::Color::White);
		textM.setFont(font);
		textM.setCharacterSize(20);
		//cout << inventory.at(1)->getDescription() << endl;
	}
	if (hasItem(world->getCurrentRoom()->getGas()))
	{
		world->getMotorcycle()->addFuel(world->getCurrentRoom()->getGas()->getFuel());
	//	cout << world->getCurrentRoom()->getRoomNumber() << "//////////////" << endl;
		inventory.pop_back();
	}
	if (hasItem(world->getCurrentRoom()->getHealthPack()))
	{
		health += world->getCurrentRoom()->getHealthPack()->getHealth();
		if (health > MAX_HEALTH)
			health = MAX_HEALTH;
		cout<< health;
		inventory.pop_back();
	}

}

void Player::render(sf::RenderWindow* window) {
	//window->draw(shape);
	if (attackFlag == false)
	{
		if (moveState == Walk)
		{
			animated::render(window);
		}
		else if (moveState == Ride)
		{
			window->draw(sprite);
			window->draw(textM);
		}
		else if (moveState == Dead)
		{
			window->draw(sprited);
		}
	}
	else if (attackFlag == true)
	{
		if(moveState == Walk)
			window->draw(spritea);
		else if (moveState == Ride)
		{
			window->draw(sprite);
			window->draw(textM);
		}
		if( health <= 0)
			window->draw(sprited);
		

	}
	
	window->draw(healthBar);
	if (keyAvailabe)
	{
		window->draw(text);
	}
	for (int i = 0; i < inventory.size(); i++) {
		inventory.at(i)->render(window);
	}
	window->draw(textI);
	
}