#pragma once
#include<SFML/Graphics.hpp>
class Target :public sf::Drawable {
private:
	sf::Vector2f speed{ 400,300 };
	sf::Vector2f loc;
	float c = 0;
	bool stepDir=true;
	float radius;
	int score;
public:
	Target(float radius, sf::Vector2f loc);
	int calc()const ;
	void move(float delta);
	int shot(int x, int y)const;
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	int locY();
};

