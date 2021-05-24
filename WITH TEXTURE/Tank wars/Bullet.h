#pragma once
#include <SFML\Graphics.hpp>
#include "Bullet.h"

using namespace sf;
using namespace std;

struct Pos {
	double x;
	double y;
};

class Bullet
{
public:
	Bullet();
	Bullet(double x, double y, double radius, Texture* texture1);
	~Bullet();

	void Update();
	void UpdateY(int y);
	void Draw(RenderWindow& window);
	Pos ballPath(double startX, double startY, double power, double ang, double time);
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double getR() {
		return radius;
	}

	void setX(double x) {
		this->x = x;
	}
	void setY(double y) {
		this->y = y;
	}

	void setRotation(double angle) {
		this->body.setRotation(angle);
	}

	void addRotation(double angle) {
		this->body.rotate(angle);
	}

	void addOpacity() {
		body.setFillColor(sf::Color(255, 255, 255, 0));
	}
	
	void removeOpacity() {
		body.setFillColor(sf::Color(255, 255, 255, 255));
	}

private:
	double x;
	double y;
	double radius;
	RectangleShape body;
};

