#pragma once
#include <SFML/Graphics.hpp>
#include<math.h>
#include<string>
#include<map>
#include<iostream>

using namespace sf;

class Platform
{//класс неподвижных объектов(платформыб, мб мины?)
private:
    float corner=0;
public:
    float w,h;
    Sprite sprite;
    Platform(Texture& texture,float X,float Y,float center_X,float center_Y,float W,float H,bool isFlip)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(center_X,center_Y);
        if(isFlip) {corner=180;}//если спрайт перевёрнут
        sprite.setRotation(corner);
        sprite.setPosition(X,Y);
        w=W;h=H;
    }
    float getCorner(){return corner;}
};
