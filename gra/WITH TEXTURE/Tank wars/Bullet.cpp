#include "all.h"

Bullet::Bullet(double x, double y, double radius, Texture* texture1) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	//body.setRadius(radius);
	body.setSize(Vector2f(25, 11));
	body.setPosition(Vector2f(x, y));
	body.setOrigin(radius / 2, radius / 2);
	body.setFillColor(Color::Black);
	body.setTexture(texture1);
}

void Bullet::Update() {
	body.setPosition(Vector2f(this->x, this->y));
}

void Bullet::UpdateY(int y) {
	this->y = y;
	body.setPosition(x, y);
}

void Bullet::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

Pos Bullet::ballPath(double startX, double startY, double power, double ang, double time) {
	double angle = ang;
	double velX = cos(angle) * power;
	double velY = sin(angle) * power;

	double distX = velX * time;
	double distY = (velY * time) + ((-4.9) * (time * time)) / 2;

	double newX = round(distX + startX);
	double newY = round(startY - distY);

	Pos result = { newX, newY };

	return result;
}

double Bullet::getX() {
	return this->x;
}

double Bullet::getY() {
	return this->y;
}

double Bullet::getR() {
	return this->radius;
}

void Bullet::setX(double x) {
	this->x = x;
}

void Bullet::setY(double y) {
	this->y = y;
}

void Bullet::setRotation(double angle) {
	this->body.setRotation(angle);
}

void Bullet::addRotation(double angle) {
	this->body.rotate(angle);
}

void Bullet::addOpacity() {
	body.setFillColor(sf::Color(255, 255, 255, 0));
}

void Bullet::removeOpacity() {
	body.setFillColor(sf::Color(255, 255, 255, 255));
}