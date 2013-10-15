#include "map.h"

#include <cstdlib>

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape wall_shape(proto_wall_shape);
	for(std::size_t x = 0; x < width; ++x)
		for(std::size_t y = 0; y < height; ++y)
			if((*this)[x][y] == Tile::FLOOR)
			{
				wall_shape.setPosition(x, y);
				target.draw(wall_shape, states);
			}
}

std::vector<sf::Vector2u> Map::generate(unsigned iterations, unsigned num_stops)
{
	std::vector<sf::Vector2u> stops;
	stops.reserve(num_stops);

	// Implements random movement (drunkard walk) algorithm

	int direction = 4; // Ignored default value for not creating a bias in any particular direction (see biasing below).
	sf::Vector2u pos {unsigned(width/2u), unsigned(height/2u)};

	unsigned j = 0;
	for(unsigned i = 1; i <= num_stops; ++i)
	{
		unsigned next_stop = iterations * i / num_stops;
		while(j++ < next_stop)
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
		stops.push_back(pos);
	}

	return stops;
}
