#include "World.h"
#include "Player.h"

World::World()
{

}

World::~World()
{
	for each (Room* r in rooms)
	{
		r->~Room();
	}
	for each (Room* c in corridors)
	{
		c->~Room();
	}
}

void World::addRoom(Room* room) {
	rooms.push_back(room);
}

void World::addRoom(sf::Color color, sf::Vector2f position, sf::Vector2f size, int roomNumber) {
	Room* room = new Room(color, position, size, roomNumber);
	addRoom(room);
}

void World::addCorridor(Room* corridor) {
	corridors.push_back(corridor);
}

void World::placeRooms(sf::Color playerColor) {
	srand(time(NULL));
	int failCount;
	lockedCount = 0;
	rooms.clear();
	corridors.clear();
	while (rooms.size() <  NUM_ROOMS) {
		// random size and place room
		float w = MIN_ROOM_SIZE + (rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE)) + 1;
		float h = MIN_ROOM_SIZE + (rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE)) + 1;
		float x = (rand() % (WORLD_WIDTH - (int)w - 1)) + 1;
		float y = (rand() % (WORLD_HEIGHT - (int)h - 1)) + 1;


		sf::Color color = playerColor;
		while (color == playerColor) {
			color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		}
		Room* room = new Room(color, sf::Vector2f(x, y), sf::Vector2f(w, h), rooms.size());

		bool interesctsRoom = false;

		// check if room is ontop another room
		for (int j = 0; j < rooms.size(); j++) {
			if (room->intersects(rooms.at(j))) {
				interesctsRoom = true;
				break;
			}
		}
		if (!interesctsRoom) {
			// if not the first room, create corridor to previous
			if ((rooms.size() > 0)) {
				sf::Vector2f prevCenter = rooms.back()->getCenter();
				int shade = rand() % 230 + 25;


				bool interesctscorridor = false;
				// check if room is ontop a corridor
				for (int j = 0; j < corridors.size(); j++) {
					if (room->intersects(corridors.at(j))) {
						interesctscorridor = true;
						break;
					}
				}



				createCorridor(prevCenter, room->getCenter(), sf::Color(shade, shade, shade, 255), room->getRoomNumber());

				// if previous room unlocked and room does not intersect a corridor, key placed in previous room
				// and room is locked
				if (!rooms.back()->isLocked() && !interesctscorridor && rooms.size() >1) {//rand() % 100 < CHANCELOCKED) {

					rooms.back()->addItem(room->getKey());
					room->getKey()->setColor(room->getColor());
					room->lock(true);
					lockedCount++;
				}

			}

			addRoom(room);

			failCount = 0;
			//cout << "Added room " << rooms.size() << " at (" << x << ", " << y << ")\n";

		}
		else {
			failCount++;
			//cout << "Failed to add room " << rooms.size() << " at (" << x << ", " << y << ")\n";
		}
		// if cannot place room give up
		if (failCount > 50)
			break;
	}
	currentRoom = rooms.front();
	previousRoom = currentRoom;

	std::cout << "Number of rooms: " << rooms.size() << ". Locked: " << lockedCount << ".\n";
	currentRoom->lock(true);// TESTING
	motorcycle = new Motorcycle(currentRoom);
	currentRoom->addItem(motorcycle);


}

void World::createCorridor(sf::Vector2f pointA, sf::Vector2f pointB, sf::Color color, int roomNumber) {
	if (rand() % 2 == 0) {
		// make horzontal corridor
		Room* horCor = new Room(color,
			sf::Vector2f(min(pointA.x, pointB.x), pointB.y),
			sf::Vector2f(max(abs(pointA.x - pointB.x), CORRIDOR_SIZE) + CORRIDOR_SIZE, CORRIDOR_SIZE), -1 * roomNumber);

		// make vertical corridor
		Room* verCor = new Room(color,
			sf::Vector2f(pointA.x, min(pointA.y, pointB.y)),
			sf::Vector2f(CORRIDOR_SIZE, max(abs(pointA.y - pointB.y) + CORRIDOR_SIZE, CORRIDOR_SIZE)), -1 * roomNumber);
		corridors.push_back(horCor);
		corridors.push_back(verCor);


	}
	else {
		// make vertical corridor
		Room* verCor = new Room(color,
			sf::Vector2f(pointB.x - CORRIDOR_SIZE / 2, min(pointA.y, pointB.y) - CORRIDOR_SIZE / 2),
			sf::Vector2f(CORRIDOR_SIZE, max(abs(pointA.y - pointB.y), 0.0f) + CORRIDOR_SIZE), -1 * roomNumber);
		// make horizontal corridor
		Room* horCor = new Room(color,
			sf::Vector2f(min(pointA.x, pointB.x) - CORRIDOR_SIZE / 2, pointA.y - CORRIDOR_SIZE / 2),
			sf::Vector2f(max(abs(pointA.x - pointB.x) + CORRIDOR_SIZE, 0.0f), CORRIDOR_SIZE), -1 * roomNumber);
		corridors.push_back(horCor);
		corridors.push_back(verCor);
		//horCor->addItem(verCor->getGas());

	}

}

