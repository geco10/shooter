#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
class Target :public Drawable {
private:
	Vector2f speed = { 6,10 };
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
	bool isShot(int x,int y) {
		Vector2f center(loc.x + radius, loc.y + radius);
		float d =sqrt((x-center.x)*(x-center.x)+(y-center.y)*(y-center.y));
		if (radius >= d) return true;
		return false;
	}
	void draw(RenderTarget& target, RenderStates states)const override {
		CircleShape circle(radius);
		circle.setFillColor(Color(255, 255, 255));
		circle.setOutlineThickness(radius / 2);
		circle.setOutlineColor(Color(255, 0, 0));
		circle.setPosition(Vector2f(loc));
		target.draw(circle);
	}
	int locY() {
		return loc.y;
	}
};
class TargetCenter :public Drawable {
	std::vector<Target> arr;
	Vector2f screen;
	int max = 7;
public:
	TargetCenter(Vector2f screen) {
		this->screen = screen;
	}
	void trySpamn() {
		if (arr.size() < max) {
			int radius = rand() % 50 + 20;
			Vector2f loc;
			loc.x = rand() % (int)screen.x;
			loc.y = radius * (-2);
			make(radius, loc);
		}
	}
	void move() {
		for (int i = 0; i < arr.size(); ++i) {
			arr[i].move();
		}
	}
	void make(int radius, Vector2f loc) {
		arr.push_back(Target(radius, loc));
	}
	int shotCheck(int x,int y) {
		int Tscore=0;
		for (int i = arr.size()-1; i >=0; --i) {
			if (arr[i].isShot(x,y) == true) {
				Tscore += arr[i].calc();
				arr.erase(arr.begin() + i);
			}
		}
		return Tscore;
	}
	void draw(RenderTarget& target, RenderStates states)const override {
		for (int i = 0; i < arr.size(); ++i) {
			target.draw(arr[i]);
		}
	}
	void clean() {
		for (int i = 0; i < arr.size(); i++) {
			if (screen.y < arr[i].locY()) arr.erase(arr.begin() + i);
		}
	}
	void tick() {
		move();
		trySpamn();
		clean();
	}
};
int main()
{
	srand(time(NULL));
	Vector2f size(925, 700);
	TargetCenter tc(size);
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(size.x, size.y), "SFML Works!");
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
			if (event.type == Event::MouseButtonPressed) {
				int s = tc.shotCheck(event.mouseButton.x,event.mouseButton.y);
				printf("%i",s);

			}
		}

		window.clear(Color(0, 255, 0));
		tc.tick();
		sleep((milliseconds(30)));
		window.draw(tc);
		window.display();
	}

	return 0;
}