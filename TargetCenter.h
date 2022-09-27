#pragma once
#include<SFML/Graphics.hpp>
#include"Target.h"
class TargetCenter :public sf::Drawable
{
	std::vector<Target> arr;
	sf::Vector2f screen;
	int max = 7;
public:
	TargetCenter(sf::Vector2f screen);
	void trySpamn();
	void move(float delta);
	void make(int radius, sf::Vector2f loc);
	int shotCheck(int x, int y);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	void clean();
	void tick(float delta);
};

