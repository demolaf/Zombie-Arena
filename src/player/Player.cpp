#include <SFML/Graphics.hpp>
#include "player.h"
#include "../core/constants/UISizing.cpp"
#include <iostream>

Player::Player()
	: m_Speed(START_SPEED),
	m_Health(START_HEALTH),
	m_MaxHealth(START_HEALTH),
	m_Texture(),
	m_Sprite(m_Texture),
	m_DownPressed(false),
	m_UpPressed(false),
	m_LeftPressed(false),
	m_RightPressed(false),
	m_TileSize(0)
{
	// Associate a texture with the sprite
	// !!Watch this space!!
	if (!m_Texture.loadFromFile("./assets/graphics/player.png"))
	{
		printf("Error loading player texture");
	}

	// Set the origin of the sprite to the center, for smooth rotation
	m_Sprite.setTextureRect(sf::IntRect{ {0, 0}, {50, 50} });
	m_Sprite.setOrigin({ 25, 25 });
}

void Player::spawn(sf::IntRect arena, sf::Vector2u resolution, int tileSize) {
	// Place the player in the middle of the arena
	m_Position.x = arena.size.x / 2.0;
	m_Position.y = arena.size.y / 2.0;

	// Copy the details of the arena
	// to the player's m_Arena
	m_Arena.size = arena.size;

	// Remember how big the titles are in this arena
	m_TileSize = tileSize;

	// Store the resolution for future use
	m_Resolution = resolution;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime()
{
	return m_LastHit;
}

bool Player::hit(sf::Time timeHit)
{
	// Without this, a zombie would only need to in contact with the player for one second,
	// and tens of thousands of health points would be deducted.
	// 
	// What this does is that health points will only be deducted from the player up to 
	// five times per second.
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}

	return false;
}

sf::FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter() const
{
	return m_Position;
}

sf::Angle Player::getRotation()
{
	return m_Sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth() const
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
	// Move the player using WASD/Arrow Keys
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}
	
	// Update player position
	m_Sprite.setPosition(m_Position);

	// Ensure the player doesn't go out of bounds of the arena and the tile size
	// ensures that the player stops on a tile before the wall instead of the actual
	
	if (m_Position.x > m_Arena.size.x - m_TileSize)
	{
		// Maintain position
		m_Position.x = m_Arena.size.x - m_TileSize;
	}

	if (m_Position.x < m_Arena.position.x + m_TileSize)
	{
		m_Position.x = m_Arena.position.x + m_TileSize;
	}

	if (m_Position.y > m_Arena.size.y - m_TileSize)
	{
		m_Position.y = m_Arena.size.y - m_TileSize;
	}

	if (m_Position.y < m_Arena.position.y + m_TileSize)
	{
		m_Position.y = m_Arena.position.y + m_TileSize;
	}

	// Calculate the angle the player is facing
	float yDifference = mousePosition.y - m_Resolution.y / 2.0; // calculates the angle between the center
	// of the screen i.e. m_Resolution.x / 2 and the current mouse position.
	float xDifference = mousePosition.x - m_Resolution.x / 2.0;

	//The atan2 function is used to calculate the angle formed by an imaginary line formed between the center 
	// of the screen(m_Resolution.x / 2, m_Resolution.y / 2) and the current mouse 
	// position(mousePosition.x, mousePosition.y).
	float angleInRadians = atan2(yDifference, xDifference);
	float angleConvertedToDegrees = angleInRadians * (180.0f / 3.141);
	m_Sprite.setRotation(sf::degrees(angleConvertedToDegrees));
}

void Player::updateSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;
	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}
