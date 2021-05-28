#include "all.h"

int main() {
	srand(time(NULL));

	RenderWindow window(VideoMode(1280, 720), "Top Tanks", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	Menu menu(&window);

	menu.run();

	Game tanks(&window);

	tanks.run();

	return 0;
}

