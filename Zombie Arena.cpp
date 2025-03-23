#include <SFML/Graphics.hpp>
#include "src/player/Player.h"
#include "src/core/utils/media_query/MediaQuery.h"
#include <iostream>

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

	sf::RenderWindow window(vm, "Zombie Arena", sf::Style::Default);

	// Create an SFML View for the main action
	sf::View mainView(sf::FloatRect({ 0, 0 }, { MediaQuery::screenWidth(), MediaQuery::screenHeight() }));

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

	// Handle events
	// [&window, &state, &clock, &player, &arena] is the capture list
	const auto onKeyPressed = [&window, &state, &clock, &player, &arena](const sf::Event::KeyPressed& keyPressed) 
		{
			// Handle the player quitting
			if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
			{
				window.close();
			}

			// Pause a game while playing
			if (keyPressed.scancode == sf::Keyboard::Scancode::Enter && state == State::PLAYING)
			{
				state = State::PAUSED;
			}
			// Restart while paused
			else if (keyPressed.scancode == sf::Keyboard::Scancode::Enter && state == State::PAUSED)
			{
				state = State::PLAYING;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
			// Start a new game while in GAME_OVER state
			else if (keyPressed.scancode == sf::Keyboard::Scancode::Enter && state == State::GAME_OVER)
			{
				state = State::LEVELING_UP;
			}

			if (state == State::PLAYING)
			{

			}

			// Handle WASD while playing
			if (state == State::PLAYING)
			{
				// Handle the pressing and releasing of WASD keys
				if (keyPressed.scancode == sf::Keyboard::Scancode::W)
				{
					player.moveUp();
				}
				else
				{
					player.stopUp();
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::S)
				{
					player.moveDown();
				}
				else
				{
					player.stopDown();
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::A)
				{
					player.moveLeft();
				}
				else
				{
					player.stopLeft();
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::D)
				{
					player.moveRight();
				}
				else
				{
					player.stopRight();
				}
			} // End WASD while playing

			// Handle the LEVELING up state
			if (state == State::LEVELING_UP)
			{
				// Handle the player LEVELING up
				if (keyPressed.scancode == sf::Keyboard::Scancode::Num1)
				{
					state = State::PLAYING;
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::Num2)
				{
					state = State::PLAYING;
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::Num3)
				{
					state = State::PLAYING;
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::Num4)
				{
					state = State::PLAYING;
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::Num5)
				{
					state = State::PLAYING;
				}

				if (keyPressed.scancode == sf::Keyboard::Scancode::Num6)
				{
					state = State::PLAYING;
				}

				if (state == State::PLAYING)
				{
					// Prepare the level
					// We will modify the next two lines later
					arena.size = sf::Vector2i{500, 500};
					arena.position = sf::Vector2i{0, 0};

					// We will modify this line of code later
					int tileSize = 50;

					// Spawn the player in middle of the arena
					player.spawn(arena, MediaQuery::getResolution(), tileSize);

					// Reset clock so there isn't a frame jump
					clock.restart();
				}
			} // End LEVELING up

		}; // end event polling

	// The main game loop
	while (window.isOpen())
	{
		// Handle input
		window.handleEvents(onKeyPressed);

		/*
		************
		UPDATE THE FRAME
		************
		*/
		if (state == State::PLAYING)
		{
			// Update the delta time
			sf::Time dt = clock.restart();

			// Update the total game time
			gameTimeTotal += dt;

			// Make a fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = sf::Mouse::getPosition();

			// Convert mouse position to world based coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				sf::Mouse::getPosition(), mainView);

			// Update the player
			player.update(dtAsSeconds, sf::Mouse::getPosition());

			// Make a note of the players new position
			sf::Vector2f playerPosition(player.getCenter());

			// Make the view centre around player
			mainView.setCenter(player.getCenter());
		} // End updating the scene

		/*
		***********
		* Draw the scene
		***********
		*/
		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window and
			// draw everything related to it
			window.setView(mainView);

			// Draw the player
			window.draw(player.getSprite());
		}

		if (state == State::LEVELING_UP)
		{

		}

		if (state == State::PAUSED)
		{

		}

		if (state == State::GAME_OVER)
		{

		}

		window.display();

	} // End game loop

	return 0;
}