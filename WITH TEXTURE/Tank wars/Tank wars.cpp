#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <SFML\Graphics.hpp>
#include "tank.h"
#include "explosion.h"
#include "Bullet.h"
#define M_PI 3.14159265358979323846

using namespace sf;
using namespace std;

double findAngle(Bullet bullet, Vector2i mousePos) {

	double sX = bullet.getX();
	double sY = bullet.getY();
	double angle = 0;

	angle = atan((sY - mousePos.y) / (sX - mousePos.x));

	if (mousePos.y < sY && mousePos.x > sX)
		angle = abs(angle);
	else if (mousePos.y < sY && mousePos.x < sX)
		angle = M_PI - angle;
	else if (mousePos.y > sY && mousePos.x < sX)
		angle = M_PI + abs(angle);
	else if (mousePos.y > sY && mousePos.x > sX)
		angle = (M_PI * 2) - angle;

	return angle;

}

int main() {
	srand(time(NULL));

	double time = 0;
	double power = 0;
	double angle = 0;
	bool shoot = false;
	bool collided = false;
	double x = 0;
	double y = 0;
	int stripeNumber = 0;
	double currentAngle = 0;
	int random1 = 0;
	random1 = rand() % 2;
	int whoHasMove = random1;

	Vector2f position1;
	Vector2f position2;

	int map[160]{};

	string str = "";
	int count = 0;
	ifstream file("map_1.txt");
	if (file.good()) {
		while (!file.eof()) {
			file >> str;
			map[count] = stoi(str);
			count++;
		}
	}

	RenderWindow window(VideoMode(1280, 720), "SFML Program", Style::Close | Style::Titlebar);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);


	RectangleShape surface;
	surface.setSize(Vector2f(8, 360));
	//surface.setFillColor(Color(25, 137, 8));
	
	RectangleShape arrow;
	Texture arrowTexture;
	arrow.setSize(Vector2f(100, 50));
	arrow.setOrigin(95,25);
	arrowTexture.loadFromFile("textures/arrow.png");
	arrowTexture.setSmooth(true);
	arrow.setTexture(&arrowTexture);

	Texture surfaceTexture;
	surfaceTexture.loadFromFile("textures/grass1.jpg");
	surface.setTexture(&surfaceTexture);

	Texture tankTexture1a;
	Texture tankTexture1b;
	tankTexture1a.loadFromFile("textures/tank4a.png");
	tankTexture1b.loadFromFile("textures/tank4b.png");
	Tank tankLeft(150, 550, Vector2f(100, 55), 1000, 100, true, &tankTexture1a, &tankTexture1b);
	Tank tankRight(1050, 550, Vector2f(100, 55), 1000, 100, false, &tankTexture1a, &tankTexture1b);

	Texture explosionTexture;
	explosionTexture.loadFromFile("textures/explosion1.png");
	Explosion explosion(&explosionTexture);

	Texture bullet1;
	bullet1.loadFromFile("textures/bullet1.png");
	Vector2i mousePos = Mouse::getPosition(window);
	Bullet bullet(140, 580, 13, &bullet1);
	if (whoHasMove == 0) bullet.setX(140);
	else bullet.setX(1050);

	bullet.Update();

	while (window.isOpen()) {

		Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == evnt.Closed) {
				window.close();
			}
		}

		window.clear(Color(135, 206, 235));
		for (int i = 0; i < 160; i++) {
			surface.setSize(Vector2f(8, map[i]));
			surface.setPosition(i * 8, 720 - map[i]);
			surface.setTextureRect(IntRect(i * 8, 500 - map[i], 8, map[i]));
			window.draw(surface);
		}
		position1 = Vector2f(bullet.getX() + (bullet.getR() / 2), bullet.getY() + (bullet.getR() / 2));
		position2 = Vector2f(mousePos.x, mousePos.y);;

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!shoot) {
				x = bullet.getX();
				y = bullet.getY();
				mousePos = Mouse::getPosition(window);
				shoot = true;
				power = sqrt(pow((position2.y - position1.y), 2) + pow((position2.x - position1.x), 2)) / 8;
				angle = findAngle(bullet, mousePos);
				whoHasMove++;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (shoot) {

			bullet.removeOpacity();
			time += 0.1;
			Pos po = bullet.ballPath(x, y, power, angle, time);
			bullet.setX(po.x);
			if (po.y == bullet.getY()) {
				bullet.setRotation(-currentAngle);
			}
			bullet.setY(po.y);
			bullet.Update();

			stripeNumber = po.x / 8;
			if (po.x <= 1280 && po.x >=0) {
				if (map[stripeNumber] >= (720 - bullet.getY())) {

					//if (stripeNumber - 7 >= 0 && map[stripeNumber - 7] < 720) map[stripeNumber - 7] -= 2;
					//if (stripeNumber - 6 >= 0 && map[stripeNumber - 6] < 720) map[stripeNumber - 6] -= 10;
					if (stripeNumber - 5 >= 0 && map[stripeNumber - 5] < 720) map[stripeNumber - 5] -= 1;
					if (stripeNumber - 4 >= 0 && map[stripeNumber - 4] < 720) map[stripeNumber - 4] -= 9;
					if (stripeNumber - 3 >= 0 && map[stripeNumber - 3] < 720) map[stripeNumber - 3] -= 16;
					if (stripeNumber - 2 >= 0 && map[stripeNumber - 2] < 720) map[stripeNumber - 2] -= 21;
					if (stripeNumber - 1 >= 0 && map[stripeNumber - 1] < 720) map[stripeNumber - 1] -= 24;
					map[stripeNumber] -= 26;
					if (stripeNumber + 1 <= 159 && map[stripeNumber + 1] < 720) map[stripeNumber + 1] -= 24;
					if (stripeNumber + 2 <= 159 && map[stripeNumber + 2] < 720) map[stripeNumber + 2] -= 21;
					if (stripeNumber + 3 <= 159 && map[stripeNumber + 3] < 720) map[stripeNumber + 3] -= 16;
					if (stripeNumber + 4 <= 159 && map[stripeNumber + 4] < 720) map[stripeNumber + 4] -= 9;
					if (stripeNumber + 5 <= 159 && map[stripeNumber + 5] < 720) map[stripeNumber + 5] -= 1;
					//if (stripeNumber + 6 <= 159 && map[stripeNumber + 6] < 720) map[stripeNumber + 6] -= 10;
					//if (stripeNumber + 7 <= 159 && map[stripeNumber + 7] < 720) map[stripeNumber + 7] -= 2;

					if (po.y-50 < 720)
						explosion.boom(po.x-50, po.y-50);
					else
						explosion.boom(po.x - 50,  680);

					cout << "\nCollision";
					shoot = false;
					time = 0;
					if (bullet.getY() > 720) {
						bullet.setY(720);
					}
					if (whoHasMove % 2 == 0) {
						bullet.setX(150);
						bullet.setY(720 - map[18] - 20);
						//tankRight.updateGun(180);
					}
					else {
						bullet.setX(1050);
						bullet.setY(720 - map[132] - 20);
						//tankLeft.updateGun(0);
					}
					bullet.Update();
				}
					
			}
			else {
				shoot = false;
				time = 0;
				bullet.setY(720 - map[18] - 20);
				if (whoHasMove % 2 == 0) bullet.setX(150);
				else bullet.setX(1050); 
				bullet.Update();
			}
				
		}
		else {
			mousePos = Mouse::getPosition(window);
			currentAngle = findAngle(bullet, mousePos) * -57.2957795;
			cout << currentAngle << endl;
			if (whoHasMove % 2 == 0) tankLeft.updateGun(currentAngle);
			else tankRight.updateGun(currentAngle);
			
			bullet.setRotation(currentAngle);
			if (whoHasMove % 2 == 0) {
				bullet.UpdateY(720 - map[18] - 20);
			}
			else {
				bullet.UpdateY(720 - map[132] - 20);
			}
			bullet.addOpacity();

			arrow.setPosition(Vector2f(mousePos.x,mousePos.y));
			arrow.setRotation(currentAngle);

			window.draw(arrow);

		}

		
		mousePos = Mouse::getPosition(window);
		bullet.Draw(window);
		explosion.Draw(window);
		tankLeft.Update(720 - map[18] - 25);
		tankRight.Update(720 - map[130] - 25);
		tankLeft.Draw(window);
		tankRight.Draw(window);
		//window.draw(explosion1);
		window.display();

	}

	return 0;
}