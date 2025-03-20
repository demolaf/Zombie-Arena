#include "MediaQuery.h"

MediaQuery::MediaQuery()
{
	currentVideoMode = sf::VideoMode::getFullscreenModes()[0];
}

MediaQuery MediaQuery::instance = MediaQuery();

sf::VideoMode MediaQuery::getCurrentVM()
{
	sf::VideoMode vm = instance.currentVideoMode;
	// printf("Video mode, Width: %d - Height: %d", vm.width, vm.height);
	return vm;
}

sf::Vector2u MediaQuery::getResolution()
{
	return instance.currentVideoMode.size;
}

int MediaQuery::screenWidth()
{
	return static_cast<int>(instance.currentVideoMode.size.x);
}

int MediaQuery::screenHeight()
{
	return static_cast<int>(instance.currentVideoMode.size.y);
}

int MediaQuery::centerX()
{
	return screenWidth() / 2;
}

int MediaQuery::centerY()
{
	return screenHeight() / 2;
}
