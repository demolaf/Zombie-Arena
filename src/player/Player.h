#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	// Where is the player
	sf::Vector2f m_Position;
	
	// The sprite
	sf::Sprite m_Sprite;
	
	// and a texture
	// !!Watch this space - Changes here soon!!
	sf::Texture m_Texture;
	
	// What is the screen resolution
	sf::Vector2u m_Resolution;

	// What size is the current arena
	sf::IntRect m_Arena;
	
	// What size is the current arena
	int m_TileSize;
	
	// Which direction(s) the player is moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	
	// How much health has the player got?
	int m_Health;
	
	// What is the max' health the player can have
	int m_MaxHealth;
	
	// When was the player last hit
	sf::Time m_LastHit;
	
	// Speed in pixels per second
	float m_Speed;

	// All our public functions next
public:
	Player();

	void spawn(sf::IntRect arena, sf::Vector2u resolution, int tileSize);
	
	// Call this at the end of every game
	void resetPlayerStats();

	// Handle the player getting hit by a zombie
	bool hit(sf::Time timeHit);
	
	// How long ago was the player last hit
	sf::Time getLastHitTime();
	
	// Where is the player
	sf::FloatRect getPosition();
	
	// Where is the center of the player
	sf::Vector2f getCenter() const;
	
	// What angle is the player facing
	sf::Angle getRotation();
	
	// Send a copy of the sprite to the main function
	sf::Sprite getSprite();
	
	// The next four functions move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	
	// Stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	
	// We will call this function once every frame
	void update(float elapsedTime, sf::Vector2i mousePosition);
	
	// Give the player a speed boost
	void updateSpeed();
	
	// Give the player some health
	void upgradeHealth();
	
	// Increase the max' health the player can have
	void increaseHealthLevel(int amount);
	
	// How much health has the player currently got?
	int getHealth() const;
};