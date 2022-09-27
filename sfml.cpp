﻿#include <SFML/Graphics.hpp>
#include<string.h>
#include<windows.h>
#include <cmath>
#include"TargetCenter.h"
#include"Target.h"
#include"Aim.h"
using namespace sf;

//class Aim :public Drawable{
//private:
//	Vector2f loc;
//public:
//	Aim() = default;
//	void move(int x,int y) {
//		loc.x = x;
//		loc.y = y;
//	}
//	void draw(RenderTarget& target, RenderStates states)const override {
//		CircleShape circle1(15);
//		circle1.setFillColor(Color(0,0,0,0));
//		circle1.setOutlineThickness(2);
//		circle1.setOutlineColor(Color(255, 0, 0));
//		circle1.setPosition(Vector2f(loc.x-15,loc.y-15));
//		target.draw(circle1);
//
//		CircleShape circle2(2);
//		circle2.setFillColor(Color(255,0, 0));
//		circle2.setPosition(Vector2f(loc));
//		target.draw(circle2);
//	}
//};
class GameScore:public Drawable{
private:
	int score=0;
	Vector2f screen;
public:
	GameScore(Vector2f screen) {
		this->screen = screen;
	}
	void add(int a) {
		score += a;
	}
	void intToStr(int a,char* res)const {
		int i = 0;
		do{
			res[i] = a % 10+'0';
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
	void draw(RenderTarget& target, RenderStates states)const override {
		char scoreStr[100];
		intToStr(score, scoreStr);
		char v[60] = "score: ";
		strcat_s(v,scoreStr);
		int a = strlen(v);
		Font font;
		font.loadFromFile("Top Secret.ttf");
		Text text(v, font, 20u);
		text.setFillColor(Color(0, 0, 0));
		text.setPosition(Vector2f((screen.x-10)-a*10,0));
		target.draw(text);
	}
};
size_t toMilliseconds(SYSTEMTIME time) {
	return time.wHour * 3600000 + time.wMinute * 60000 +time.wSecond*1000 + time.wMilliseconds;
}
int main()
{
	srand(time(NULL));
	Vector2f size(925, 700);
	GameScore sc(size);
	TargetCenter tc(size);
	Aim aim;
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(size.x, size.y), "SFML Works!");
	// Главный цикл приложения: выполняется, пока открыто окно
	SYSTEMTIME time;
	GetLocalTime(&time);
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем ег
			if (event.type == Event::MouseButtonPressed) {
				int s = tc.shotCheck(event.mouseButton.x,event.mouseButton.y);
				sc.add(s);

			}
			if (event.type == Event::MouseMoved) {
				//aim.move(event.mouseButton.x, event.mouseButton.y);
				aim.move(event.mouseMove.x, event.mouseMove.y);
			}
		}

		window.clear(Color(0, 255, 0));
		SYSTEMTIME time1;
		GetLocalTime(&time1);
		int delta = toMilliseconds(time1) - toMilliseconds(time);
		time = time1;
		tc.tick(delta/1000.f);
		window.draw(tc);
		window.draw(aim);
		window.draw(sc);
		window.display();
	}

	return 0;
}