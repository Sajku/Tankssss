#include "all.h"

Game::Game(RenderWindow* window) {

	// =============== VARIABLES SETTING ===============
	this->time = 0;
	this->power = 0;
	this->angle = 0;
	this->shoot = false;
	this->collided = false;
	this->x = 0;
	this->y = 0;
	this->stripeNumber = 0;
	this->currentAngle = 0;
	int random1 = 0;
	random1 = rand() % 2;
	this->whoHasMove = random1;

	// =============== SFML ELEMENTS SETTING ===============
	// =============== TEXTURES LOADING ===============

	this->arrowTexture.loadFromFile("textures/arrow.png");
	this->arrowTexture.setSmooth(true);								// ??? IDK IF NEEDED
	this->surfaceTexture.loadFromFile("textures/grass1.jpg");
	this->tankTexture1a.loadFromFile("textures/tank4a.png");
	this->tankTexture1b.loadFromFile("textures/tank4b.png");
	this->explosionTexture.loadFromFile("textures/explosion1.png");
	this->bulletTexture.loadFromFile("textures/bullet1.png");
	this->backgroundTexture.loadFromFile("textures/background1.png");

	// =============== SFML ELEMENTS SETTING ===============
	// =============== ESSENTIALS ===============

	this->window = window;
	// this->window->setFramerateLimit(60);
	// this->window->setMouseCursorVisible(false);
	this->mousePos = Mouse::getPosition(*window);

	// =============== SFML ELEMENTS SETTING ===============
	// =============== GAME ELEMENTS ===============

	this->ground.setSize(Vector2f(8, 360));
	this->background.setSize(Vector2f(1280,720));
	this->background.setTexture(&backgroundTexture);
	this->background.setPosition(0,0);
	this->arrow.setSize(Vector2f(100, 50));
	this->arrow.setOrigin(95, 25);
	this->arrow.setTexture(&arrowTexture);
	this->ground.setTexture(&surfaceTexture);	
	this->explosion = Explosion(&explosionTexture);	
	this->bullet = Bullet(140, 580, 13, &bulletTexture);
	// PROPER BULLET PLACEMENT AT THE START
	if (this->whoHasMove == 0) bullet.setX(140);
	else bullet.setX(1050);

	// =============== MAP RANDOM CHOOSING AND LOADING FROM FILE ===============
	// TO DO -------------------------------------------------------------------------------------------------------------------------------------------
	// RANDOM MAP CHOOSING

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

}

Game::~Game() {}

void Game::run() {

	// MAIN GAME LOOP
	while (this->window->isOpen()) {

		// WINDOW AND KEYBOARD EVENTS LISTENER
		while (this->window->pollEvent(this->winEvent))
		{
			switch (this->winEvent.type)
			{
			case Event::Closed:
				this->window->close();
				break;
			case Event::KeyPressed:
				if (this->winEvent.key.code == Keyboard::Escape)
					this->window->close();
				break;
			}
		}

		// BACKGROUND AND GROUND PRINTING
		window->clear(Color(135, 206, 235));
		//window->draw(background);
		for (int i = 0; i < 160; i++) {
			ground.setSize(Vector2f(8, map[i]));
			ground.setPosition(i * 8, 720 - map[i]);
			ground.setTextureRect(IntRect(i * 8, 500 -  map[i], 8, map[i]));
			window->draw(ground);
		}
		position1 = Vector2f(bullet.getX() + (bullet.getR() / 2), bullet.getY() + (bullet.getR() / 2));
		position2 = Vector2f(mousePos.x, mousePos.y);;


		// SHOOTING LISTENER
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (!shoot) {
				x = bullet.getX();
				y = bullet.getY();
				shoot = true;
				power = sqrt(pow((position2.y - position1.y), 2) + pow((position2.x - position1.x), 2)) / 8;
				angle = findAngle(bullet, mousePos);
				whoHasMove++;
			}
		}

		if (shoot) {
			bulletInAir();
		}
		else {
			bulletInTank();
		}

		// GAME ELEMENT DRAWING
		bullet.Draw(*window);
		explosion.Draw(*window);
		tankLeft.Update(720 - map[18] - 25);
		tankRight.Update(720 - map[130] - 25);
		tankLeft.Draw(*window);
		tankRight.Draw(*window);
		//window.draw(explosion1);
		this->window->display();
	}
}

