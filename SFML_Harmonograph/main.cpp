#include "imgui\imgui.h"
#include "imgui\imgui-SFML.h"

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

int p1Denom = 6;
int p2Denom = 2;
int p3Denom = 6;
int p4Denom = 2;

// Time
float tMax = 100.0f;
float tIncr = 0.001f;

const float EulerConstant = 2.718281f;
const float Pi = 3.141526f;

sf::VertexArray points(sf::Points, tMax / tIncr);

void generateHarmonographPoints()
{
	// Phase
	float p1 = Pi / p1Denom;
	float p2 = Pi / p2Denom;
	float p3 = Pi / p3Denom;
	float p4 = Pi / p4Denom;

	// Generate the harmonograph
	int currentArrPos = 0;
	for (float t = 0; t < tMax; t += tIncr)
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
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Harmonograph");
	sf::Event event;
	sf::View view;
	view.setCenter(0, 0);
	view.setSize(1000, 1000);
	window.setView(view);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		//TODO: these need to be much more granular to get interesting patterns
		ImGui::Begin("Parameters");
		ImGui::SliderFloat("A1", &a1, 0.0f, 400.0f);
		ImGui::SliderFloat("A2", &a2, 0.0f, 400.0f);
		ImGui::SliderFloat("A3", &a3, 0.0f, 400.0f);
		ImGui::SliderFloat("A4", &a4, 0.0f, 400.0f);
		ImGui::Text("");
		ImGui::SliderFloat("f1", &f1, 0.0f, 40.0f);
		ImGui::SliderFloat("f2", &f2, 0.0f, 40.0f);
		ImGui::SliderFloat("f3", &f3, 0.0f, 40.0f);
		ImGui::SliderFloat("f4", &f4, 0.0f, 40.0f);
		ImGui::Text("");
		ImGui::SliderFloat("d1", &d1, 0.0f, 0.5f);
		ImGui::SliderFloat("d2", &d2, 0.0f, 0.5f);
		ImGui::SliderFloat("d3", &d3, 0.0f, 0.5f);
		ImGui::SliderFloat("d4", &d4, 0.0f, 0.5f);
		ImGui::Text("");
		ImGui::SliderInt("p1", &p1Denom, 0.0f, 360.0f);
		ImGui::SliderInt("p2", &p2Denom, 0.0f, 360.0f);
		ImGui::SliderInt("p3", &p3Denom, 0.0f, 360.0f);
		ImGui::SliderInt("p4", &p4Denom, 0.0f, 360.0f);
		ImGui::Text("");
		ImGui::SliderFloat("t", &tMax, 1.0f, 100.0f);
		ImGui::SliderFloat("dt", &tIncr, 0.001f, 1.0f);
		ImGui::End();

		generateHarmonographPoints();

		window.clear(sf::Color::Black);
		window.draw(points);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}