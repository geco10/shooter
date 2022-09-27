#include "TargetCenter.h"
TargetCenter::TargetCenter(sf::Vector2f screen) {
	this->screen = screen;
}
void TargetCenter::trySpamn() {
	if (arr.size() < max) {
		int radius = rand() % 50 + 20;
		sf::Vector2f loc;
		loc.x = rand() % (int)screen.x;
		loc.y = radius * (-2);
		make(radius, loc);
	}
}
void TargetCenter::move(float delta) {
	for (int i = 0; i < arr.size(); ++i) {
		arr[i].move(delta);
	}
}
void TargetCenter::make(int radius, sf::Vector2f loc) {
	arr.push_back(Target(radius, loc));
}
int TargetCenter::shotCheck(int x, int y) {
	int Tscore = 0;
	for (int i = arr.size() - 1; i >= 0; --i) {
		int s = arr[i].shot(x, y);
		if (s > 0) {
			Tscore += s;
			arr.erase(arr.begin() + i);
		}
	}
	return Tscore;
}
void TargetCenter::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	for (int i = 0; i < arr.size(); ++i) {
		target.draw(arr[i]);
	}
}
void TargetCenter::clean() {
	for (int i = 0; i < arr.size(); i++) {
		if (screen.y < arr[i].locY()) arr.erase(arr.begin() + i);
	}
}
void TargetCenter::tick(float delta) {
	move(delta);
	trySpamn();
	clean();
}


