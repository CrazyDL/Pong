#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

class Player
{
public:
	float x, y, w, h, dy = 0, speed = 0;
	bool dir;
	String File;
	Texture texture;
	Sprite sprite;

	Player(String F, float X, float Y, float W, float H)
	{
		File = F;
		w = W; h = H; x = X; y = Y;
		texture.loadFromFile(File);
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x, y, w, h));
	}

	void update(float time, int x)
	{
		if (dir) {y += speed*time;}
			else {y += -speed*time;}
		speed = 0;
		sprite.setPosition(x, y);
	}

};

class Ball
{
public:
	float x, y, w, h, dy, dx, speed = 0.2;
	int x1 = 400, y1 = 300;
	int dir = 0;
	bool f = false;
	String File;
	Texture texture;
	Sprite sprite;

	Ball(String F, float X, float Y, float W, float H)
	{
		File = F;
		w = W; h = H; x = X; y = Y;
		texture.loadFromFile(File);
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(x, y, w, h));
	}

	void update(float time)
	{
			/*switch (dir)
			{
			case 0: dx = speed; dy = -speed/3; break;
			case 1: dx = -speed; dy = speed/3; break;
			case 2: dx = speed; dy = speed/3; break;
			case 3: dx = -speed; dy = -speed/3; break;
			}
			x1 += dx*time;
			y1 += dy*time;
			sprite.setPosition(x1, y1);*/
		if (f)
		{
			x1 += speed*time;
			y1 += speed*time;
			sprite.setPosition(x1, y1);
		}
		//sprite.setPosition(400, 300);
	}

};

int main()
{
	RenderWindow window(VideoMode(800, 600), "SkaneTest", Style::Close);
	Clock clock;
	
	Player f("fon.png", 0, 0, 800, 600);//Фон

	Player p1("pl.png", 16, 130, 15, 80);//Левый игрок
	p1.sprite.scale(Vector2f(1.4f, 1.4f));

	Player p2("pl.png", 16, 130, 15, 80);//Правый игрок
	p2.sprite.scale(Vector2f(1.4f, 1.4f));

	Ball b("ball.png", 15, 15, 100, 100);//Мяч
	b.sprite.setPosition(400, 300);
	b.sprite.scale(Vector2f(0.25f, 0.25f));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 200;
		//Закрытие окна
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) { window.close(); }
		}
		//Движение левого игрока		
		if ((p1.y + 103) > 600) { if (Keyboard::isKeyPressed(Keyboard::W)) { p1.dir = false; p1.speed = 0.1; } }
		else if (p1.y < 0){if (Keyboard::isKeyPressed(Keyboard::S)) { p1.dir = true; p1.speed = 0.1; }}
		else if ((p1.y < 800) && (p1.y > 0))
		{
			if(Keyboard::isKeyPressed(Keyboard::W)) { p1.dir = false; p1.speed = 0.1; } 
			if (Keyboard::isKeyPressed(Keyboard::S)) { p1.dir = true; p1.speed = 0.1; }
		}
		/*
				if (Keyboard::isKeyPressed(Keyboard::W))
			if (p1.y < 800 && p1.y > 0){ p1.dir = false; p1.speed = 0.1; }
		if (Keyboard::isKeyPressed(Keyboard::S)) 
			if (p1.y < 800 && p1.y > 0){ p1.dir = true; p1.speed = 0.1; }
		*/
		p1.update(time, 20);
		//Движение Правого игрока
		if ((p2.y + 103) > 600) { if (Keyboard::isKeyPressed(Keyboard::Up)) { p2.dir = false; p2.speed = 0.1; } }
		else if (p2.y < 0) { if (Keyboard::isKeyPressed(Keyboard::Down)) { p2.dir = true; p2.speed = 0.1; } }
		else if ((p2.y < 800) && (p2.y > 0))
		{
			if (Keyboard::isKeyPressed(Keyboard::Up)) { p2.dir = false; p2.speed = 0.1; }
			if (Keyboard::isKeyPressed(Keyboard::Down)) { p2.dir = true; p2.speed = 0.1; }
		}
		p2.update(time, 760);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			b.f = true;
		}
		b.update(time);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			b.f = false;
		}
		//if ((b.y > 800) && (b.y < 0))b.f = false;

		//Вывод на экран
		window.clear();
		window.draw(f.sprite);
		window.draw(p1.sprite);
		window.draw(p2.sprite);
		window.draw(b.sprite);
		window.display();
	}
	//Windows (/SUBSYSTEM:WINDOWS)
	return 0;
}