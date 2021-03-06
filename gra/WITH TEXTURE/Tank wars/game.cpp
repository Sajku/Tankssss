#include "all.h"

// RANDOM NUMBERS GENERATOR
int randomNum(int min, int max) {
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution <int> numer(min, max);
	return numer(generator);
}

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
	this->endingOpen = false;
	this->end = false;



	// =============== SFML ELEMENTS SETTING ===============
	// =============== TEXTURES LOADING ===============

	this->arrowTexture.loadFromFile("textures/arrow.png");
	this->arrowTexture.setSmooth(true);		

	switch (randomNum(0, 2)) {
	case 0:
		this->surfaceTexture.loadFromFile("textures/stone.png");
		break;
	case 1:
		this->surfaceTexture.loadFromFile("textures/sand.png");
		break;
	case 2:
		this->surfaceTexture.loadFromFile("textures/grass.png");
		break;
	}

	int colorTank1 = randomNum(1, 4);
	int colorTank2{};
	do {
		colorTank2 = randomNum(1, 4);
	} while (colorTank1 == colorTank2);

	switch (colorTank1) {
	case 1:
		this->tankTexture1a.loadFromFile("textures/tanks/tank1a.png");
		this->tankTexture1b.loadFromFile("textures/tanks/tank1b.png");
		this->destroyedTankTexture1.loadFromFile("textures/tanks/destroyed1.png");
		break;
	case 2:
		this->tankTexture1a.loadFromFile("textures/tanks/tank2a.png");
		this->tankTexture1b.loadFromFile("textures/tanks/tank2b.png");
		this->destroyedTankTexture1.loadFromFile("textures/tanks/destroyed2.png");
		break;
	case 3:
		this->tankTexture1a.loadFromFile("textures/tanks/tank3a.png");
		this->tankTexture1b.loadFromFile("textures/tanks/tank3b.png");
		this->destroyedTankTexture1.loadFromFile("textures/tanks/destroyed3.png");
		break;
	case 4:
		this->tankTexture1a.loadFromFile("textures/tanks/tank4a.png");
		this->tankTexture1b.loadFromFile("textures/tanks/tank4b.png");
		this->destroyedTankTexture1.loadFromFile("textures/tanks/destroyed4.png");
		break;
	}

	switch (colorTank2) {
	case 1:
		this->tankTexture2a.loadFromFile("textures/tanks/tank1a.png");
		this->tankTexture2b.loadFromFile("textures/tanks/tank1b.png");
		this->destroyedTankTexture2.loadFromFile("textures/tanks/destroyed1.png");
		break;
	case 2:
		this->tankTexture2a.loadFromFile("textures/tanks/tank2a.png");
		this->tankTexture2b.loadFromFile("textures/tanks/tank2b.png");
		this->destroyedTankTexture2.loadFromFile("textures/tanks/destroyed2.png");
		break;
	case 3:
		this->tankTexture2a.loadFromFile("textures/tanks/tank3a.png");
		this->tankTexture2b.loadFromFile("textures/tanks/tank3b.png");
		this->destroyedTankTexture2.loadFromFile("textures/tanks/destroyed3.png");
		break;
	case 4:
		this->tankTexture2a.loadFromFile("textures/tanks/tank4a.png");
		this->tankTexture2b.loadFromFile("textures/tanks/tank4b.png");
		this->destroyedTankTexture2.loadFromFile("textures/tanks/destroyed4.png");
		break;
	}


	this->explosionTexture.loadFromFile("textures/explosion1.png");
	this->endingExplosionTexture.loadFromFile("textures/explosionEND.png");
	this->tankLeftHPT.loadFromFile("textures/HP-L.png");
	this->tankRightHPT.loadFromFile("textures/HP-R.png");
	this->bulletTexture.loadFromFile("textures/bullet1.png");
	this->backgroundTexture.loadFromFile("textures/background.png");

	// =============== SFML ELEMENTS SETTING ===============
	// =============== ESSENTIALS ===============

	this->window = window;
	// this->window->setFramerateLimit(60);
	// this->window->setMouseCursorVisible(false);
	this->mousePos = Mouse::getPosition(*window);

	// =============== SFML ELEMENTS SETTING ===============
	// =============== GAME ELEMENTS ===============

	this->ground.setSize(Vector2f(8, 360));
	this->background.setSize(Vector2f(1280, 720));
	this->background.setTexture(&backgroundTexture);
	this->background.setPosition(0, 0);
	this->arrow.setSize(Vector2f(86, 44));
	this->arrow.setOrigin(84, 22);
	this->arrow.setTexture(&arrowTexture);
	this->ground.setTexture(&surfaceTexture);
	this->tankLeftHP.setSize(Vector2f(210, 73));
	this->tankLeftHP.setPosition(25, 25);
	this->tankLeftHP.setTexture(&tankLeftHPT);
	this->tankRightHP.setSize(Vector2f(210, 73));
	this->tankRightHP.setOrigin(210, 0);
	this->tankRightHP.setPosition(1255, 25);
	this->tankRightHP.setTexture(&tankRightHPT);
	this->bullet = Bullet(140, 580, 13, &bulletTexture);

	this->font.loadFromFile("textures/Chalkduster400.ttf");
	this->leftHP.setFont(font);
	this->leftHP.setCharacterSize(45);
	this->leftHP.setFillColor(Color::Black);
	this->leftHP.setStyle(Text::Bold);
	this->leftHP.setString("100");
	this->leftHP.setOrigin(leftHP.getLocalBounds().width / 2, 0);
	this->leftHP.setPosition(177, 34);

	this->rightHP.setFont(font);
	this->rightHP.setCharacterSize(45);
	this->rightHP.setFillColor(Color::Black);
	this->rightHP.setStyle(Text::Bold);
	this->rightHP.setString("100");
	this->rightHP.setOrigin(leftHP.getLocalBounds().width / 2, 0);
	this->rightHP.setPosition(1103, 34);

	// PROPER BULLET PLACEMENT AT THE START
	if (this->whoHasMove == 0) bullet.setX(140);
	else bullet.setX(1130);
	this->endingT.loadFromFile("textures/menu/theend.png");
	this->ending.setSize(Vector2f(1280, 720));
	this->ending.setPosition(0, 0);
	this->ending.setTexture(&endingT);

	this->winTexture.loadFromFile("textures/win_1.png");
	this->win.setSize(Vector2f(1280, 720));
	this->win.setPosition(0, 0);
	this->win.setTexture(&winTexture);

	// =============== MAP RANDOM CHOOSING AND LOADING FROM FILE ===============

	// RANDOM MAP CHOOSING

	string mapa[6] = { "maps/map_2.txt", "maps/map_3.txt", "maps/map_4.txt", "maps/map_5.txt", "maps/map_6.txt", "maps/map_7.txt" };
	int mapNumber = randomNum(0, 5);
	string str = "";
	int count = 0;
	ifstream file(mapa[mapNumber]);
	if (file.good()) {
		while (!file.eof()) {
			file >> str;
			map[count] = stoi(str);
			count++;
		}
	}

}

