#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Burn_Explosion_Manager.h"

using namespace sf;

class BulletManager
{
private:
    std::map<std::string,Texture> texturesMap;
public:
    std::vector<Bullet*> bullets;
    void addNewTexture(std::string str, Texture& t){texturesMap[str]=t;}
    void Create(std::string str,float x,float y,float corner,float tarX,float tarY)
    {
        if(str=="tankBullet")
            bullets.push_back(new Bullet(texturesMap["tankBullet"],"tankBullet",23,x,y,5,4,10,5,corner,tarX,tarY));
        else if(str=="Bullet")
            bullets.push_back(new Bullet(texturesMap["Bullet"],"Bullet",24,x,y,5,0,9,1,corner,tarX,tarY));
    }
    void update(RenderWindow& window,Burn_ExplosionManager& brnExplManage,float timme,bool& p)
    {
        if(bullets.begin()!=bullets.end())
        {
            for(std::vector<Bullet*>::iterator it=bullets.begin();it<bullets.end();it++)
        {
            if(bullets.begin()!=bullets.end())
            {//обновляем все существующие анимации
                if(!p) (*it)->update(timme);
                if((*it)->getLife()) {window.draw((*it)->sprite);}
                else
                {
                    brnExplManage.Create("not-"+(*it)->getName(),(*it)->sprite.getPosition().x,(*it)->sprite.getPosition().y,(*it)->getCorner());
                    bullets.erase(it);
                }
            }
        }
        }
    }
};
