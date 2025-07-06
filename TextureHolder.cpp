#include "TextureHolder.h"
// Include the "assert feature"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;

	// auto is the equivalent of map<std::string, sf::Texture>
	// Create an iterator to hold a key-value pair (kvp)
	// and search for the required kvp using the passed in file name
	auto keyValuePair = m.find(filename); // auto is equivalent of std::map<std::string, sf::Texture>::iterator

	// Did we find a match?
	// m.end() — the end() function is a member function of std::map and most STL containers.
	// It returns an iterator pointing just past the last element of the container.
	// This "past-the-end" iterator is used as a sentinel value in iteration, 
	// typically to signal when the iteration should stop.
	//
	// so below we're checking if the key exists in the map
	if (keyValuePair != m.end())
	{
		// Yes. Return the texture, the second part of the kvp, the texture
		return keyValuePair->second;
	}
	else
	{
		// Filename not found
		// Create a new key value pair using the filename
		auto& texture = m[filename];

		// Load the texture from file in the usual way
		texture.loadFromFile(filename);

		// Return the texture to the calling code
		return texture;
	}
}