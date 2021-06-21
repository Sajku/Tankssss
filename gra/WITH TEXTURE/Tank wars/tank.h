#pragma once
#include "all.h"

using namespace sf;
using namespace std;

class Tank
{
public:
	Tank(int x, int y, Vector2f size, int hp, int dmg, bool side, Texture* texture, Texture* texture2);
	virtual ~Tank() = default;
	void Draw(RenderWindow& window);
	void Update(int newX);
	void updateGun(double angle);
	int getY();
	int getHP();
	string getHPString();
	void DecreaseHP(int damage);
	int GetX();
	void updateTexture(Texture* newTexture);

private:
	int posX;
	int posY;
	int health;
	int damage;
	bool onLeft;
	RectangleShape body;
	RectangleShape gun;
};

