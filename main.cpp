// Texture Packing
// a custom dynamic texture packing algorithm in order to use it for sprite batches
#include "texturePacker.hpp"
#include <SFML/Graphics/Image.hpp>

int main()
    {
        texturePacker pack;

        sf::Texture a;
        a.loadFromFile("test1.bmp");

        sf::Texture b;
        b.loadFromFile("test2.bmp");

        sf::Texture c;
        c.loadFromFile("test3.bmp");

        pack.addTexture(&a);
        pack.addTexture(&b);
        pack.addTexture(&c);

        pack.getTexture().copyToImage().saveToFile("image.png");
        return 0;
    }