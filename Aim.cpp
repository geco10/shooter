#include "Aim.h"

void Aim::move(int x, int y) {
	loc.x = x;
	loc.y = y;
}
void Aim::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	sf::CircleShape circle1(15);
	circle1.setFillColor(sf::Color(0, 0, 0, 0));
	circle1.setOutlineThickness(2);
	circle1.setOutlineColor(sf::Color(255, 0, 0));
	circle1.setPosition(sf::Vector2f(loc.x - 15, loc.y - 15));
	target.draw(circle1);

	sf::CircleShape circle2(2);
	circle2.setFillColor(sf::Color(255, 0, 0));
	circle2.setPosition(sf::Vector2f(loc));
	target.draw(circle2);
}