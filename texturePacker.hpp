// texturePacker.hpp
// a texture packer. Takes input textures, appends them to an output one and returns a data package
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
                    

                    packNode();
                    packNode *insert(const sf::Texture *texture);
                    void clear();

                } m_baseNode;

            sf::Texture m_packedTexture;
            bool m_needsUpdate;

            void createImage(packNode *node, sf::Image &packed);

        public:
            texturePacker();

            sf::Vector2u addTexture(sf::Texture *texture);
            const sf::Texture &getTexture();

            ~texturePacker();

    };