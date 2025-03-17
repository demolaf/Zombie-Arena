#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MediaQuery.h"

int main()
{
	// The game will always be in one of four states
	enum class State {
		PAUSED,
		LEVELING_UP,
		GAME_OVER,
		PLAYING
	};

	// Start with the GAME_OVER state
	State state = State::GAME_OVER;

	// Get the screen resolution and create an SFML window
	sf::VideoMode vm = MediaQuery::getCurrentVM();

	sf::RenderWindow window(vm, "Zombie Arena", sf::Style::Fullscreen);

	// Create an SFML View for the main action
	sf::View mainView(sf::FloatRect(0, 0, MediaQuery::screenWidth(),
		MediaQuery::screenHeight()));

	// Here is our clock for timing everything
	sf::Clock clock;

	// How long has the PLAYING state been active
	sf::Time gameTimeTotal;

	// Where is the mouse in relation to the world coordinates
	// NOTE: Vector2f means a container of two float variables
	sf::Vector2f mouseWorldPosition; // Firstly, as the player moves around the 
	// world, we will need to keep track of where the crosshair is in that world.

	// Where is the mouse in relation to screen coordinates
	// NOTE: Vector2i means a container of two int variables
	sf::Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	sf::IntRect arena;

	// The main game loop
	while (window.isOpen())
	{
		// Handle input

		// Handle events by polling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == sf::Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				// Restart while paused
				else if (event.key.code == sf::Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				// Start a new game while in GAME_OVER state
				else if (event.key.code == sf::Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{

				}
			}
		} // End event polling
	} // End game loop

	return 0;
}