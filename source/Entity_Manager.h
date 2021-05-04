#pragma once
#include <SFML/Graphics.hpp>
#include"Objectt.h"
#include "Tank.h"
#include "Gun.h"

using namespace sf;

class EntityManager
{
private:
    std::map<std::string,Texture> TextureMap;
    std::vector<Entity*>entities;
    std::vector<Entity*>checkEntities;
public:
    EntityManager()
    {
    Texture tanPlatformTexture;
    tanPlatformTexture.loadFromFile("images/Tan.png");
    TextureMap["tankPlatform"]=tanPlatformTexture;
    Texture tanTurretTexture;
    tanTurretTexture.loadFromFile("images/tankTower.png");
    TextureMap["tankTurret"]=tanTurretTexture;
    Texture tanSmallTurretTexture;
    tanSmallTurretTexture.loadFromFile("images/TankSmallTurret.png");
    TextureMap["tankSmallTurret"]=tanSmallTurretTexture;
    Texture pushkaPlatformTexture;
    pushkaPlatformTexture.loadFromFile("images/gunPlatform.png");
    TextureMap["gunPlatform"]=pushkaPlatformTexture;
    Texture pushkaTurretTexture;
    pushkaTurretTexture.loadFromFile("images/gunBarrel.png");
    TextureMap["gunTurret"]=pushkaTurretTexture;
    }
    void Create(std::string str,float x,float y)
    {
        if(str=="tank")
        {
            Tank *t=new Tank("tank",TextureMap["tankPlatform"],TextureMap["tankTurret"],TextureMap["tankSmallTurret"],"tankBullet","Bullet",0.1,50,20,0.9,0.3,0.2,x,y,4,44,25,90,50,12,11,44,23,35,-11,2,2,9,4,30,200,555,true);
            t->setPlatformTarget(0,y);t->setTurretTarget(0,y);t->setMashTarget(x,y);/*t->setTargetIterator(findTargetIterator("pushka",t));*/entities.push_back(t);
        }
        if(str=="pushka")
        {
            Gun *g=new Gun("pushka",TextureMap["gunPlatform"],TextureMap["gunTurret"],"tankBullet",99,30,1.0,x,y,2,37,20,25,40,11,11,42,22,150,false,true);
            g->setTarget(11111,y);entities.push_back(g);
        }
    }
    std::vector<Entity*>::iterator findTargetIterator(std::string str,std::vector<Entity*>::iterator ti)
    {
        float dis=32000;std::vector<Entity*>::iterator tar = entities.end();
        for(std::vector<Entity*>::iterator it=entities.begin();it<entities.end();it++)
        {
            if(((*it)->getName()==str)&&((*it)->getLife()>0))
            {float d=sqrt(pow((*it)->getEntPosition().x-(*ti)->getEntPosition().x,2)+pow((*it)->getEntPosition().y-(*ti)->getEntPosition().y,2));
            if(d<dis){dis=d;tar=it;}}
        }
        return tar;
    }
    void afterCreate()
    {
        for(std::vector<Entity*>::iterator ti=entities.begin();ti<entities.end();ti++)
        {
            if((*ti)->getName()=="tank")
                (*ti)->setTargetIterator(findTargetIterator("pushka",ti));
            if((*ti)->getName()=="pushka")
                (*ti)->setTargetIterator(findTargetIterator("tank",ti));
        }
    }
    void update(RenderWindow& window,BulletManager& bulManage,Burn_ExplosionManager& brnExplManage,float timme,float x,float y,bool isMouseChecked,bool& p)
    {
        if(entities.begin()!=entities.end())
            for(std::vector<Entity*>::iterator ti=entities.begin();ti<entities.end();ti++)
            {
                if(((*ti)->getName()=="tank")&&((*ti)->getLife()>0)&&((*(*ti)->getTargetIterator())->getLife()<=0))
                {
                    std::vector<Entity*>::iterator tar = findTargetIterator("pushka",ti);
                    if(tar != entities.end())
                        (*ti)->setTargetIterator(tar);
                }
                if((*ti)->getCheck()==true)
                {
                    if((*ti)->getName()=="pushka"){checkEntities.push_back((*ti));}
                    else if((*ti)->getName()=="tank")
                    {
                        (*ti)->setCheck(false);
                        if(checkEntities.begin()!=checkEntities.end())
                            for(std::vector<Entity*>::iterator tit=checkEntities.begin();tit<checkEntities.end();tit++)
                                {(*tit)->setTargetIterator(ti);(*tit)->setCheck(false);}
                        checkEntities.clear();
                    }
                }
                (*ti)->MouseIntersection(x,y,isMouseChecked);
                if(!p) (*ti)->update(bulManage,brnExplManage,entities,timme);
                (*ti)->Draw(window);
            }
    }
};
