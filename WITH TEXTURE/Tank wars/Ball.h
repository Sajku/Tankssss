#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"

using namespace sf;
using namespace std;

struct Pos {
	double x;
	double y;
};

class Ball
{
public:
	Ball(double x, double y, double radius);
	~Ball();

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

private:
	double x;
	double y;
	double radius;
	RectangleShape body;
};

