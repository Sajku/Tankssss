#pragma once
#include "all.h"

using namespace sf;
using namespace std;

struct Pos {
	double x;
	double y;
};

class Bullet
{
public:
	Bullet(double x, double y, double radius, Texture* texture1);
	virtual ~Bullet() = default;

	void Update();
	void UpdateY(int y);
	void Draw(RenderWindow& window);
	Pos ballPath(double startX, double startY, double power, double ang, double time);
	
	double getX();
	double getY();
	double getR();

	void setX(double x);
	void setY(double y);

	void setRotation(double angle);
	void addRotation(double angle);

	void addOpacity();
	void removeOpacity();

private:
	double x;
	double y;
	double radius;
	RectangleShape body;
};