void World::placeEnemies() {
	int random;
	for (int i = 1; i < rooms.size(); i++) {
		/*sf::Texture tex;
		if (tex.loadFromFile("c:\\goku_small.jpg")) {// , sf::IntRect(currentRoom.getTopLeft().x, currentRoom.getTopLeft().y, 20, 20));
		cout << "Tex loaded size: (" << tex.getSize().x << ", " << tex.getSize().y << ")\n";
		}*/

		if (rooms.at(i)->getInventorySize() == 0)
		{
			random = rand() % 2;
			if (random == 0)
			{
				rooms.at(i)->addItem(rooms.at(i)->getGas());
			}
			else if (random == 1)
			{
				rooms.at(i)->addItem(rooms.at(i)->getHealthPack());
			}
		}

		Enemy* testEnemy = new Enemy(rooms.at(i), player);
		testEnemy->init(rooms.at(i)->getPosition().x + 5, rooms.at(i)->getPosition().y + 5, sf::Vector2f(1, 1), 3.0f, "data/zombie_Attack.png");
		rooms.at(i)->addEnemy(testEnemy);
	}
}
void World::placeMotorcycle()
{
	//	Motorcycle* motorcycle = new Motorcycle(corridors.at(0), player);
	cout << corridors.at(1)->getRoomNumber();
}

bool World::checkIsInRoom(sf::Vector2f position, float angle, sf::Vector2f size) {
	bool ret = false;
	for (int i = 0; i < rooms.size(); i++) {
		if (rooms.at(i)->checkIsInRoom(position, angle, size)) {
			ret = true;
		}
	}
	for (int i = 0; i < corridors.size(); i++) {
		if (corridors.at(i)->checkIsInRoom(position, angle, size)) {
			ret = true;
		}
	}
	return ret;
}

bool World::checkPoint(Room* room, sf::Vector2f position) {
	if (room->checkIsInRoom(position)) {
		unlockRoom(room);
		return true;
	}
	return false;
}

