#pragma once
#include <math.hpp>
#include <collisiongrid.hpp>
#include <configuration.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <omp.h>
#include <vector>

struct VerletBall
{
	sf::Vector2<double> position;
	sf::Vector2<double> position_last;
	sf::Vector2<double> position_next;
	sf::Vector2<double> displacement;
	sf::Vector2<double> acceleration;
	float radius;
	sf::Color color;

	VerletBall()
		: position((conf::constraints.x) / 2, 0.0f),
		position_last((conf::constraints.x) / 2, 0.0f),
		displacement(position - position_last),
		acceleration(0, 0),
		radius(1.0f),
		color(sf::Color::White)
	{}

	void update(double dt, double gravity)
	{
		displacement = position - position_last;
		position_next = position + displacement + acceleration * dt * dt;

		position_last = position;
		position = position_next;
		acceleration = sf::Vector2<double>(0.0f, gravity);
	}

};
