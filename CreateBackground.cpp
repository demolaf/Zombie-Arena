#include "ZombieArena.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena)
{
	// Anything we do to rVA we are really doing to background 
	// (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50; // The TILE_SIZE constant refers to the size in pixels of each tile within the sprite sheet.
	const int TILE_TYPES = 3; // The TILE_TYPES constant refers to the number of different tiles within the sprite sheet

	// Important note: This change from Quads to Triangles will require additional 
	// modifications to your vertex array setup, since you'll need 6 vertices (making two triangles) 
	// to draw what was previously a quad. 
	// 
	// The current code assumes 4 vertices per tile (VERTS_IN_QUAD = 4), but with triangles, 
	// you'll need 6 vertices per tile.

	// In SFML 3, we need 6 vertices to make a quad (2 triangles) instead of 4
	// Triangle 1: vertices 0,1,2 => (0) -> right -> (1) -> down -> (2) 
	// Triangle 2: vertices 2,3,0 => (2) -> left -> (3) -> top -> (0)

	const int VERTS_IN_QUAD = 6; // 6 vertices in a quad because we have to adjacent triangles each having three points/vertices

	// they refer to the width and height of the world in the number of tiles, not pixels.
	int worldWidth = arena.size.x / TILE_SIZE; // worldWidth = 500 / 50 = 10
	int worldHeight = arena.size.y / TILE_SIZE; // worldHeight = 500 / 50 = 10

	// Using Triangles instead of Quads (SFML 3 change)
	rVA.setPrimitiveType(sf::PrimitiveType::Triangles);

	// Set the size of the vertex array
	// 
	// worldWidth * worldHeight * VERTS_IN_QUAD, which equates to the exact number of vertices that our vertex 
	// array will have when we are done preparing it
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD); // 10 * 10 * 6

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad (made of 2 triangles)
			// First triangle
			rVA[currentVertex + 0].position = 
				sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);                           // Top-left, (0 * 50, 0 * 50) = (0, 0)
			rVA[currentVertex + 1].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);            // Top-right, ((0 * 50) + 50, 0 * 50) = (50, 0)
			rVA[currentVertex + 2].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE); // Bottom-right, ((0 * 50) + 50, (0 * 50) + 50) = (50, 50)

			// Second triangle
			rVA[currentVertex + 3].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE); // Bottom-right, ((0 * 50) + 50, (0 * 50) + 50) = (50, 50)
			rVA[currentVertex + 4].position = 
				sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);            // Bottom-left, (0 * 50, (0 * 50) + 50) = (0, 50)
			rVA[currentVertex + 5].position = 
				sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);                           // Top-left, (0 * 50, 0 * 50) = (0, 0)

			// Define the position in the Texture for current quad
			// Either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				// First triangle
				rVA[currentVertex + 0].texCoords = 
					sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);                     // Top-left
				rVA[currentVertex + 1].texCoords = 
					sf::Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);            // Top-right
				rVA[currentVertex + 2].texCoords = 
					sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);    // Bottom-right

				// Second triangle
				rVA[currentVertex + 3].texCoords = 
					sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);    // Bottom-right
				rVA[currentVertex + 4].texCoords = 
					sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);            // Bottom-left
				rVA[currentVertex + 5].texCoords = 
					sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);                    // Top-left
			}
			else
			{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				// mOrG - mud or grass
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				// First triangle
				rVA[currentVertex + 0].texCoords = 
					sf::Vector2f(0, 0 + verticalOffset);                            // Top-left
				rVA[currentVertex + 1].texCoords = 
					sf::Vector2f(TILE_SIZE, 0 + verticalOffset);                   // Top-right
				rVA[currentVertex + 2].texCoords = 
					sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);           // Bottom-right

				// Second triangle
				rVA[currentVertex + 3].texCoords = 
					sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);           // Bottom-right
				rVA[currentVertex + 4].texCoords = 
					sf::Vector2f(0, TILE_SIZE + verticalOffset);                   // Bottom-left
				rVA[currentVertex + 5].texCoords = 
					sf::Vector2f(0, 0 + verticalOffset);                           // Top-left
			}

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}