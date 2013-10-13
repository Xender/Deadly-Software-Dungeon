#pragma once

#include "arr2d.h"
#include <SFML/Graphics.hpp>

enum class Tile : unsigned char
{
	WALL,
	FLOOR
};

class Map : public Arr2d<Tile>, public sf::Drawable
{
	sf::RectangleShape proto_wall_shape;

public:
	static const unsigned TILE_SIZE = 48;

	Map(std::size_t width, std::size_t height)
	: Arr2d<Tile>(width, height)
	{
		proto_wall_shape.setFillColor(sf::Color::Black);
		proto_wall_shape.setSize({float(TILE_SIZE), float(TILE_SIZE)});
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	// Returns point that for sure is floor
	sf::Vector2u generate(unsigned iterations = 10000);
};
