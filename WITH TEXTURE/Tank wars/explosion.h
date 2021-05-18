#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Explosion {
public:
	Explosion(Texture* texture);
	~Explosion();

	void Draw(RenderWindow& window);
	void boom(double x, double y);
	void Update();

private:
	int step;
	RectangleShape body;
};

