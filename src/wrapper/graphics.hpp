#pragma once

#include <string>

#include <SFML/Graphics.hpp>

namespace W {

    class Sprite;

    class Window {

    public:

        Window(unsigned int VX=200, 
                unsigned int VY=150, 
                unsigned int WX=800, 
                unsigned int WY=600 )
        :   renderWindow(sf::VideoMode(VX, VY), "www.seanbutler.net")
        ,   clearColour(0, 0, 0)
        {
            SetSize(WX, WY);
            SetClearColour(255, 255, 255);
            SetFrameRateLimit(30);
            renderWindow.setVisible(1);
            renderWindow.setActive(1);
        }

        ~Window() {}

        void SetTitle(std::string T)                                { renderWindow.setTitle(T); }
        void SetPosition( int X, int Y)                             { renderWindow.setPosition(sf::Vector2i(X, Y)); }
        void SetSize(unsigned int W, unsigned int H)                { renderWindow.setSize(sf::Vector2u(W, H)); }
        void SetClearColour(uint8_t R=0, uint8_t G=0, uint8_t B=0)  { clearColour = sf::Color(R, B, G); }
        void SetFrameRateLimit(unsigned int L=60)                   { renderWindow.setFramerateLimit(L); }

        void Clear()                                                { renderWindow.clear();     }
        void Display()                                              { renderWindow.display();   }
        sf::RenderWindow & get()                                    { return renderWindow;      }
        void DrawSprite(Sprite& S);

    private:
        sf::RenderWindow    renderWindow;
        sf::Color           clearColour;
    };


    class Sprite {
        public:
        
        Sprite(std::string F, int X=0, int Y=0, int W=32, int H=32)
        :   x(X)
        ,   y(Y)
        ,   w(W)
        ,   h(H)
        ,   filename(F)
        ,   texture()
        ,   sprite()
        {
            if (!texture.loadFromFile(filename, sf::IntRect(x, y, w, h)))
            {
                // error...
            }
            sprite.setTexture(texture);
            texture.setRepeated(false);
            texture.setSmooth(false);
        }

        ~Sprite() {}

        void Draw(Window W);
        sf::Sprite & get()                  { return sprite; }


    public:
        int                 x, y, w, h;

    private:
        std::string         filename;
        sf::Texture         texture;
        sf::Sprite          sprite;
    };
};


