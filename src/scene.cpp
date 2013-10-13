#include "scene.h"

#include <cmath>

Scene scene;

Scene::Scene()
: update_text(true)
, map(MAP_W, MAP_H)
, player(player_size/2)
{
	bg_text_font.loadFromFile("sazanami-gothic.ttf");

	bg_text.setFont(bg_text_font);
	bg_text.setCharacterSize(FONT_SIZE_PX);
	bg_text.setColor(sf::Color::Red);

	player.setFillColor(sf::Color::Green);
	player.setPosition( sf::Vector2f(map.generate()) );
}

void Scene::generate_bg_text(sf::Vector2f size)
{
	bg_text_str.clear();
	for(int i = size.y/19 +1; i--;) //TODO MAGIC_NUMBERS values hardcoded for 16px Sazanami Gothic font
	{
		for(int i = size.x/24 +1; i--;) //TODO MAGIC_NUMBERS values hardcoded for 16px Sazanami Gothic font
		{
			unsigned r = rand();
			bg_text_str += "0123456789ABCDEF"[r & 0xf];
			r >>= 4;
			bg_text_str += "0123456789ABCDEF"[r & 0xf];
			bg_text_str += ' ';
		}
		bg_text_str += '\n';
	}

	bg_text.setString(bg_text_str.c_str());

	update_text = false;
}

void Scene::pre_draw(sf::RenderTarget& target)
{
	if(update_text)
		generate_bg_text(target.getView().getSize());
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::View view = target.getView();
	sf::Vector2f size = view.getSize();
	view.reset({0, 0, size.x, size.y});

	target.setView(view);
	target.draw(bg_text, states);

	//-------------------------------------------------------------------------------
	view.setCenter(
		//sf::Vector2f(sf::Vector2i(
			player.getPosition() * float(Map::TILE_SIZE)
			/*)) + sf::Vector2f{0.0f, 0.5f}*/);
	target.setView(view);

	// sf::Rect<float> viewport = view.getViewport();
	// bg_text.setPosition(viewport.left, viewport.top);

	target.draw(map, states);

	states.transform.scale({Map::TILE_SIZE, Map::TILE_SIZE});
	target.draw(player, states);
}

void Scene::handle_event(sf::Event& ev)
{
	switch(ev.type)
	{
		case sf::Event::Resized:
			generate_bg_text({float(ev.size.width), float(ev.size.height)});

		default:
			break;
	}
}

void Scene::move_player(sf::Vector2f ds)
{
	player.move(ds);
	sf::Vector2f pos = player.getPosition();
	size_t x = size_t(pos.x), y = size_t(pos.y), x_1 = x+player_size, y_1 = y+player_size;

	if(map[x][y] == Tile::WALL || map[x][y_1] == Tile::WALL)
		pos.x = x_1;

	if(map[x][y] == Tile::WALL || map[x_1][y] == Tile::WALL)
		pos.y = y_1;

	if(map[x_1][y] == Tile::WALL || map[x_1][y_1] == Tile::WALL)
		pos.x = x;

	if(map[x][y_1] == Tile::WALL || map[x_1][y_1] == Tile::WALL)
		pos.y = y;

	player.setPosition(pos);
}

void Scene::update()
{
	struct Movement
	{
		sf::Keyboard::Key key;
		sf::Vector2f vec;
	};

	static constexpr float s = player_speed_tiles_per_ms*fixed_dt_ms; // [Player] displacement

	static const Movement movements[] =
	{
		{sf::Keyboard::  Left, {-s,  0} },
		{sf::Keyboard::    Up, { 0, -s} },
		{sf::Keyboard:: Right, { s,  0} },
		{sf::Keyboard::  Down, { 0,  s} },

		{sf::Keyboard::     A, {-s,  0} },
		{sf::Keyboard::     W, { 0, -s} },
		{sf::Keyboard::     D, { s,  0} },
		{sf::Keyboard::     S, { 0,  s} },
	};

	for(const auto& movement: movements)
	{
		if(sf::Keyboard::isKeyPressed(movement.key))
		{
			move_player(movement.vec);
			update_text = true;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
