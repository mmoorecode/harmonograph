#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

// Amplitude
float a1 = 100.0f;
float a2 = 100.0f;
float a3 = 100.0f;
float a4 = 100.0f;

// Frequency
float f1 = 3.0f;
float f2 = 2.0f;
float f3 = 6.0f;
float f4 = 4.0f;

// Damping (0 - 1)
float d1 = 0.01f;
float d2 = 0.5f;
float d3 = 0.2f;
float d4 = 0.005f;

// Time
const float tMax = 1500.0f;
const float tIncr = 0.01f;

const float EulerConstant = 2.718281f;
const float Pi = 3.141526f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Harmonograph");
	sf::Event event;
	sf::View view;
	view.setCenter(0, 0);
	view.setSize(1000, 1000);
	window.setView(view);

	// Phase
	float p1 = Pi / 6;
	float p2 = Pi / 2;
	float p3 = Pi / 6;
	float p4 = Pi / 2;

	// Generate the harmonograph
	sf::VertexArray points(sf::Points, tMax / tIncr);
	int currentArrPos = 0;
	for (float t = 0; t < tMax; t+=tIncr)
	{
		// Calculate x(t)
		float pen1x = a1 * sin((t * f1) + p1) * pow(EulerConstant, -d1 * t);
		float pen2x = a2 * sin((t * f2) + p2) * pow(EulerConstant, -d2 * t);
		float x = (pen1x + pen2x);

		// Calculate y(t)
		float pen1y = a3 * sin((t * f3) + p3) * pow(EulerConstant, -d3 * t);
		float pen2y = a4 * sin((t * f4) + p4) * pow(EulerConstant, -d4 * t);
		float y = (pen1y + pen2y);

		// Add point to the array
		sf::Vertex vertex;
		points[currentArrPos].position = sf::Vector2f(x, y);
		points[currentArrPos].color = sf::Color::White;

		currentArrPos++;
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::Blue);
		window.draw(points);
		window.display();
	}

	return 0;
}