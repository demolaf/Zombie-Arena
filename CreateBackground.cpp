#include "ZombieArena.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena)
{
	// Anything we do to rVA we are really doing to background 
	// (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;

	// Important note: This change from Quads to Triangles will require additional 
	// modifications to your vertex array setup, since you'll need 6 vertices (making two triangles) 
	// to draw what was previously a quad. 
	// 
	// The current code assumes 4 vertices per tile (VERTS_IN_QUAD = 4), but with triangles, 
	// you'll need 6 vertices per tile.

	// In SFML 3, we need 6 vertices to make a quad (2 triangles) instead of 4
	// Triangle 1: vertices 0,1,2
	// Triangle 2: vertices 2,3,0
	const int VERTS_IN_QUAD = 6;
	int worldWidth = arena.size.x / TILE_SIZE;
	int worldHeight = arena.size.y / TILE_SIZE;

	// Using Triangles instead of Quads (SFML 3 change)
	rVA.setPrimitiveType(sf::PrimitiveType::Triangles);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad (made of 2 triangles)
			// First triangle
			rVA[currentVertex + 0].position = 
				sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);                           // Top-left
			rVA[currentVertex + 1].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);            // Top-right
			rVA[currentVertex + 2].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE); // Bottom-right

			// Second triangle
			rVA[currentVertex + 3].position = 
				sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE); // Bottom-right
			rVA[currentVertex + 4].position = 
				sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);            // Bottom-left
			rVA[currentVertex + 5].position = 
				sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);                           // Top-left

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