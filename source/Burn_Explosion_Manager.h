#pragma once
#include <SFML/Graphics.hpp>
/*#include<math.h>
#include<string>
#include<map>
#include<iostream>*/
#include "Burn_Explosion.h"
#include <list>

using namespace sf;

class Burn_ExplosionManager
{
private:
   std::map<std::string,Texture> texturesMap;//список с текстурами
   std::list<Burn_Explosion*> brnExpl;
public:
    void addNewTexture(std::string str,Texture& t) {texturesMap[str]=t;}//добавление новой текстуры в список
    void Create(String str,float x,float y,float corner)
    {//создаЄм новый взрыв/огонь/и.т.д.
        if(str=="tankBullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"tankBullet",x,y,15,30,100,60,corner,false,1));
        else if(str=="tankBurn")
        {
            if(rand()%2==0) {brnExpl.push_back(new Burn_Explosion(texturesMap["tankBurn1"],"tankBurn",x,y,16,16,32,32,0,true,6));}
            else {brnExpl.push_back(new Burn_Explosion(texturesMap["tankBurn2"],"tankBurn",x,y,16,16,32,32,0,true,6));}
        }
        else if(str=="not-tankBullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"not-tankBullet",x,y,15,30,100,60,corner,false,4));
        else if(str=="out-tankBullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"out-tankBullet",x,y,15,30,100,60,corner,false,1));
        else if(str=="Bullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"Bullet",x,y,15,30,100,60,corner,false,1));//пока так потом ѕќћ≈Ќя“№!!!!
        else if(str=="not-Bullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"not-Bullet",x,y,15,30,100,60,corner,false,1));//как текстуры по€в€тс€)
        else if(str=="out-Bullet")
            brnExpl.push_back(new Burn_Explosion(texturesMap["tankBullet"],"out-Bullet",x,y,15,30,100,60,corner,false,1));
    }
    void update(RenderWindow& window,float timme,bool& p)
    {
        if(brnExpl.begin()!=brnExpl.end())
        {
            for(std::list<Burn_Explosion*>::iterator it=brnExpl.begin();it != brnExpl.end();it++)
        {
            if(brnExpl.begin()!=brnExpl.end())
            {//обновл€ем все существующие анимации
                if(!p) (*it)->update(timme);
                if(((*it)->is_recharge)&&((*it)->GetCurrentFrame()>1.1))
                {
                    Create((*it)->name,(*it)->startX,(*it)->sprite.getPosition().y,0);
                    (*it)->is_recharge=false;
                }
                if((*it)->getLife()) {window.draw((*it)->sprite);}
                else {brnExpl.erase(it);}
            }
        }
        }
    }
};
