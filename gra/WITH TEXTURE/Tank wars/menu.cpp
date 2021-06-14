#include "all.h"

Menu::Menu(RenderWindow* window) {
	this->window = window;
	this->mousePos = Mouse::getPosition(*window);

	this->cursorMenuT.loadFromFile("textures/menu/cursor.png");
	this->cursorMenu.setSize(Vector2f(50, 50));
	this->cursorMenu.setOrigin(25, 25);
	this->cursorMenu.setPosition(640, 370);
	this->cursorMenu.setTexture(&cursorMenuT);

	this->bannerTexture.loadFromFile("textures/menu/banner.png");
	this->backgroundTexture.loadFromFile("textures/menu/background-menu.png");

	this->banner.setSize(Vector2f(1280, 720));
	this->banner.setPosition(0, 0);
	this->banner.setTexture(&bannerTexture);
	
	this->infoT.loadFromFile("textures/menu/game_info.png");
	this->info.setSize(Vector2f(1280, 720));
	this->info.setPosition(0, 0);
	this->info.setTexture(&infoT);

	this->background.setSize(Vector2f(1280, 720));
	this->background.setPosition(0, 0);
	this->background.setTexture(&backgroundTexture);

	this->playBtnT.loadFromFile("textures/menu/play.png");
	this->infoBtnT.loadFromFile("textures/menu/info.png");
	this->quitBtnT.loadFromFile("textures/menu/quit.png");
	this->menuBtnT.loadFromFile("textures/menu/menu.png");
	this->playBtnTHover.loadFromFile("textures/menu/playH.png");
	this->infoBtnTHover.loadFromFile("textures/menu/infoH.png");
	this->quitBtnTHover.loadFromFile("textures/menu/quitH.png");
	this->menuBtnTHover.loadFromFile("textures/menu/menuH.png");

	this->playButton.setSize(Vector2f(268, 94));
	this->playButton.setOrigin(134, 0);
	this->playButton.setPosition(640, 330);
	this->playButton.setTexture(&playBtnT);
	this->infoButton.setSize(Vector2f(268, 94));
	this->infoButton.setOrigin(134, 0);
	this->infoButton.setPosition(640, 450);
	this->infoButton.setTexture(&infoBtnT);
	this->quitButton.setSize(Vector2f(268, 94));
	this->quitButton.setOrigin(134, 0);
	this->quitButton.setPosition(640, 570);
	this->quitButton.setTexture(&quitBtnT);
	this->menuButton.setSize(Vector2f(268, 94));
	this->menuButton.setOrigin(134, 0);
	this->menuButton.setPosition(640, 600);
	this->menuButton.setTexture(&menuBtnT);


	this->endingT.loadFromFile("textures/menu/theend.png");
	this->ending.setSize(Vector2f(1280,720));
	this->ending.setPosition(0, 0);
	this->ending.setTexture(&endingT);
	

	this->menuOpen = true;
	this->creditsOpen = false;

	this->playBtn = playButton.getGlobalBounds();
	this->infoBtn = infoButton.getGlobalBounds();
	this->quitBtn = quitButton.getGlobalBounds();
	this->menuBtn = menuButton.getGlobalBounds();

	this->mX = 0;
	this->mY = 0;
	this->endingOpen = false;
}

Menu::~Menu() {}

void Menu::run() {

	while (this->window->isOpen() && menuOpen) {

		// ENDING SCREEN
		if (endingOpen) {
			window->draw(ending);
			window->display();
			this_thread::sleep_for(chrono::milliseconds(300));

			if (Mouse::isButtonPressed(Mouse::Left))
				this->window->close();
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
		}
		// MENU 
		else {

			// WINDOW AND KEYBOARD EVENTS LISTENER
			while (this->window->pollEvent(this->winEvent))
			{
				switch (this->winEvent.type)
				{
				case Event::Closed:
					endingOpen = true;
					break;
				case Event::KeyPressed:
					if (this->winEvent.key.code == Keyboard::Escape)
						endingOpen = true;
					break;
				}
			}

			mousePos = Mouse::getPosition(*window);
			mX = mousePos.x;
			mY = mousePos.y;
			if (!creditsOpen) {
				if (playBtn.contains(mX, mY)) playButton.setTexture(&playBtnTHover);
				else playButton.setTexture(&playBtnT);

				if (infoBtn.contains(mX, mY)) infoButton.setTexture(&infoBtnTHover);
				else infoButton.setTexture(&infoBtnT);

				if (quitBtn.contains(mX, mY)) quitButton.setTexture(&quitBtnTHover);
				else quitButton.setTexture(&quitBtnT);

			}
			else {
				if (menuBtn.contains(mX, mY)) menuButton.setTexture(&menuBtnTHover);
				else menuButton.setTexture(&menuBtnT);
			}

			
			if (Mouse::isButtonPressed(Mouse::Left)) {

				choose(mousePos.x, mousePos.y);
			}

			cursorMenu.setPosition(mousePos.x, mousePos.y);


			if (creditsOpen) {
				window->draw(background);
				window->draw(info);
				window->draw(menuButton);
				window->draw(cursorMenu);
				window->display();
			}
			else {
				window->draw(background);
				window->draw(banner);
				window->draw(playButton);
				window->draw(infoButton);
				window->draw(quitButton);
				window->draw(cursorMenu);
				window->display();
			}
		}
	}

}

void Menu::choose(int mX, int mY) {
	
	if (!creditsOpen) {
		if (playBtn.contains(mX, mY)) {
			cout << "\n1. BUTTON";
			menuOpen = false;
		}

		if (infoBtn.contains(mX, mY)) {
			cout << "\n2. BUTTON";
			creditsOpen = true;
		}

		if (quitBtn.contains(mX, mY)) {
			cout << "\n3. BUTTON";
			endingOpen = true;
		}
	}
	else {
		if (menuBtn.contains(mX, mY)) {
			cout << "\nBACK TO MENU";
			creditsOpen = false;
			menuOpen = true;
			window->draw(background);
			window->draw(banner);
			window->draw(playButton);
			window->draw(infoButton);
			window->draw(quitButton);
			window->draw(cursorMenu);
			window->display();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	
}