void Game::run() {

	// MAIN GAME LOOP
	while (this->window->isOpen()) {

		if (endingOpen) {
			if (this->winEvent.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				window->draw(ending);
				window->display();
				this_thread::sleep_for(chrono::milliseconds(2000));

				window->close();

			}
		}
		else {
			// WINDOW AND KEYBOARD EVENTS LISTENER
			while (this->window->pollEvent(this->winEvent)) {
				if (this->winEvent.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
					endingOpen = true;
				}
			}

			// BACKGROUND AND GROUND PRINTING
			//window->clear(Color(135, 206, 235));
			window->draw(background);
			for (int i = 0; i < 160; i++) {
				ground.setSize(Vector2f(8, map[i]));
				ground.setPosition(i * 8, 720 - map[i]);
				ground.setTextureRect(IntRect(i * 8, 720 - map[i], 8, map[i]));
				window->draw(ground);
			}
			position1 = Vector2f(bullet.getX() + (bullet.getR() / 2), bullet.getY() + (bullet.getR() / 2));
			position2 = Vector2f(mousePos.x, mousePos.y);;


			// SHOOTING LISTENER
			if (!end) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (position2.x >= 0 && position2.x <= 1280 && position2.y >= 0 && position2.y <= 720) {
						if (!shoot) {
							x = bullet.getX();
							y = bullet.getY();
							shoot = true;
							power = sqrt(pow((position2.y - position1.y), 2) + pow((position2.x - position1.x), 2)) / 8;
							angle = findAngle(bullet, mousePos);
							whoHasMove++;
						}
					}
				}
			}

			if (shoot) {
				bulletInAir();
			}
			else {
				if (!end) bulletInTank();
			}

			// GAME ELEMENT DRAWING
			bullet.Draw(*window);
			
			tankLeft.Update(720 - map[18] - 25);
			tankRight.Update(720 - map[141] - 25);

			tankLeft.Draw(*window);
			tankRight.Draw(*window);
			if (!end) {
				leftHP.setString(tankLeft.getHPString());
				rightHP.setString(tankRight.getHPString());
				window->draw(tankLeftHP);
				window->draw(tankRightHP);
				window->draw(leftHP);
				window->draw(rightHP);
			}
			else {
				window->draw(win);
			}
			
			explosion.Draw(*window);
			endingExplosion.Draw(*window);
			//window.draw(explosion1);
			this->window->display();
		}
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

			if (whoHasMove % 2 == 0)
			{
				// LEFT TANK COLLISION
				if (abs(bullet.getY() - tankLeft.getY()) < 100 && abs(bullet.getX() - tankLeft.GetX()) < 50) tankLeft.DecreaseHP(rand() % 5 + 10);
			}
			if (whoHasMove % 2 == 1)
			{
				// RIGHT TANK COLLISION
				if (abs(bullet.getY() - tankRight.getY()) < 100 && abs(bullet.getX() - tankRight.GetX()) < 50) tankRight.DecreaseHP(rand() % 5 + 10);
			}
			if (!end) bulletHitGround(po);
		}

	}
	else {
		// WINDOW WALLS COLLISION
		shoot = false;
		time = 0;
		bullet.setY(720 - map[18] - 20);
		if (whoHasMove % 2 == 0) bullet.setX(150);
		else bullet.setX(1130);
		bullet.Update();
	}
}

