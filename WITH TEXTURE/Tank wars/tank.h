#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Tank
{
public:
	Tank(int x, int y, Vector2f size, int hp, int dmg, bool side, Texture* texture);
	~Tank();
	void Draw(RenderWindow& window);
	void Update(int newX);

private:
	int posX;
	int posY;
	int health;
	int damage;
	bool onLeft;
	RectangleShape body;
};

