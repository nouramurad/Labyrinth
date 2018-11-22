#include "View.h"



View::View(Model* model)
{
	font.loadFromFile("ariali.ttf");
	text.setColor(sf::Color::White);
	text.setFont(font);
	text.setCharacterSize(20);

	this->model = model;
	window = new sf::RenderWindow();
	this->window->create(sf::VideoMode(winW, winH), "Adventure");
	this->window->setFramerateLimit(60);

	winSize = sf::Vector2f(winW, winH);
	/*
	sf::Image actorimage;
	actorimage.loadFromFile("Assets/actorspritesheet.png");
	actorTex.loadFromImage(actorimage);
	actorTex.setSmooth(true);
	actorStates.texture = &actorTex;
	actorTexSize;
	actorSpriteSheetSize;
	actorVerticesPos = 0;

	sf::Image objectimage;
	objectimage.loadFromFile("Assets/objectspritesheet.png");
	objectTex.loadFromImage(objectimage);
	objectTex.setSmooth(true);
	objectStates.texture = &objectTex;
	objectTexSize;
	objectSpriteSheetSize;
	objectVerticesPos = 0;
	*/

	worldVertices = sf::VertexArray(sf::Quads, model->getWorld()->getRooms()->size() * 4 + model->getWorld()->getCorridors()->size() * 4);
	
	sf::Image worldimage;
	worldimage.loadFromFile("data/worldspritesheet.png");
	worldTex.loadFromImage(worldimage);
	worldTex.setSmooth(true);
	worldStates.texture = &worldTex;
	worldTexSize = sf::Vector2i(64,64);
	worldSpriteSheetSize = sf::Vector2i(2, 3);
	worldVerticesPos = 0;

	addRooms();
}

View::~View()
{
}

void View::addRenderable(renderable* obj) {
	model->getRenderables()->push_back(obj);
}
/*
void View::addActorSprite(sf::Vector2f pos, sf::Vector2f size, int texNum) {
	actorVertices[actorVerticesPos  + 0].position = sf::Vector2f(pos.x, pos.y); // top left
	actorVertices[actorVerticesPos  + 1].position = sf::Vector2f(pos.x + size.x, pos.y);//top right
	actorVertices[actorVerticesPos  + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);// bottom right
	actorVertices[actorVerticesPos  + 3].position = sf::Vector2f(pos.x, pos.y + size.y);// bottom left

	int y = texNum % actorSpriteSheetSize.y;
	int x = (texNum - y) / actorSpriteSheetSize.x;

	actorVertices[actorVerticesPos + 0].texCoords = sf::Vector2f(x * actorTexSize.x, y * actorTexSize.y);
	actorVertices[actorVerticesPos + 1].texCoords = sf::Vector2f((x + 1) * actorTexSize.x, y * actorTexSize.y);
	actorVertices[actorVerticesPos + 2].texCoords = sf::Vector2f((x + 1) * actorTexSize.x, (y + 1) * actorTexSize.y);
	actorVertices[actorVerticesPos  + 3].texCoords = sf::Vector2f(x * actorTexSize.x, (y + 1) * actorTexSize.y);
	actorVerticesPos += 4;
}

void View::addObjectSprite(sf::Vector2f pos, sf::Vector2f size, int texNum) {
	objectVertices[objectVerticesPos + 0].position = sf::Vector2f(pos.x, pos.y); // top left
	objectVertices[objectVerticesPos + 1].position = sf::Vector2f(pos.x + size.x, pos.y);//top right
	objectVertices[objectVerticesPos + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);// bottom right
	objectVertices[objectVerticesPos + 3].position = sf::Vector2f(pos.x, pos.y + size.y);// bottom left

	int y = texNum % objectSpriteSheetSize.y;
	int x = (texNum - y) / objectSpriteSheetSize.x;

	objectVertices[objectVerticesPos + 0].texCoords = sf::Vector2f(x * objectTexSize.x, y * objectTexSize.y);
	objectVertices[objectVerticesPos + 1].texCoords = sf::Vector2f((x + 1) * objectTexSize.x, y * objectTexSize.y);
	objectVertices[objectVerticesPos + 2].texCoords = sf::Vector2f((x + 1) * objectTexSize.x, (y + 1) * objectTexSize.y);
	objectVertices[objectVerticesPos + 3].texCoords = sf::Vector2f(x * objectTexSize.x, (y + 1) * objectTexSize.y);
	objectVerticesPos += 4;
}
*/
void View::addWorldSprite(sf::Vector2f pos, sf::Vector2f size, int texNum, sf::Color col) {

	
	worldVertices[worldVerticesPos + 0].position = sf::Vector2f(pos.x, pos.y); // top left
	worldVertices[worldVerticesPos + 1].position = sf::Vector2f(pos.x + size.x, pos.y);//top right
	worldVertices[worldVerticesPos + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);// bottom right
	worldVertices[worldVerticesPos + 3].position = sf::Vector2f(pos.x, pos.y + size.y);// bottom left

	int y = texNum % worldSpriteSheetSize.y;
	int x = (texNum - y) / worldSpriteSheetSize.x;

	std::cout << x << ", " << y << " = texCoord, " << pos.x << ", " << pos.y << " = worldCoord\n";

	worldVertices[worldVerticesPos + 0].texCoords = sf::Vector2f(x * worldTexSize.x, y * worldTexSize.y);
	worldVertices[worldVerticesPos + 1].texCoords = sf::Vector2f((x + 1) * worldTexSize.x, y * worldTexSize.y);
	worldVertices[worldVerticesPos + 2].texCoords = sf::Vector2f((x + 1) * worldTexSize.x, (y + 1) * worldTexSize.y);
	worldVertices[worldVerticesPos + 3].texCoords = sf::Vector2f(x * worldTexSize.x, (y + 1) * worldTexSize.y);



	worldVertices[worldVerticesPos + 0].color = col;
	worldVertices[worldVerticesPos + 1].color = col;
	worldVertices[worldVerticesPos + 2].color = col;
	worldVertices[worldVerticesPos + 3].color = col;

	worldVerticesPos += 4;
}

void View::addRooms() {
	std::cout << "addCorridors\n";
	std::vector<Room*>* rooms = model->getWorld()->getCorridors();
	for each (Room* room in *rooms)
	{
		addWorldSprite(room->getPosition(), room->getSize(), 2, room->getColor());
	}
	std::cout << "addRooms\n";
	rooms = model->getWorld()->getRooms();
	for each (Room* room in *rooms)
	{
		addWorldSprite(room->getPosition(), room->getSize(), 1, room->getColor());
	}
	
	std::cout << "world added\n";
}
void View::gameOver() {
	if (!gameOverflag) {
		gameOverflag = true;
		std::cout << "gameover\n";

		if (model->getPlayer()->playerWon()) {
			text.setString("YOU WIN!");
		}
		else if (model->getPlayer()->playerLost()) {
			text.setString("YOU LOSE!");
		}
		text.setPosition(model->getPlayer()->getPosition().x - 100, model->getPlayer()->getPosition().y - 100);
		//model->getPlayer()->render(window);
		render();
		window->draw(text);
		window->display();
	}
	
	//sf::sleep(sf::seconds(5));
	/*while (true) {
		if (sf::Keyboard::isKeyPressed)
			break;
	}*/
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}

}

void View::render() {
	window->clear();
	view = sf::View(model->getPlayer()->getPosition(),  winSize );
	window->setView(view);
	window->draw(worldVertices, worldStates);
	for each (renderable* obj in *model->getRenderables())
	{
		obj->render(window);
	}

	window->display();
}
