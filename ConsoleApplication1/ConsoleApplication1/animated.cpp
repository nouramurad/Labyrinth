#include "animated.h"



animated::animated()
{
	currentFrameTime = sf::Time::Zero;
	currentFrame = STOP;
}


animated::~animated()
{
}

bool animated::setTexture(std::string fileName,sf::Vector2f scale) {

	for (int i = 0; i < (int)Frames::Count; i++)
	{
		textures.push_back(sf::Texture());
		textures.back().setSmooth(true);
	}
	bool flag = true;
	if (!textures.at(Frames::STOP).loadFromFile(fileName + "_walk_stand.png"))
		flag = false;
	if (textures[Frames::RIGHT1].loadFromFile(fileName + "_walk_Right.png"))
		flag = false;
	if (textures[Frames::RIGHT2].loadFromFile(fileName + "_walk_left.png"))
		flag = false;
	if (textures[Frames::LEFT1].loadFromFile(fileName + "_walk_Right.png"))
		flag = false;
	if (textures[Frames::LEFT2].loadFromFile(fileName + "_walk_left.png"))
		flag = false;
	if (textures[Frames::UP1].loadFromFile(fileName + "_walk_left.png"))
		flag = false;
	if (textures[Frames::UP2].loadFromFile(fileName + "_walk_Right.png"))
		flag = false;
	if (textures[Frames::DOWN1].loadFromFile(fileName + "_walk_left.png"))
		flag = false;
	if (textures[Frames::DOWN2].loadFromFile(fileName + "_walk_Right.png"))
		flag = false;
	currentFrame = Frames::STOP;
	sprite.setTexture(textures[currentFrame]);
	sprite.setScale(scale);

	size.x = textures.front().getSize().x * scale.x;
	size.y = textures.front().getSize().y * scale.y ;

	sprite.setOrigin(size.x/2, size.y /2);

	currentFrameTime = sf::Time::Zero;
	return flag;
}

void animated::setFrame(sf::Time deltaTime, sf::Vector2f direction) {
	//std::cout << "dir " << direction.x << " ," << direction.y << "\n";
	if (direction.x == 0 && direction.y == 0) {
		currentFrame = STOP;
	}
	else if (direction.x > 0 && direction.y == 0 && currentFrameTime.asMilliseconds() >= 100) {
		if (currentFrame == RIGHT1)
			currentFrame = RIGHT2;
		else
			currentFrame = RIGHT1;
		currentFrameTime = sf::Time::Zero;
	}
	else if (direction.x < 0 && direction.y == 0 && currentFrameTime.asMilliseconds() >= 100) {
		if (currentFrame == LEFT1)
			currentFrame = LEFT2;
		else
			currentFrame = LEFT1;
		currentFrameTime = sf::Time::Zero;
	}
	else if (direction.x == 0 && direction.y < 0 && currentFrameTime.asMilliseconds() >= 100) {
		if (currentFrame == UP1)
			currentFrame = UP2;
		else
			currentFrame = UP1;
		currentFrameTime = sf::Time::Zero;
	}

	else if (direction.x == 0 && direction.y > 0 && currentFrameTime.asMilliseconds() >= 100) {
		if (currentFrame == DOWN1)
			currentFrame = DOWN2;
		else
			currentFrame = DOWN1;
		currentFrameTime = sf::Time::Zero;
	}
	sprite.setTexture(textures[currentFrame]);
	currentFrameTime += deltaTime;

	//std::cout << currentFrame << "\n";
}

void animated::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}
void animated::move(sf::Vector2f delta) {
	sprite.move(delta);
}
void animated::rotate(float radians) {
	sprite.rotate(radians);

}

void animated::render(sf::RenderWindow* window) {
	window->draw(sprite);
}