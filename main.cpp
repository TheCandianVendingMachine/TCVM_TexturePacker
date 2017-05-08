// Texture Packing
// a custom dynamic texture packing algorithm in order to use it for sprite batches
#include "texturePacker.hpp"
#include <SFML/Graphics/Image.hpp>
#include <chrono>
#include <iostream>

int main()
    {
        texturePacker pack;

        sf::Texture a;
        sf::Texture b;
        sf::Texture c;

        a.loadFromFile("test1.bmp");       
        b.loadFromFile("test2.bmp");
        c.loadFromFile("test3.bmp");

        pack.addTexture(&c);

        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);


        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&b);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);
        pack.addTexture(&a);

        pack.getTexture().copyToImage().saveToFile("image.bmp");
        return 0;
    }