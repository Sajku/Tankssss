#include <iostream>
#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "tank.h"
#include "explosion.h"
#include <fstream>
#define M_PI 3.14159265358979323846

using namespace sf;
using namespace std;

double findAngle(Ball ball, Vector2i mousePos) {

	double sX = ball.getX();
	double sY = ball.getY();
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

	double time = 0;
	double power = 0;
	double angle = 0;
	bool shoot = false;
	bool collided = false;
	double x = 0;
	double y = 0;
	bool mapChanged = true;
	int stripeNumber = 0;
	double currentAngle = 0;

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

	Vector2i mousePos = Mouse::getPosition(window);
	Ball ball(150, 580, 13);
	RectangleShape surface;
	surface.setSize(Vector2f(8, 360));
	//surface.setFillColor(Color(25, 137, 8));
	
	RectangleShape arrow;
	Texture arrowTexture;
	arrow.setSize(Vector2f(100, 50));
	arrow.setOrigin(95,25);
	arrowTexture.loadFromFile("arrow.png");
	arrowTexture.setSmooth(true);
	arrow.setTexture(&arrowTexture);

	Texture surfaceTexture;
	surfaceTexture.loadFromFile("grass1.jpg");
	surface.setTexture(&surfaceTexture);

	Texture tankTexture1;
	tankTexture1.loadFromFile("tank1.png");
	Tank tankLeft(150, 550, Vector2f(100, 55), 1000, 100, true, &tankTexture1);
	Tank tankRight(1050, 550, Vector2f(100, 55), 1000, 100, false, &tankTexture1);

	Texture explosionTexture;
	explosionTexture.loadFromFile("explosion1.png");
	Explosion explosion(&explosionTexture);

	/*RectangleShape explosion1;
	explosion1.setSize(Vector2f(100,100));
	explosion1.setTexture(&explosionTexture1);
	explosion1.setTextureRect(IntRect(100, 0, 100, 100));
	explosion1.setPosition(500, 500);
	explosion1.setOrigin(50, 50);*/
	
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
		position1 = Vector2f(ball.getX() + (ball.getR() / 2), ball.getY() + (ball.getR() / 2));
		position2 = Vector2f(mousePos.x, mousePos.y);;

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!shoot) {
				x = ball.getX();
				y = ball.getY();
				mousePos = Mouse::getPosition(window);
				shoot = true;
				power = sqrt(pow((position2.y - position1.y), 2) + pow((position2.x - position1.x), 2)) / 8;
				angle = findAngle(ball, mousePos);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (shoot) {

			time += 0.1;
			Pos po = ball.ballPath(x, y, power, angle, time);
			ball.setX(po.x);
			if (po.y == ball.getY()) {
				ball.setRotation(-currentAngle);
			}
			ball.setY(po.y);
			ball.Update();

			stripeNumber = po.x / 8;
			if (po.x <= 1280 && po.x >=0) {
				if (map[stripeNumber] >= (720 - ball.getY())) {

					if (stripeNumber - 7 >= 0 && map[stripeNumber - 7] < 720) map[stripeNumber - 7] -= 2;
					if (stripeNumber - 6 >= 0 && map[stripeNumber - 6] < 720) map[stripeNumber - 6] -= 10;
					if (stripeNumber - 5 >= 0 && map[stripeNumber - 5] < 720) map[stripeNumber - 5] -= 20;
					if (stripeNumber - 4 >= 0 && map[stripeNumber - 4] < 720) map[stripeNumber - 4] -= 28;
					if (stripeNumber - 3 >= 0 && map[stripeNumber - 3] < 720) map[stripeNumber - 3] -= 35;
					if (stripeNumber - 2 >= 0 && map[stripeNumber - 2] < 720) map[stripeNumber - 2] -= 40;
					if (stripeNumber - 1 >= 0 && map[stripeNumber - 1] < 720) map[stripeNumber - 1] -= 42;
					map[stripeNumber] -= 44;
					if (stripeNumber + 1 <= 159 && map[stripeNumber + 1] < 720) map[stripeNumber + 1] -= 42;
					if (stripeNumber + 2 <= 159 && map[stripeNumber + 2] < 720) map[stripeNumber + 2] -= 40;
					if (stripeNumber + 3 <= 159 && map[stripeNumber + 3] < 720) map[stripeNumber + 3] -= 35;
					if (stripeNumber + 4 <= 159 && map[stripeNumber + 4] < 720) map[stripeNumber + 4] -= 28;
					if (stripeNumber + 5 <= 159 && map[stripeNumber + 5] < 720) map[stripeNumber + 5] -= 20;
					if (stripeNumber + 6 <= 159 && map[stripeNumber + 6] < 720) map[stripeNumber + 6] -= 10;
					if (stripeNumber + 7 <= 159 && map[stripeNumber + 7] < 720) map[stripeNumber + 7] -= 2;

					if (po.y-50 < 720)
						explosion.boom(po.x-50, po.y-50);
					else
						explosion.boom(po.x - 50,  680);

					cout << "\nCollision";
					shoot = false;
					time = 0;
					ball.setY(720 - map[18] - 20);
					if (ball.getY() > 720) {
						ball.setY(720);
					}
					ball.setX(150);
					ball.Update();
				}
					
			}
			else {
				if (720 - ball.getY() < 0) {
					shoot = false;
					time = 0;
					ball.setY(720 - map[18] - 20);
					ball.setX(150);
					ball.Update();
				}
			}
				
		}
		else {
			mousePos = Mouse::getPosition(window);
			currentAngle = findAngle(ball, mousePos) * -57.2957795;
			cout << currentAngle << endl;
			ball.setRotation(currentAngle);
			ball.UpdateY(720 - map[18] - 20);
			
			arrow.setPosition(Vector2f(mousePos.x,mousePos.y));
			arrow.setRotation(currentAngle);

			window.draw(arrow);

		}

		
		mousePos = Mouse::getPosition(window);
		ball.Draw(window);
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