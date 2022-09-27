#include "GameScore.h"
GameScore::GameScore(sf::Vector2f screen) {
	this->screen = screen;
}
void GameScore::add(int a) {
	score += a;
}
void GameScore::intToStr(int a, char* res)const {
	int i = 0;
	do {
		res[i] = a % 10 + '0';
		res[i + 1] = '\0';
		++i;
		a /= 10;
	} while (a != 0);
	for (int j = 0; j < i / 2; ++j) {
		char t = res[j];
		res[j] = res[i - 1 - j];
		res[i - 1 - j] = t;
	}
}
void GameScore::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	char scoreStr[100];
	intToStr(score, scoreStr);
	char v[60] = "score: ";
	strcat_s(v, scoreStr);
	int a = strlen(v);
	sf::Font font;
	font.loadFromFile("Top Secret.ttf");
	sf::Text text(v, font, 20u);
	text.setFillColor(sf::Color(0, 0, 0));
	text.setPosition(sf::Vector2f((screen.x - 10) - a * 10, 0));
	target.draw(text);
}