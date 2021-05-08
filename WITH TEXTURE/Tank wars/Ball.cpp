#include "Ball.h"
#include <cmath>
#define M_PI 3.14159265358979323846

Ball::Ball(double x, double y, double radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	//body.setRadius(radius);
	body.setSize(Vector2f(radius + 7, radius));
	body.setPosition(Vector2f(x, y));
	body.setOrigin(radius / 2, radius / 2);
	body.setFillColor(Color::Black);
}

Ball::~Ball()
{

}

void Ball::Update() {
	body.setPosition(Vector2f(this->x, this->y));
}

void Ball::UpdateY(int y) {
	body.setPosition(x, y);
}

void Ball::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

Pos Ball::ballPath(double startX, double startY, double power, double ang, double time) {
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