void World::handleCollision(sf::Vector2f* direction) {
	float m = direction->y / direction->x;
	//cout << m << std::endl;
	if (!topLeftB) {
		if (!topRightB && !bottomLeftB) {
			// do nothing
			direction->x = 0;
			direction->y = 0;
		}

		else if (!topRightB) {
			// zero y in dir
			direction->y = 0;
		}
		else if (!bottomLeftB) {
			direction->x = 0;
			// zero x in dir
		}
		else {

			float b = m *-topLeft.x + topLeft.y;
			float roomB = bottomLeftRoom->getPosition().y;
			float intersectX = (roomB - b) / m;
			float intersectY = m*intersectX + b;

			if (intersectX <= topLeft.x && intersectX >= topLeft.x - direction->x &&
				intersectY >= topLeft.y && intersectY <= topLeft.y - direction->y) {
				direction->y = 0;
			}
			else {
				direction->x = 0;
			}
			/*
			direction->x = 0;
			direction->y = 0;
			*/
		}

	}
	if (!topRightB) {
		if (!topLeftB && !bottomRightB) {
			direction->x = 0;
			direction->y = 0;
		}
		else if (!bottomRightB) {
			direction->x = 0;
		}
		else if (!topLeftB) {
			direction->y = 0;
		}
		else {
			float b = m *-topRight.x + topRight.y;
			float roomB = bottomRightRoom->getPosition().y;
			float intersectX = (roomB - b) / m;
			float intersectY = m*intersectX + b;

			if (intersectX >= topRight.x && intersectX <= topRight.x - direction->x &&
				intersectY >= topRight.y && intersectY <= topRight.y - direction->y) {
				direction->y = 0;
			}
			else {
				direction->x = 0;
			}

			/*direction->x = 0;
			direction->y = 0;
			*/
		}
	}
	if (!bottomLeftB) {
		if (!topLeftB && !bottomRightB) {
			direction->x = 0;
			direction->y = 0;
		}
		else if (!topLeftB) {
			direction->x = 0;
		}
		else if (!bottomRightB) {
			direction->y = 0;
		}
		else {
			float b = m *-bottomLeft.x + bottomLeft.y;
			float roomB = topLeftRoom->getPosition().y + topLeftRoom->getSize().y;
			float intersectX = (roomB - b) / m;
			float intersectY = m*intersectX + b;

			if (intersectX <= topLeft.x && intersectX >= topLeft.x - direction->x &&
				intersectY >= topLeft.y && intersectY >= topLeft.y - direction->y) {
				direction->y = 0;
			}
			else {
				direction->x = 0;
			}
			/*
			direction->x = 0;
			direction->y = 0;
			*/
		}


	}
	if (!bottomRightB) {
		if (!topRightB && !bottomLeftB) {
			direction->x = 0;
			direction->y = 0;
		}
		else if (!bottomLeftB) {
			direction->y = 0;
		}
		else if (!topRightB) {
			direction->x = 0;
		}
		else {
			float b = m *-bottomRight.x + bottomRight.y;
			float roomB = topRightRoom->getPosition().y + topRightRoom->getSize().y;
			float intersectX = (roomB - b) / m;
			float intersectY = m*intersectX + b;

			std::cout << "intersect " << intersectX << ", " << intersectY << " m = " << m << " b = " << b << "room b = " << roomB << "\npos " << topRight.x << " , " << topRight.y << "dir " << direction->x << ", " << direction->y << "\n\n";


			if (intersectX >= topRight.x && intersectX <= topRight.x - direction->x &&
				intersectY >= topRight.y && intersectY >= topRight.y - direction->y) {
				direction->y = 0;
				std::cout << "bottom right out dropY\n";
			}
			else {
				direction->x = 0;
				std::cout << "bottom right out dropX\n";
			}
			/*
			direction->x = 0;
			direction->y = 0;
			*/
		}
	}
}

bool World::checkPlayerIsInRoom(sf::Vector2f position, sf::Vector2f* direction, sf::Vector2f size) {
	bool unlocked = true;
	downMat = sf::Transform::Identity;
	rightMat = sf::Transform::Identity;
	//rotMat = sf::Transform::Identity;
	downMat.translate(sf::Vector2f(0, size.y));
	rightMat.translate(sf::Vector2f(size.x, 0));
	origin = sf::Vector2f(0, 0);
	sf::Transform frontmat = sf::Transform::Identity;
	frontmat.translate(*direction);
	topLeft = position;
	topRight = rightMat *origin + position;
	bottomLeft = downMat *origin + position;
	bottomRight = downMat*rightMat *origin + position;
	front = frontmat * position;

	topLeftB = false;
	topRightB = false;
	bottomLeftB = false;
	bottomRightB = false;

	for (int i = 0; i < rooms.size(); i++) {
		if (!topLeftB) {
			topLeftB = checkPoint(rooms.at(i), topLeft);
			if (topLeftB && rooms.at(i)->isLocked())
				unlocked = false;
			else if (topLeftB && !rooms.at(i)->isLocked()) {
				topLeftRoom = rooms.at(i);
			}
		}
		if (!topRightB) {
			topRightB = checkPoint(rooms.at(i), topRight);
			if (topRightB && rooms.at(i)->isLocked())
				unlocked = false;
			else if (topRightB && !rooms.at(i)->isLocked()) {
				topRightRoom = rooms.at(i);
			}
		}
		if (!bottomLeftB) {
			bottomLeftB = checkPoint(rooms.at(i), bottomLeft);
			if (bottomLeftB && rooms.at(i)->isLocked())
				unlocked = false;
			else if (bottomLeftB && !rooms.at(i)->isLocked()) {
				bottomLeftRoom = rooms.at(i);
			}
		}
		if (!bottomRightB) {
			bottomRightB = checkPoint(rooms.at(i), bottomRight);
			if (bottomRightB && rooms.at(i)->isLocked())
				unlocked = false;
			else if (bottomRightB && !rooms.at(i)->isLocked()) {
				bottomRightRoom = rooms.at(i);
			}
		}
	}


	for (int i = 0; i < corridors.size(); i++) {
		if (!topLeftB) {
			topLeftB = checkPoint(corridors.at(i), topLeft);
			if (topLeftB) {
				topLeftRoom = corridors.at(i);
			}
		}
		if (!topRightB) {
			topRightB = checkPoint(corridors.at(i), topRight);
			if (topRightB) {
				topRightRoom = corridors.at(i);
			}
		}
		if (!bottomLeftB) {
			bottomLeftB = checkPoint(corridors.at(i), bottomLeft);
			if (bottomLeftB) {
				bottomLeftRoom = corridors.at(i);
			}
		}
		if (!bottomRightB) {
			bottomRightB = checkPoint(corridors.at(i), bottomRight);
			if (bottomRightB) {
				bottomRightRoom = corridors.at(i);
			}
		}
	}
	handleCollision(direction);

	if (topLeftRoom == topRightRoom && bottomLeftRoom == bottomRightRoom && bottomLeftRoom == topLeftRoom && topLeftRoom->getRoomNumber() >= 0) {
		//topLeftRoom->playerEntered(player);
		//unlocked = true;
	}
	return unlocked;
}

