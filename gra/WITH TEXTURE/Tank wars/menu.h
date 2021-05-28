#pragma once
#include "all.h"

class Menu {
public:
	Menu(RenderWindow* window);
	~Menu();
	void run();
	void choose(int mX, int mY);

private:
	RenderWindow* window;
	Event winEvent;
	Vector2i mousePos;

	Texture bannerTexture;
	RectangleShape banner;
	RectangleShape playButton;
	RectangleShape creditsButton;
	RectangleShape quitButton;
	
	RectangleShape credits;
	RectangleShape creditsBackButton;

	FloatRect button1;
	FloatRect button2;
	FloatRect button3;
	FloatRect button4;

	Font font;
	Text text1;
	Text text2;
	Text text3;

	int mX;
	int mY;
	
	bool menuOpen;
	bool creditsOpen;
};