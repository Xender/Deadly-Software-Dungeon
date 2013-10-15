#pragma once

#include "../scene.h"
#include <SFML/Graphics.hpp>

class GameOverScene : public Scene
{
	static constexpr unsigned FONT_SIZE_PX = 64;
	sf::Font font;

public:
	sf::Text text;

	GameOverScene();

	void handle_event(sf::Event& ev);
	void update();
	void pre_draw(sf::RenderTarget& target);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

extern GameOverScene game_over_scene;
