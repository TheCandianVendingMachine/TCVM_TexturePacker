#include "texturePacker.hpp"
#include <SFML/Graphics/Image.hpp>
#include <algorithm>

void texturePacker::createImage(packNode *node, sf::Image &packed)
    {
        if (node->m_child[0])
            {
                createImage(node->m_child[0], packed);
                createImage(node->m_child[1], packed);
            }
        else if (node->m_texture)
            {
                sf::Vector2u pos = node->m_position;
                sf::Vector2u size = node->m_texture->getSize();

                sf::Image textureImage = node->m_texture->copyToImage();

                for (unsigned int i = 0; i < size.x; i++)
                    {
                        for (unsigned int j = 0; j < size.y; j++)
                            {
                                packed.setPixel(i + pos.x, j + pos.y, textureImage.getPixel(i, j));
                            }
                    }
            }
    }

texturePacker::texturePacker() : m_needsUpdate(false)
    {
        sf::Vector2u size(2048, 2048);

        m_baseNode.m_size = size;
        m_packedTexture.create(size.x, size.y);
    }

sf::Vector2u texturePacker::addTexture(sf::Texture *texture)
    {
        packNode *ret = m_baseNode.insert(texture);
        if (ret) 
            {
                ret->m_texture = texture;
                m_needsUpdate = true;
                return ret->m_position;
            }
        else
            {
                return sf::Vector2u(0, 0);
            }
    }

const sf::Texture &texturePacker::getTexture()
    {
        if (m_needsUpdate)
            {
                sf::Image packed = m_packedTexture.copyToImage();
                createImage(&m_baseNode, packed);
                m_packedTexture.loadFromImage(packed);
            }
        

        return m_packedTexture;
    }

texturePacker::~texturePacker()
    {
        m_baseNode.clear();
    }

texturePacker::packNode::packNode()
    {
        m_child[0] = nullptr;
        m_child[1] = nullptr;
        m_texture = nullptr;
    }

texturePacker::packNode *texturePacker::packNode::insert(const sf::Texture *texture)
    {
        if (m_child[0]) // if we are a branch we will have atleast 1 child
            {
                packNode *newNode = m_child[0]->insert(texture);
                if (newNode) return newNode;

                return m_child[1]->insert(texture);
            }
        else
            {
                // if we already have a texture, return
                if (m_texture) return nullptr;
                
                // if we are too small we cant use this
                if (texture->getSize().x > m_size.x || texture->getSize().y > m_size.y)
                    {
                        return nullptr;
                    }
                // if we are the perfect size, we dont need children
                else if (texture->getSize().x == m_size.x || texture->getSize().y == m_size.y)
                    {
                        return this;
                    }

                m_child[0] = new packNode;
                m_child[1] = new packNode;

                float dWidth = m_size.x - texture->getSize().x;
                float dHeight = m_size.y - texture->getSize().y;

                if (dWidth > dHeight)
                    {
                        m_child[0]->m_position = m_position;
                        m_child[0]->m_size = sf::Vector2u(texture->getSize().x, m_size.y);

                        m_child[1]->m_position = sf::Vector2u(m_position.x + texture->getSize().x, m_position.y);
                        m_child[1]->m_size = sf::Vector2u(m_size.x - texture->getSize().x, m_size.y);
                    }
                else
                    {
                        m_child[0]->m_position = m_position;
                        m_child[0]->m_size = sf::Vector2u(m_size.x, texture->getSize().y);

                        m_child[1]->m_position = sf::Vector2u(m_position.x, m_position.y + texture->getSize().y);
                        m_child[1]->m_size = sf::Vector2u(m_size.x, m_size.y - texture->getSize().y);
                    }

                return m_child[0]->insert(texture);
            }
    }

void texturePacker::packNode::clear()
    {
        if (m_child[0])
            {
                m_child[0]->clear();
                m_child[1]->clear();

                delete m_child[0];
                delete m_child[1];

                m_child[0] = nullptr;
                m_child[1] = nullptr;
            }
    }
