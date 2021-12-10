#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <cstdlib>
#include<math.h>
#include"Animation.h"
sf::RenderWindow window(sf::VideoMode(1000, 700), "Demo", sf::Style::Close | sf::Style::Resize);
using namespace std;
int main()
{
	int dem = 0;
	double v1=0, v2=-1, v1l, v2l;
	double m1 = 1 , m2 = 100000000,M,N;

	sf::Clock clock;
	float deltaTime;
	Animation ani("MegamanRun", 10, 0.1f);

	sf::RectangleShape shape1(sf::Vector2f(150.f, 150.f));
	shape1.setOrigin(sf::Vector2f(75.f, 75.f));
	shape1.setPosition(sf::Vector2f(200.f,623.f));
	shape1.setFillColor(sf::Color::Blue);
	shape1.setOutlineColor(sf::Color::White);
	shape1.setOutlineThickness(2.f);

	sf::RectangleShape shape2(sf::Vector2f(200.f, 200.f));
	shape2.setOrigin(sf::Vector2f(100.f, 100.f));
	shape2.setPosition(sf::Vector2f(700.f,598.f));
	shape2.setFillColor(sf::Color::Red);
	shape2.setOutlineColor(sf::Color::White);
	shape2.setOutlineThickness(2.f);
	
	sf::Font font;
	font.loadFromFile("Pangolin.ttf");
	sf::Text text,vat1,vat2;
	vat1.setPosition(sf::Vector2f(shape1.getPosition().x, shape1.getPosition().y-115));
	vat2.setPosition(sf::Vector2f(shape2.getPosition().x, shape2.getPosition().y-150));
	vat1.setFont(font);
	vat2.setFont(font);
	vat1.setString(to_string((int)m1));
	vat2.setString(to_string((int)m2));
	text.setFont(font);
	text.setCharacterSize(36);
	text.setPosition(sf::Vector2f(150, 400));

	sf::SoundBuffer buffer;
	buffer.loadFromFile("sound.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	while (window.isOpen())
	{
		deltaTime = 1;
		//deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		shape2.move(sf::Vector2f(v2 * deltaTime, 0));
		vat2.move(sf::Vector2f(v2 * deltaTime, 0));
		shape1.move(sf::Vector2f(v1 * deltaTime, 0));
		vat1.move(sf::Vector2f(v1 * deltaTime, 0));
		if (shape1.getPosition().x + 75 >= shape2.getPosition().x - 100)
		{
			sound.play();
			dem++;
			M = m1 * v1 + m2 * v2;
			N = m1 * v1 * v1 + m2 * v2 * v2;
			v1l = (M - sqrt(N * m1 * m2 * m2 + N * m1 * m2 - M * M * m2)) / (m1 * (m2 + 1));
			v2l = (M * m2 + sqrt(N * m1 * m2 * m2 + N * m1 * m2 - M * M * m2)) / (m2 + m2 * m2);
			v1 = v1l;
			v2 = v2l;
		}
		if (shape1.getPosition().x - 75 <= 0)
		{
			sound.play();
			dem++;
			v1 = -v1;
		}
		text.setString("Number of collisions: " + to_string(dem));
		window.clear();
		window.draw(text);
		window.draw(vat1);
		window.draw(vat2);
		window.draw(shape1);
		window.draw(shape2);
		window.display();
	}

	return 0;
}