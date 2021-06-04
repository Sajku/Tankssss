#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Tank
{
public:
	Tank();
	Tank(int x, int y, Vector2f size, int hp, int dmg, bool side, Texture* texture, Texture* texture2);
	~Tank();
	void Draw(RenderWindow& window);
	void Update(int newX);
	void updateGun(double angle);
	int getY();
	string getHP();

private:
	int posX;
	int posY;
	int health;
	int damage;
	bool onLeft;
	RectangleShape body;
	RectangleShape gun;
};

