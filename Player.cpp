#include "player.h"
#include "UISizing.cpp"

Player::Player()
	: m_Speed(START_SPEED),
	m_Health(START_HEALTH),
	m_MaxHealth(START_HEALTH),
	m_Texture(),
	m_Sprite()
{
	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the center,
	// for smooth rotation
	float playerCenter = UISizing::playerLocalBoundsCenter();
	m_Sprite.setOrigin(playerCenter, playerCenter);
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize) {
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// Copy the details of the arena
	// to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the titles are in this arena
	m_TileSize = tileSize;

	// Store the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
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

sf::Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
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
	
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		// Maintain position
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the angle the player is facing
	float yDifference = mousePosition.y - m_Resolution.y / 2; // calculates the angle between the center
	// of the screen i.e. m_Resolution.x / 2 and the current mouse position.
	float xDifference = mousePosition.x - m_Resolution.x / 2;
	float angle = (atan2(yDifference, xDifference) * 180) / 3.141; // The atan2 function is used to calculate the angle formed by an 
	// imaginary line formed between the center of the screen(m_Resolution.x / 2, m_Resolution.y / 2) and 
	// the current mouse position(mousePosition.x, mousePosition.y).
	m_Sprite.setRotation(angle);
}