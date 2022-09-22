#include "Target.h"
Target::Target(float radius, sf::Vector2f loc) {
		this->radius = radius;
		this->loc = loc;
		score = calc();
}
int Target::calc()const {
	return 70 - radius;
}
void Target::move(float delta) {
	c += delta;
	loc.y = loc.y + speed.y * delta;
	if (stepDir)loc.x = loc.x + speed.x * delta;
	else loc.x = loc.x - speed.x * delta;
	if (c >= 1) {
		c = 0;
		stepDir = !stepDir;
	}
}
int Target::shot(int x, int y)const {
	sf::Vector2f center(loc.x + radius, loc.y + radius);
	float d = sqrt((x - center.x) * (x - center.x) + (y - center.y) * (y - center.y));
	if (radius >= d) return score;
	else if (radius + (radius / 2) >= d) {
		return score / 3;
	}
	return 0;
}
void Target::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color(255, 255, 255));
	circle.setOutlineThickness(radius / 2);
	circle.setOutlineColor(sf::Color(255, 0, 0));
	circle.setPosition(sf::Vector2f(loc));
	target.draw(circle);
}
int Target::locY() {
	return loc.y;
}