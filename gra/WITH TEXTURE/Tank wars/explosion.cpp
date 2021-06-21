#include "explosion.h"

Explosion::Explosion(Texture* texture, bool end) {
	if (!end) {
		body.setSize(Vector2f(100, 100));
		body.setTexture(texture);
		body.setTextureRect(IntRect(400, 300, 100, 100));
		body.setPosition(100, 100);
	}
	else {
		body.setSize(Vector2f(1280, 1280));
		body.setTexture(texture);
		body.setTextureRect(IntRect(5120, 5840, 1280, 1280));
		body.setPosition(0, 0);
		body.setOrigin(0, 300);
	}
	this->ending = end;
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
	if (!ending) {
		if (step > -1) {
			//body.setTextureRect(IntRect(100*step, 0, 100, 100));
			if (step > 4)
				body.setTextureRect(IntRect(100 * (step - 4), 100, 100, 100));
			if (step > 9)
				body.setTextureRect(IntRect(100 * (step - 9), 200, 100, 100));
			if (step > 14)
				body.setTextureRect(IntRect(100 * (step - 14), 300, 100, 100));
			if (step > 20) step = -1;
			if (step < 20 && step > -1) step++;
		}
	}
	else {
		if (step > -1) {
			//body.setTextureRect(IntRect(100*step, 0, 100, 100));
			if (step > 4)
				body.setTextureRect(IntRect(1280 * (int(step) - 4), 1280, 1280, 1280));
			if (step > 9)
				body.setTextureRect(IntRect(1280 * (int(step) - 9), 2560, 1280, 1280));
			if (step > 14)
				body.setTextureRect(IntRect(1280 * (int(step) - 14), 3840, 1280, 1280));
			if (step >= 20) step = -1;
			if (step < 20 && step > -1) step += 0.2;
		}
	}
	
}
