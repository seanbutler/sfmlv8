
#include "graphics.hpp"



void W::Window::DrawSprite(W::Sprite& S)
{ 
    get().draw(S.get());      
}


void W::Sprite::Draw(Window W)
{
    W.get().draw(sprite);
} 


