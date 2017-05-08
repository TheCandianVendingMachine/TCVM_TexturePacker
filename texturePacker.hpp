// texturePacker.hpp
// a texture packer. Takes input textures, appends them to an output one and returns a data package
// Algorithm inspired from http://blackpawn.com/texts/lightmaps/default.html
#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class texturePacker
    {
        private:
            struct packNode
                {
                    packNode *m_child[2];
                    sf::Texture *m_texture;

                    sf::Vector2u m_position;
                    sf::Vector2u m_size;
                    

                    packNode(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
                    packNode *insert(sf::Texture *texture);
                    void clear();

                } m_baseNode;

            sf::Texture m_packedTexture;
            bool m_needsUpdate;

            void createImage(packNode *node, sf::Image &packed);

        public:
            texturePacker(sf::Vector2u textureSize = sf::Vector2u(2048, 2048));

            sf::Vector2u addTexture(sf::Texture *texture);
            const sf::Texture &getTexture();

            ~texturePacker();

    };