#include "all.h"

Menu::Menu(RenderWindow* window) {
	this->window = window;
	this->mousePos = Mouse::getPosition(*window);

	this->bannerTexture.loadFromFile("textures/banner.png");

	this->banner.setSize(Vector2f(1280, 720));
	this->banner.setPosition(0, 0);
	this->banner.setTexture(&bannerTexture);

	this->playButton.setSize(Vector2f(300, 100));
	this->playButton.setOrigin(150, 0);
	this->playButton.setPosition(640, 300);
	this->playButton.setFillColor(Color(50,100,50));
	this->creditsButton.setSize(Vector2f(300, 100));
	this->creditsButton.setOrigin(150, 0);
	this->creditsButton.setPosition(640, 450);
	this->creditsButton.setFillColor(Color(50, 100, 50));
	this->quitButton.setSize(Vector2f(300, 100));
	this->quitButton.setOrigin(150, 0);
	this->quitButton.setPosition(640, 600);
	this->quitButton.setFillColor(Color(50, 100, 50));

	this->credits.setSize(Vector2f(800, 500));
	this->credits.setOrigin(400, 0);
	this->credits.setPosition(640, 150);
	this->credits.setFillColor(Color(100, 50, 50));

	this->creditsBackButton.setSize(Vector2f(50, 50));
	this->creditsBackButton.setOrigin(00, 0);
	this->creditsBackButton.setPosition(25, 600);
	this->creditsBackButton.setFillColor(Color(25, 25, 150));

	this->menuOpen = true;
	this->creditsOpen = false;

	this->font.loadFromFile("textures/WarFont.ttf");
	this->text1.setFont(font);
	this->text1.setCharacterSize(50);
	this->text1.setFillColor(Color::Red);
	this->text1.setStyle(Text::Bold);
	this->text1.setString("Play");
	this->text1.setPosition(570, 315);

	this->text2.setFont(font);
	this->text2.setCharacterSize(50);
	this->text2.setFillColor(Color::Red);
	this->text2.setStyle(Text::Bold);
	this->text2.setString("Credits");
	this->text2.setPosition(530, 465);

	this->text3.setFont(font);
	this->text3.setCharacterSize(50);
	this->text3.setFillColor(Color::Red);
	this->text3.setStyle(Text::Bold);
	this->text3.setString("Quit");
	this->text3.setPosition(575, 615);

	this->button1 = playButton.getGlobalBounds();
	this->button2 = creditsButton.getGlobalBounds();
	this->button3 = quitButton.getGlobalBounds();
	this->button4 = creditsBackButton.getGlobalBounds();
}

Menu::~Menu() {}

void Menu::run() {

	while (this->window->isOpen() && menuOpen) {

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

		if (Mouse::isButtonPressed(Mouse::Left)) {
			mousePos = Mouse::getPosition(*window);
			choose(mousePos.x, mousePos.y);
		}

		if (creditsOpen) {
			window->clear(Color(150, 150, 150));
			window->draw(credits);
			window->draw(creditsBackButton);
			window->display();
		}
		else {
			window->clear(Color(150, 150, 150));

			window->draw(banner);
			window->draw(playButton);
			window->draw(creditsButton);
			window->draw(quitButton);
			window->draw(text1);
			window->draw(text2);
			window->draw(text3);
			window->display();
		}
	}
}

void Menu::choose(int mX, int mY) {
	
	if (!creditsOpen) {
		if (button1.contains(mX, mY)) {
			cout << "\n1. BUTTON";
			menuOpen = false;
		}

		if (button2.contains(mX, mY)) {
			cout << "\n2. BUTTON";
			creditsOpen = true;
		}

		if (button3.contains(mX, mY)) {
			cout << "\n3. BUTTON";
			window->close();
		}
	}
	else {
		if (button4.contains(mX, mY)) {
			cout << "\nBACK TO MENU";
			creditsOpen = false;
			menuOpen = true;
		}
	}
	
}