double Game::findAngle(Bullet bullet, Vector2i mousePos)
{
	// FINDING ANGLE BETWEEN BULLET AND CURSOR
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

void Game::bulletInAir() {
	
	// PROCESSING BULLET DURING SHOT
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

	// BULLET BEETWEEN WINDOW WALLS
	if (po.x <= 1278 && po.x >= 0) {

		// BULLET COLLISION DETECTION
		if (map[stripeNumber] >= (720 - bullet.getY())) {
			bulletHitGround(po);
		}

	}
	else {
		// WINDOW WALLS COLLISION
		shoot = false;
		time = 0;
		bullet.setY(720 - map[18] - 20);
		if (whoHasMove % 2 == 0) bullet.setX(150);
		else bullet.setX(1050);
		bullet.Update();
	}
}

void Game::bulletInTank() {
	// ARROW AND TANKS GUN ROTATION BEFORE SHOT
	mousePos = Mouse::getPosition(*window);
	currentAngle = findAngle(bullet, mousePos) * -57.2957795;
	cout << currentAngle << endl;
	if (whoHasMove % 2 == 0) tankLeft.updateGun(currentAngle);
	else tankRight.updateGun(currentAngle);

	// A BULLET POSITION BEFORE SHOT
	bullet.setRotation(currentAngle);
	if (whoHasMove % 2 == 0) {
		bullet.UpdateY(720 - map[18] - 20);
	}
	else {
		bullet.UpdateY(720 - map[132] - 20);
	}
	bullet.addOpacity();

	arrow.setPosition(Vector2f(mousePos.x, mousePos.y));
	arrow.setRotation(currentAngle);

	this->window->draw(arrow);
}

void Game::bulletHitGround(Pos po) {

	// MAKING A HOLE IN A GROUND, ON BULLET COLLISION WITH GROUND

	holeMaker();

	// EXPLOSION ANIMATION
	if (po.y - 50 < 720)
		explosion.boom(po.x - 50, po.y - 50);
	else
		explosion.boom(po.x - 50, 680);

	cout << "\nCollision";
	shoot = false;
	time = 0;

	// A BULLET PLACEMENT IN A PROPER TANK AFTER EXPLOSION
	
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

void Game::holeMaker() {
	//if (stripeNumber - 7 >= 0 && map[stripeNumber - 7] < 720) map[stripeNumber - 7] -= 2;
	//if (stripeNumber - 6 >= 0 && map[stripeNumber - 6] < 720) map[stripeNumber - 6] -= 10;
	if (stripeNumber - 5 >= 0 && map[stripeNumber - 5] > 0) map[stripeNumber - 5] -= 1;
	if (stripeNumber - 4 >= 0 && map[stripeNumber - 4] > 0) map[stripeNumber - 4] -= 9;
	if (stripeNumber - 3 >= 0 && map[stripeNumber - 3] > 0) map[stripeNumber - 3] -= 16;
	if (stripeNumber - 2 >= 0 && map[stripeNumber - 2] > 0) map[stripeNumber - 2] -= 21;
	if (stripeNumber - 1 >= 0 && map[stripeNumber - 1] > 0) map[stripeNumber - 1] -= 24;
	if (map[stripeNumber] > 0) map[stripeNumber] -= 26;
	if (stripeNumber + 1 <= 159 && map[stripeNumber + 1] > 0) map[stripeNumber + 1] -= 24;
	if (stripeNumber + 2 <= 159 && map[stripeNumber + 2] > 0) map[stripeNumber + 2] -= 21;
	if (stripeNumber + 3 <= 159 && map[stripeNumber + 3] > 0) map[stripeNumber + 3] -= 16;
	if (stripeNumber + 4 <= 159 && map[stripeNumber + 4] > 0) map[stripeNumber + 4] -= 9;
	if (stripeNumber + 5 <= 159 && map[stripeNumber + 5] > 0) map[stripeNumber + 5] -= 1;
	//if (stripeNumber + 6 <= 159 && map[stripeNumber + 6] < 720) map[stripeNumber + 6] -= 10;
	//if (stripeNumber + 7 <= 159 && map[stripeNumber + 7] < 720) map[stripeNumber + 7] -= 2;
}