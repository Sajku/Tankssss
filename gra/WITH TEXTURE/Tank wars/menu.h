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

	Texture cursorMenuT;
	RectangleShape cursorMenu;

	Texture bannerTexture;
	Texture backgroundTexture;
	RectangleShape banner;
	RectangleShape background;
	RectangleShape info;

	Texture infoT;
	Texture playBtnT;
	Texture infoBtnT;
	Texture quitBtnT;
	Texture menuBtnT;
	Texture playBtnTHover;
	Texture infoBtnTHover;
	Texture quitBtnTHover;
	Texture menuBtnTHover;
	RectangleShape playButton;
	RectangleShape infoButton;
	RectangleShape quitButton;
	RectangleShape menuButton;


	Texture endingT;
	RectangleShape ending;

	FloatRect playBtn;
	FloatRect infoBtn;
	FloatRect quitBtn;
	FloatRect menuBtn;


	int mX;
	int mY;
	
	bool menuOpen;
	bool creditsOpen;
	bool endingOpen;
};