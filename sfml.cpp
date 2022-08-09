#include <SFML/Graphics.hpp>	

using namespace sf;
class Target:public Drawable {
private:
	Vector2f loc;
	float radius;
	int score;
	public:
	Target(float radius, Vector2f loc) {
		this->radius = radius;
		this->loc = loc;
		score = calc();
	}
	int calc() {
		return 80 - radius;
	}
	void draw(RenderTarget &target,RenderStates states)const override {
		CircleShape circle(radius);
		circle.setFillColor(Color(255,155,0));
		circle.setOutlineThickness(radius / 10);
		circle.setOutlineColor(Color(98,0,255));
		circle.setPosition(Vector2f(loc));
		target.draw(circle);
	}
};
int main()
{

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(500, 300), "SFML Works!");

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его
		}
		window.clear(Color(255,255,255));
		Target target(12,Vector2f(150,200));
		window.draw(target);
		window.display();
	}

	return 0;
}