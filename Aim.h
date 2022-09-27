#pragma once
#include<SFML/Graphics.hpp>
class Aim :public sf::Drawable{
private:
	sf::Vector2f loc;
public:
	Aim() = default;
	void move(int x, int y);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};


