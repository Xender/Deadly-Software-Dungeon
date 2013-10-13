#include <SFML/Graphics.hpp>
#include "scene.h"

int main(/*int argc, const char *argv[]*/)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Deadly Software Dungeon");
	sf::Clock timer;
	sf::Time accum;

	while(window.isOpen())
	{
		sf::Event ev;
		while(window.pollEvent(ev))
		{
			switch(ev.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					window.setView(sf::View({0, 0, float(ev.size.width), float(ev.size.height)}));

				default:
					scene.handle_event(ev);
			}
		}

		sf::Time scene_fixed_dt = sf::milliseconds(Scene::fixed_dt_ms);
		for(accum += timer.restart(); accum > scene_fixed_dt; accum -= scene_fixed_dt)
		{
			scene.update();
		}

		scene.pre_draw();

		window.clear(sf::Color::Black);
		window.draw(scene);
		window.display();
	}

	return 0;
}
