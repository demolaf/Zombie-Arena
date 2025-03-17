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

sf::Vector2f MediaQuery::getResolution()
{
	sf::Vector2f resolution(instance.currentVideoMode.width, instance.currentVideoMode.height);
	return resolution;
}

int MediaQuery::screenWidth()
{
	return instance.currentVideoMode.width;
}

int MediaQuery::screenHeight()
{
	return instance.currentVideoMode.height;
}

int MediaQuery::centerX()
{
	return screenWidth() / 2;
}

int MediaQuery::centerY()
{
	return screenHeight() / 2;
}
