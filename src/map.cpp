#include "map.h"

#include <cstdlib>

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape wall_shape(proto_wall_shape);
	for(std::size_t x = 0; x < width; ++x)
		for(std::size_t y = 0; y < height; ++y)
			if((*this)[x][y] == Tile::FLOOR)
			{
				wall_shape.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				target.draw(wall_shape, states);
			}
}

sf::Vector2u Map::generate(unsigned iterations)
{
	// Implements random movement (drunkard walk) algorithm

	int direction = 4;
	sf::Vector2u pos {unsigned(width/2u), unsigned(height/2u)};

	for(unsigned i = 0; i < iterations; ++i)
	{
		// Bias toward previous walk direction - for more sparse structure
		int choice = rand() % 6;
		if(choice < 4)
			direction = choice;

		switch(direction)
		{
			case 0: if(pos.x < width -1) ++pos.x; else pos = {unsigned(width/2u), unsigned(height/2u)}; break;
			case 1: if(pos.y < height-1) ++pos.y; else pos = {unsigned(width/2u), unsigned(height/2u)}; break;
			case 2: if(pos.x > 0)        --pos.x; else pos = {unsigned(width/2u), unsigned(height/2u)}; break;
			case 3: if(pos.y > 0)        --pos.y; else pos = {unsigned(width/2u), unsigned(height/2u)}; break;
		}
		(*this)[pos.x][pos.y] = Tile::FLOOR;
	}

	return pos;
	// for(std::size_t x = 0; x < width; ++x)
	// 	for(std::size_t y = 0; y < height; ++y)
	// 		(*this)[x][y] = (rand() & 1) ? Tile::WALL : Tile::FLOOR;
}
