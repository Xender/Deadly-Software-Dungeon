#pragma once

#include "../map.h"
#include <SFML/Graphics.hpp>

class Scene : public sf::Drawable
{
	static constexpr unsigned FONT_SIZE_PX = 16;
	sf::Font bg_text_font;
	sf::Text bg_text;
	std::string bg_text_str;
	bool update_text;

	static constexpr unsigned TILE_SIZE = 48;
	static constexpr std::size_t MAP_W = 200, MAP_H = 200;
	Map map;

	static constexpr size_t NUM_PATCHES = 5;
	sf::Texture patch_tex;
	std::vector<sf::Sprite> patches;

	static constexpr size_t NUM_BUGS = 200;
	sf::Texture bug_tex;
	std::vector<sf::Sprite> bugs;

	static constexpr float player_size = 0.6f;
	sf::CircleShape player;
	static constexpr float player_speed_tiles_per_ms = 0.01f; // TODO Value of 0.03 causes glitches in collision detection

	void generate_bg_text(sf::Vector2f size);
	void move_player(sf::Vector2f ds);
	// void collect_patch();

public:
	static constexpr unsigned fixed_dt_ms = 20;

	Scene();

	void handle_event(sf::Event& ev);
	void update();
	void pre_draw(sf::RenderTarget& target);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

extern Scene scene;