void Game::bulletInTank() {
	// ARROW AND TANKS GUN ROTATION BEFORE SHOT
	mousePos = Mouse::getPosition(*window);
	currentAngle = findAngle(bullet, mousePos) * -57.2957795;
	// cout << currentAngle << endl;
	if (whoHasMove % 2 == 0) tankLeft.updateGun(currentAngle);
	else tankRight.updateGun(currentAngle);

	// A BULLET POSITION BEFORE SHOT
	bullet.setRotation(currentAngle);
	if (whoHasMove % 2 == 0) {
		bullet.UpdateY(720 - map[18] - 20);
	}
	else {
		bullet.UpdateY(720 - map[141] - 20);
	}
	bullet.addOpacity();

	arrow.setPosition(Vector2f(mousePos.x, mousePos.y));
	arrow.setRotation(currentAngle);

	if (!end) this->window->draw(arrow);
}

void Game::bulletHitGround(Pos po) {

	// MAKING A HOLE IN A GROUND, ON BULLET COLLISION WITH GROUND
	holeMaker();

	// ENDING SHOT
	if (tankLeft.getHP() <= 0 || tankRight.getHP() <= 0) {
		if (tankLeft.getHP() <= 0) {
			this->winTexture.loadFromFile("textures/win_2.png");
			this->win.setTexture(&winTexture);
			this->tankLeft.updateTexture(&destroyedTankTexture1);
		}
		else {
			this->tankRight.updateTexture(&destroyedTankTexture2);
		}

		win.setTexture(&winTexture);
		end = true;
		endingExplosion.boom(0, 0);

		cout << "\nCollision";
		shoot = false;
		time = 0;
		if (whoHasMove % 2 == 0) {
			bullet.setX(150);
			bullet.setY(720 - map[18] - 20);
			//tankRight.updateGun(180);
		}
		else {
			bullet.setX(1130);
			bullet.setY(720 - map[141] - 20);
			//tankLeft.updateGun(0);
		}
		bullet.Update();
	}
	else {
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
			bullet.setX(1130);
			bullet.setY(720 - map[141] - 20);
			//tankLeft.updateGun(0);
		}
		bullet.Update();
	}
	
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