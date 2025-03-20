#pragma once
#include <SFML/Graphics.hpp>

class MediaQuery
{
public:
	static sf::VideoMode getCurrentVM();
	static sf::Vector2u getResolution();
	static int screenWidth();
	static int screenHeight();
	static int centerX();
	static int centerY();

private:
	MediaQuery();
	static MediaQuery instance;
	sf::VideoMode currentVideoMode;
};