void World::unlockRoom(Room* room) {
	if (player->hasItem(room->getKey())) {
		room->lock(false);
		player->setTrapped(false);
	}
}

Room* World::getCurrentRoom(sf::Vector2f position, float angle, sf::Vector2f size) {

	for (int i = 0; i < rooms.size(); i++) {
		if (rooms.at(i)->checkIsInRoom(position, angle, size)) {
			if (rooms.at(i) != currentRoom) {
				previousRoom = currentRoom;
				currentRoom = rooms.at(i);
				previousRoom->updateEnemyAi(false);
				currentRoom->updateEnemyAi(true);

				//currentRoom->playerEntered(player);

				//currentRoom->addItems(player->pickUp(currentRoom->pickUpItems()));

				cout << "Room " << currentRoom->getRoomNumber() << "\n";

			}
			player->setRiding(0);
			return rooms.at(i);
		}
	}

	for (int i = 0; i < corridors.size(); i++) {
		if (corridors.at(i)->checkIsInRoom(position, angle, size)) {
			if (corridors.at(i) != currentRoom) {
				previousRoom = currentRoom;
				currentRoom = corridors.at(i);
				previousRoom->updateEnemyAi(false);
				currentRoom->updateEnemyAi(true);

				//currentRoom->addItems(player->pickUp(currentRoom->pickUpItems()));
				cout << "corridor " << currentRoom->getRoomNumber() << "\n";
			}
			player->setRiding(1);
			return corridors.at(i);
		}
	}
	return previousRoom;

}

Room* World::randomRoom() {
	return rooms.at(rand() % rooms.size());
}

Room* World::firstRoom() {
	currentRoom = rooms.front();
	return rooms.front();
}

Room* World::getCurrentRoom() {
	return currentRoom;
}

void  World::update(sf::Time deltaTime) {
	getCurrentRoom(player->getPosition(), player->getHeading(), player->getSize());


	for (int i = 0; i < rooms.size(); i++) {
		rooms.at(i)->update(deltaTime);
	}
}

void  World::render(sf::RenderWindow* window) {
	sf::RectangleShape curR;
	curR.setPosition(sf::Vector2f(currentRoom->getPosition().x - 10, currentRoom->getPosition().y - 10));
	curR.setSize(sf::Vector2f(currentRoom->getSize().x + 20, currentRoom->getSize().y + 20));
	curR.setFillColor(sf::Color::White);
	//window->draw(curR);

	for (int i = 0; i < corridors.size(); i++) {
		corridors.at(i)->render(window);
	}
	for (int i = 0; i < rooms.size(); i++) {
		rooms.at(i)->render(window);
	}
	sf::CircleShape dot;
	dot.setRadius(3);
	dot.setOrigin(1.5, 1.5);
	dot.setFillColor(sf::Color::Yellow);
	dot.setPosition(topLeft);

	window->draw(dot);
	dot.setFillColor(sf::Color::Red);
	dot.setPosition(topRight);
	window->draw(dot);
	dot.setPosition(bottomLeft);
	window->draw(dot);
	dot.setPosition(bottomRight);
	window->draw(dot);
	dot.setFillColor(sf::Color::Green);
	dot.setPosition(front);
	window->draw(dot);
}