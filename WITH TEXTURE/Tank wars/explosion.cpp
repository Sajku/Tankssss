#include "explosion.h"

Explosion::Explosion(Texture* texture) {
	body.setSize(Vector2f(100,100));
	body.setTexture(texture);
	body.setTextureRect(IntRect(400, 300, 100, 100));
	body.setPosition(100, 100);
	this->step = -1;
}

Explosion::~Explosion() {
}

void Explosion::Draw(RenderWindow& window) {
	this->Update();
	window.draw(body);
}

void Explosion::boom(double x, double y) {
	body.setPosition(x,y);
	this->step = 5;
}

void Explosion::Update() {
	if (step > -1) {
		//body.setTextureRect(IntRect(100*step, 0, 100, 100));
		if (step > 4) 
			body.setTextureRect(IntRect(100 * (step-5), 100, 100, 100));
		if (step > 9)
			body.setTextureRect(IntRect(100 * (step - 10), 200, 100, 100));
		if (step > 14)
			body.setTextureRect(IntRect(100 * (step - 15), 300, 100, 100));
		if (step > 20) step = -1;
		if (step < 20) step++;
	}
}
