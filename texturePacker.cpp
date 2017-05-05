#include "texturePacker.hpp"
#include <SFML/Graphics/Image.hpp>
#include <algorithm>

texturePacker::texturePacker() : m_needsUpdate(false), m_maxItemsY(2), m_itemCount(0)
    {
    }

void texturePacker::addTexture(sf::Texture *texture)
    {
        m_packedTextures.push_back(texture);
        m_itemCount++;

        m_maxSize.x += texture->getSize().x;
        m_maxSize.y += texture->getSize().y;

        m_needsUpdate = true;
    }

const sf::Texture &texturePacker::getTexture()
    {
        if (m_needsUpdate)
            {
                std::sort(m_packedTextures.begin(), m_packedTextures.end(),
                         [](sf::Texture *a, sf::Texture *b) {
                         return (a->getSize().x * a->getSize().x + a->getSize().y * a->getSize().y) >
                                (b->getSize().x * b->getSize().x + b->getSize().y * b->getSize().y);
                    });

                sf::Image packed;
                packed.create(m_maxSize.x, m_maxSize.y);

                sf::Vector2u offset(0, 0);
                unsigned int maxTextureSizeX = 0;
                for (auto &texture : m_packedTextures)
                    {
                        maxTextureSizeX = texture->getSize().x > maxTextureSizeX ? texture->getSize().x : maxTextureSizeX;

                        if (offset.y + texture->getSize().y > m_maxSize.y)
                            {
                                offset.x += maxTextureSizeX;
                                offset.y = 0;
                            }

                        auto textureImage = texture->copyToImage();
                        for (unsigned int i = 0; i < textureImage.getSize().x; i++)
                            {
                                for (unsigned int j = 0; j < textureImage.getSize().y; j++)
                                    {
                                        packed.setPixel(i + offset.x, j + offset.y, textureImage.getPixel(i, j));
                                    }
                            }

                        offset.y += texture->getSize().y;
                    }

                m_outTexture.loadFromImage(packed);
                m_needsUpdate = false;
            }

        return m_outTexture;
    }
