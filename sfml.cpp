#include <SFML/Graphics.hpp>	

using namespace sf;
class Target:public Drawable {
private:
	Vector2f speed = {6,10};
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
	void move() {
		loc.y = loc.y + speed.y;
		loc.x = loc.x + speed.x;
	}
	void draw(RenderTarget& target, RenderStates states)const override {
		CircleShape circle(radius);
		circle.setFillColor(Color(255,255,255));
		circle.setOutlineThickness(radius / 2);
		circle.setOutlineColor(Color(255,0,0));
		circle.setPosition(Vector2f(loc));
		target.draw(circle);
	}
};
class TargetCenter :public Drawable{
	std::vector<Target> arr;
	Vector2f screen;
	int max=7;
public:
	TargetCenter(Vector2f screen) {
		this->screen=screen;
	}
	void move() {
		for (int i = 0; i < arr.size(); ++i) {
			arr[i].move();
		}
	}
	bool make(int radius,Vector2f loc) {
		arr.push_back(Target(radius,loc));
	}
	void draw(RenderTarget& target, RenderStates states)const override {
		for (int i = 0; i < arr.size(); ++i) {
			target.draw(arr[i]);
		}
	}
};
int main()
{

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(500, 300), "SFML Works!");
	Target target(16, Vector2f(30, 30));
	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем ег
		}

		window.clear(Color(0,255,0));
		target.move();
		sleep((milliseconds(30)));
		window.draw(target);
		window.display();
	}

	return 0;
}