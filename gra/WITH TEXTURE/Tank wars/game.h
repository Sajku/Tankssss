#pragma once
#include "all.h"

class Game {
public:
	Game(RenderWindow* window);
	virtual ~Game() = default;

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
	bool endingOpen;
	bool end;

	Vector2f position1;
	Vector2f position2;

	int map[160]{};

	RenderWindow* window;
	Event winEvent;
	Vector2i mousePos;

	Font font;
	Text leftHP;
	Text rightHP;

	Texture arrowTexture;
	Texture surfaceTexture;
	Texture tankTexture1a;
	Texture tankTexture1b;
	Texture destroyedTankTexture1;
	Texture destroyedTankTexture2;
	Texture tankTexture2a;
	Texture tankTexture2b;
	Texture tankLeftHPT;
	Texture tankRightHPT;
	Texture explosionTexture;
	Texture endingExplosionTexture;
	Texture bulletTexture;
	Texture backgroundTexture;
	Texture winTexture;

	Texture endingT;
	RectangleShape ending;
	RectangleShape win;

	RectangleShape ground;
	RectangleShape background;
	RectangleShape arrow;
	Tank tankLeft = Tank(150, 550, Vector2f(100, 55), 100, 10, true, &tankTexture1a, &tankTexture1b);
	Tank tankRight = Tank(1130, 550, Vector2f(100, 55), 100, 10, false, &tankTexture2a, &tankTexture2b);
	RectangleShape tankLeftHP;
	RectangleShape tankRightHP;
	
	Explosion explosion = Explosion(&explosionTexture, false);
	Explosion endingExplosion = Explosion(&endingExplosionTexture, true);
	Bullet bullet = Bullet(140, 580, 13, &bulletTexture);

};