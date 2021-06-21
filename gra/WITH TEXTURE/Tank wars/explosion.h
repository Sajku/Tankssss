#pragma once
#include "all.h"

using namespace sf;

class Explosion {
public:
	Explosion(Texture* texture, bool end);
	virtual ~Explosion() = default;

	void Draw(RenderWindow& window);
	void boom(double x, double y);
	void Update();

private:
	bool ending;
	float step;
	RectangleShape body;
};

