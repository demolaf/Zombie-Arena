#pragma once
#include <SFML/Graphics.hpp>

class MediaQuery
{
public:
	static sf::VideoMode getCurrentVM();
	static int screenWidth();
	static int screenHeight();
	static int centerX();
	static int centerY();

private:
	MediaQuery();
	static MediaQuery instance;
	sf::VideoMode currentVideoMode;
};