#include "gameover.h"

#include <cmath>

GameOverScene game_over_scene;

GameOverScene::GameOverScene()
{
	// Load assets
	font.loadFromFile("assets/sazanami-gothic.ttf");

	// Visual properties
	text.setFont(font);
	text.setCharacterSize(FONT_SIZE_PX);
}

void GameOverScene::pre_draw(sf::RenderTarget& /*target*/)
{
}

void GameOverScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Background text
	sf::View view = target.getView();
	sf::Vector2f size = view.getSize();
	view.reset({0, 0, size.x, size.y});

	target.setView(view);
	target.draw(text, states);
}

void GameOverScene::handle_event(sf::Event& /*ev*/)
{
}

void GameOverScene::update()
{
}
