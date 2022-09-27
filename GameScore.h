#pragma once
#include<SFML/Graphics.hpp>
class GameScore :public sf::Drawable {
private:
	int score=0;
	sf::Vector2f screen;
public:
	GameScore(sf::Vector2f screen);
	void add(int a);
	void intToStr(int a, char* res)const;
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

