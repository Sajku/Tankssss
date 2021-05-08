#include "tank.h"

Tank::Tank(int x, int y, Vector2f size, int hp, int dmg, bool side, Texture* texture) {
	this->posX = x;
	this->posY = y;
	this->health = hp;
	this->damage = dmg;
	this->onLeft = side;
	body.setPosition(x,y);
	body.setOrigin(50,27);
	body.setSize(size);
	body.setTexture(texture);
	if (!side) {
		body.setTextureRect(IntRect(100,0,-100,55));
	}
}

Tank::~Tank() {}

void Tank::Draw(RenderWindow& window) {
	window.draw(body);
}

void Tank::Update(int newY) {
	if (newY > 710) body.setPosition(posX, 695);
	else body.setPosition(posX, newY);
}
