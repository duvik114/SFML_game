#pragma once
#include <SFML/Graphics.hpp>
#include<math.h>
#include<string>
#include<map>
#include<iostream>

using namespace sf;

class Burn_Explosion
{//класс анимации
private:
    float schet=0.01,w,h,frames,a;
    bool life=true;
public:
    bool is_recharge;
    std::string name;
    Sprite sprite;
    float startX;
    Burn_Explosion(Texture& texture,std::string Name,float X,float Y,float center_x,float center_y,float W,float H,float corner,bool Is_recharge,float Frames)
    {
        is_recharge=Is_recharge;frames=Frames;
        sprite.setTexture(texture);
        sprite.setOrigin(center_x,center_y);
        sprite.setRotation(corner);
        sprite.setPosition(X,Y);w=W;h=H;
        name=Name;startX=X;a=100.0;
        if(is_recharge){a=500.0;schet=0.8;}
    }
    float GetCurrentFrame(){return schet;}
    void update(float timme)
    {
        sprite.setTextureRect(IntRect(0,floor(schet)*h,w,h));
        if(schet==0.8){schet=0.9;}
        else{schet+=timme/a;sprite.move(0.03*timme,0);}
        if(schet>=frames)//сама анимация!
        {
            //if(is_recharge) {schet=0;}
            //else {life=false;}
            life=false;
        }
    }
    bool getLife(){return life;}
};
