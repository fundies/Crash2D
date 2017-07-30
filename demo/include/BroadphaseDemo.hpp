#ifndef BROADPHASEDEMO_HPP
#define BROADPHASEDEMO_HPP

#include "Demo.hpp"
#include "drawables.hpp"
#include "mathutility.hpp"

#include <Crash2D/collision.hpp>
#include <Crash2D/SparseSpatialBroadphase.hpp>

#include <vector>

class BroadphaseDemo : public Demo {
	SparseSpatialBroadphase broadphase;
	sf::RectangleShape mouseObject;

	std::vector<sf::RectangleShape*> objects;

public:
	BroadphaseDemo(sf::RenderWindow &window) : Demo(window), broadphase(100, 100), mouseObject(sf::Vector2f(50, 50)) {
		// set up our mouse object
		mouseObject.setOrigin(mouseObject.getSize() / 2.0f);
		mouseObject.setOutlineThickness(2);
		mouseObject.setFillColor(sf::Color(0, 200, 0));

		// set up some random rectangles
		for (size_t i = 0; i < 2500; ++i) {
			sf::RectangleShape *object = new sf::RectangleShape(sf::Vector2f(randb(5, 15), randb(5, 15)));
			object->setOrigin(object->getSize() / 2.0f);
			object->setOutlineThickness(2);
			objects.push_back(object);
		}
	}

	void draw() {
		// update the mouse position and add it to the broadphase
		auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		const auto mouseSize = mouseObject.getSize();
		mouseObject.setPosition(mousePosition);
		mousePosition -= mouseObject.getOrigin();
		broadphase.addRectangle(
			mousePosition.x,
			mousePosition.y,
			mouseSize.x,
			mouseSize.y,
			&mouseObject);

		// move the rectangles around and add them to the broadphase
		for (const auto& object : objects) {
			object->setPosition(randb(0, window.getSize().x), randb(0,  window.getSize().y));
			const auto objectPosition = object->getPosition() - object->getOrigin();
			const auto objectSize = object->getSize();
			broadphase.addRectangle(
				objectPosition.x,
				objectPosition.y,
				objectSize.x,
				objectSize.y,
				object);

			object->setFillColor(sf::Color(0x00, 0x8B, 0x8B));
			object->setOutlineColor(sf::Color::White);
		}

		// now query the collision pairs and change the color of objects that hit the mouse object to red
		const auto &collisionPairs = broadphase.getCollisionPairs();
		for (const auto &pair : collisionPairs) {
			sf::RectangleShape *other = nullptr;
			if (pair.first == &mouseObject)
				other = (sf::RectangleShape*)pair.second;
			else if (pair.second == &mouseObject)
				other = (sf::RectangleShape*)pair.first;
			else {
				((sf::RectangleShape*)pair.first)->setOutlineColor(sf::Color::Cyan);
				((sf::RectangleShape*)pair.second)->setOutlineColor(sf::Color::Cyan);
			}
			if (other != nullptr)
				other->setFillColor(sf::Color(200, 0, 0));
		}

		// clear out the broadphase for the next run
		broadphase.clear();

		// clear the window with black color
		window.clear(sf::Color::Black);

		for (const auto& object : objects)
			window.draw(*object);

		window.draw(mouseObject);

		// draw a grid to outline the buckets
		const float lineThickness = 5;
		const sf::Color lineColor(150, 150, 150);
		sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, window.getSize().y));
		verticalLine.setFillColor(lineColor);
		for (size_t i = 1; i < (window.getSize().x / broadphase.getCellWidth()); ++i) {
			verticalLine.setPosition(i * broadphase.getCellWidth(), 0);
			window.draw(verticalLine);
		}
		sf::RectangleShape horizontalLine(sf::Vector2f(window.getSize().x, lineThickness));
		horizontalLine.setFillColor(lineColor);
		for (size_t i = 1; i < (window.getSize().y / broadphase.getCellHeight()); ++i) {
			horizontalLine.setPosition(0, i * broadphase.getCellHeight());
			window.draw(horizontalLine);
		}
	}
};

#endif // BROADPHASEDEMO_HPP
