#include "all.h"

Tank::Tank(int x, int y, Vector2f size, int hp, int dmg, bool side, Texture* texture, Texture* texture2) {
	this->posX = x;
	this->posY = y;
	this->health = hp;
	this->damage = dmg;
	this->onLeft = side;
	body.setPosition(x,y);
	body.setOrigin(50,27);
	body.setSize(size);
	body.setTexture(texture);
	gun.setSize(Vector2f(43, 6));
	gun.setTexture(texture2);

	if (!side) {
		body.setTextureRect(IntRect(100,0,-100,55));
		gun.setOrigin(43, 3);
		gun.setTextureRect(IntRect(43,0,-43,6));
		gun.setPosition(x - 7, y + 41);
	}
	else {
		body.setTextureRect(IntRect(0, 0, 100, 55));
		gun.setOrigin(0, 3);
		gun.setTextureRect(IntRect(0, 0, 43, 6));
		gun.setPosition(x + 8, y + 41);
	}
}

void Tank::Draw(RenderWindow& window) {
	window.draw(gun);
	window.draw(body);
}

void Tank::Update(int newY) {
	this->posY = newY;
	if (newY > 695) body.setPosition(posX, 695);
	else body.setPosition(posX, newY);

	if (onLeft)	gun.setPosition(posX + 8, newY-3);
	else gun.setPosition(posX - 7, newY-3);
}

void Tank::updateGun(double angle) {
	if (onLeft) gun.setRotation(angle);
	else {
		angle += 180;
		gun.setRotation(angle);
	}
}

int Tank::getY() {
	return posY;
}

int Tank::getHP() {
	return health;
}

string Tank::getHPString() {
	return to_string(health);
}

void Tank::DecreaseHP(int damage)
{
	health = health - damage;
	if (health <= 0) health = 0;
}

int Tank::GetX(){
	return posX;
}

void Tank::updateTexture(Texture* newTexture) {
	this->body.setTexture(newTexture);
	this->gun.setFillColor(sf::Color(255, 255, 255, 0));
}
