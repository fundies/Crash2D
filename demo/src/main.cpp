#include "MTVDemo.hpp"
#include "BroadphaseDemo.hpp"

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Crash2D Demo");
	window.setFramerateLimit(60);

	Demo *demo = new MTVDemo(window);
	size_t demoId = 0;

	while (window.isOpen()) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				// "close requested" event: we close the window
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Space) {
						delete demo;
						++demoId;
						if (demoId > 1) demoId = 0;
						switch (demoId) {
							case 0:
								demo = new MTVDemo(window);
								break;
							case 1:
								demo = new BroadphaseDemo(window);
								break;
						}
					}
					break;
				default:
					break;
			}
		}

		demo->draw();
		window.display();
	}
}
