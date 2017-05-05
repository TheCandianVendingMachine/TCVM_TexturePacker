// texturePacker.hpp
// a texture packer. Takes input textures, appends them to an output one and returns a data package
#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class texturePacker
    {
        private:
            std::vector<sf::Texture*> m_packedTextures;
            sf::Texture m_outTexture;
            sf::Vector2u m_maxSize;

            unsigned int m_itemCount;
            const unsigned int m_maxItemsY;

            bool m_needsUpdate;

        public:
            texturePacker();

            void addTexture(sf::Texture *texture);
            const sf::Texture &getTexture();

    };