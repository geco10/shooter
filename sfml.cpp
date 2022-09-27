#include <SFML/Graphics.hpp>
#include<string.h>
#include<windows.h>
#include <cmath>
#include"TargetCenter.h"
#include"Target.h"
#include"Aim.h"
#include"GameScore.h"
using namespace sf;

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