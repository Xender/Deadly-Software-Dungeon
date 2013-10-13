#pragma once

#include "map.h"
#include <SFML/Graphics.hpp>

class Scene : public sf::Drawable
{
	sf::Font bg_text_font;
	sf::Text bg_text;
	std::string bg_text_str;
	bool update_text;

	static constexpr std::size_t MAP_W = 200, MAP_H = 200;
	Map map;

	static constexpr float player_size = 0.6f;
	sf::CircleShape player;
	static constexpr float player_speed_tiles_per_ms = 0.03f;

	void generate_bg_text();
	void move_player(sf::Vector2f ds);

public:
	static constexpr unsigned fixed_dt_ms = 20;

	Scene();

	void handle_event(sf::Event& ev);
	void update();
	void pre_draw();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

extern Scene scene;