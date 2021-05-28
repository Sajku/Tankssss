#pragma once
#include "all.h"

class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game();

	void init();
	void run();

	double findAngle(Bullet bullet, Vector2i mousePos);
	void bulletInAir();
	void bulletInTank();
	void bulletHitGround(Pos po);
	void holeMaker();

private:
	double time;
	double power;
	double angle;
	bool shoot;
	bool collided;
	double x;
	double y;
	int stripeNumber;
	double currentAngle;
	int whoHasMove;

	Vector2f position1;
	Vector2f position2;

	int map[160]{};

	RenderWindow* window;
	Event winEvent;
	Vector2i mousePos;

	Texture arrowTexture;
	Texture surfaceTexture;
	Texture tankTexture1a;
	Texture tankTexture1b;
	Texture explosionTexture;
	Texture bulletTexture;
	Texture backgroundTexture;

	RectangleShape ground;
	RectangleShape background;
	RectangleShape arrow;
	Tank tankLeft = Tank(150, 550, Vector2f(100, 55), 1000, 100, true, &tankTexture1a, &tankTexture1b);
	Tank tankRight = Tank(1050, 550, Vector2f(100, 55), 1000, 100, false, &tankTexture1a, &tankTexture1b);
	Explosion explosion = Explosion(&explosionTexture);
	Bullet bullet = Bullet(140, 580, 13, &bulletTexture);

};