#pragma once

#include "arr2d.h"
#include <SFML/Graphics.hpp>
#include <vector>

enum class Tile : unsigned char
{
	WALL,
	FLOOR
};

class Map : public Arr2d<Tile>, public sf::Drawable
{
	sf::RectangleShape proto_wall_shape;

public:
	Map(std::size_t width, std::size_t height)
	: Arr2d<Tile>(width, height)
	{
		proto_wall_shape.setFillColor(sf::Color::Black);
		proto_wall_shape.setSize({1, 1});
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Returns vector of <num_stops> coordinates of floor tiles, uniformly encountered.
	std::vector<sf::Vector2u> generate(unsigned iterations, unsigned num_stops);
};
