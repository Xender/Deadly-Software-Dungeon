#pragma once

#include <SFML/Graphics.hpp>

class Scene : public sf::Drawable
{
public:
	static constexpr unsigned fixed_dt_ms = 20;

	virtual ~Scene() {};

	virtual void handle_event(sf::Event& ev) = 0;
	virtual void update() = 0;
	virtual void pre_draw(sf::RenderTarget& target) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

extern Scene* current_scene;
