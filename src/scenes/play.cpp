#include "play.h"

#include <cmath>

Scene scene;

Scene::Scene()
: update_text(true)
, map(MAP_W, MAP_H)
, player(player_size/2)
{
	// Load assets
	bg_text_font.loadFromFile("assets/sazanami-gothic.ttf");
	patch_tex.loadFromFile("assets/patch.png");
	bug_tex.loadFromFile("assets/beetle.png");

	// Visual properties
	bg_text.setFont(bg_text_font);
	bg_text.setCharacterSize(FONT_SIZE_PX);
	bg_text.setColor(sf::Color::Red);

	player.setFillColor(sf::Color::Green);

	//Generation
	std::vector<sf::Vector2u> item_locations = map.generate(10000, NUM_PATCHES +1); // +1 for player

	player.setPosition( sf::Vector2f(item_locations.back()) ); // Place player at the end of generated path...
	item_locations.pop_back();

	patches.reserve(item_locations.size()); // ...and items in regular intervals on path
	for(const sf::Vector2u& loc: item_locations) //TODO ENTITIES_ALLOCATION refactor copypaste
	{
		patches.emplace_back(patch_tex);
		sf::Sprite& patch = patches.back();
		patch.setPosition(sf::Vector2f(loc));
		patch.setScale(1.0f/patch.getLocalBounds().width, 1.0f/patch.getLocalBounds().height);
	}

	bugs.reserve(NUM_BUGS);
	for(size_t i = 0; i < NUM_BUGS; ++i) //TODO ENTITIES_ALLOCATION refactor copypaste
	{
		bugs.emplace_back(bug_tex, sf::IntRect(0, 0, 48, 48)); //TODO HARDCODED hardcoded bug texture tile size
		sf::Sprite& bug = bugs.back();
		bug.setPosition(rand() % MAP_W, rand() % MAP_H);
		bug.setScale(1.0f/bug.getLocalBounds().width, 1.0f/bug.getLocalBounds().height);
	}
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
	// Background text
	sf::View view = target.getView();
	sf::Vector2f size = view.getSize();
	view.reset({0, 0, size.x, size.y});

	target.setView(view);
	target.draw(bg_text, states);

	// Main scene
	view.setCenter(player.getPosition() * float(TILE_SIZE));
	target.setView(view);
	states.transform.scale({TILE_SIZE, TILE_SIZE});

	target.draw(map, states);

	for(const sf::Sprite& patch: patches)
		target.draw(patch, states);

	target.draw(player, states);

	for(const sf::Sprite& bug: bugs)
		target.draw(bug, states);
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
	size_t x_left = pos.x, y_top = pos.y, x_right = pos.x+player_size, y_bottom = pos.y+player_size;

	if(map[x_left][y_top] == Tile::WALL && map[x_left][y_bottom] == Tile::WALL)
		pos.x = x_left+1;

	if(map[x_left][y_top] == Tile::WALL && map[x_right][y_top] == Tile::WALL)
		pos.y = y_top+1;

	if(map[x_right][y_top] == Tile::WALL && map[x_right][y_bottom] == Tile::WALL)
		pos.x = x_right-player_size;

	if(map[x_left][y_bottom] == Tile::WALL && map[x_right][y_bottom] == Tile::WALL)
		pos.y = y_bottom-player_size;

	player.setPosition(pos);

	const sf::FloatRect& player_bb = player.getGlobalBounds();
	for(auto it = patches.begin(); it != patches.end(); )
	{
		if( player_bb.intersects(it->getGlobalBounds()) )
		{
			*it = patches.back();
			patches.pop_back();

			// collect_patch();
			// win
		}
		else
			++it;
	}
}

// void Scene::collect_patch()
// {
// 	if(patches.empty())
// 	{
// 		//TODO win
// 	}
// }

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

	//TODO refactor
	static int steps_to_bug_move = 0;
	const sf::FloatRect& player_bb = player.getGlobalBounds();

	if(steps_to_bug_move++ == 3)
	{
		steps_to_bug_move = 0;

		for(sf::Sprite& bug: bugs)
		{
			int direction = rand() % 4;
			switch(direction)
			{
				case 0: bug.move({ 0,  1}); break;
				case 1: bug.move({ 0, -1}); break;
				case 2: bug.move({ 1,  0}); break;
				case 3: bug.move({-1,  0}); break;
			}

			if( player_bb.intersects(bug.getGlobalBounds()) )
			{
				// lose
			}
		}
	}
}
