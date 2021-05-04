#pragma once
#include <SFML/Graphics.hpp>
#include "Objectt.h"

using namespace sf;

class Gun:public Entity
{
private:
    float max_corner/*,tarX,tarY*/;
    int schet=0,reload=0,gradus;//перезарядка и максимальный угол отклонения снарядов
    bool is_weak,is_Flip;
    std::string bulName;
    //std::vector<Entity*>::iterator Target;
public:
    Platform gunPlatform;
    Turret gunTurret;
    Gun(std::string name,Texture& platTexture,Texture& turretTexture,std::string Bulname,int Reload,float Max_corner,float Vcorner,float X,float Y,int Life,float platCenter_X,float platCenter_Y,float platW,float platH,float turCenter_X,float turCenter_Y,float turW,float turH,int gradus,bool is_flip,bool isWeak)
    :gunPlatform(platTexture,X,Y,platCenter_X,platCenter_Y,platW,platH,is_flip),gunTurret(turretTexture,X,Y,turCenter_X,turCenter_Y,turW,turH,Vcorner,is_flip),Entity(Life,name)
    {
        max_corner=Max_corner;is_Flip=is_flip;reload=Reload;
        is_weak=isWeak;this->gradus=gradus;bulName=Bulname;//всё остальное идёт в turret & platform
    }
    void Draw(RenderWindow& window)
    {
        window.draw(gunPlatform.sprite);
        window.draw(gunTurret.sprite);
    }
   // void setTargetIterator(std::vector<Entity*>::iterator T) {Target=T;}
   // std::vector<Entity*>::iterator getTargetIterator() {return Target;}
    void setTarget(float x,float y){gunTurret.setTarget(x,y);}
    Vector2f getEntPosition() {Vector2f vec;vec.x=gunPlatform.sprite.getPosition().x;vec.y=gunPlatform.sprite.getPosition().y;return vec;}
    float Get(std::string s){return 0;}
    void Set(std::string s,float val){}
    void MouseIntersection(float mouseX,float mouseY,bool isMouseChecked)
    {
        if(sqrt(pow(gunPlatform.sprite.getPosition().x-mouseX,2)+pow(gunPlatform.sprite.getPosition().y-mouseY,2))<gunTurret.w)
        {
            gunPlatform.sprite.setColor(Color(200,50,50));
            gunTurret.sprite.setColor(Color(200,50,50));
            if(isMouseChecked)
            {
                setCheck(true);
                gunPlatform.sprite.setColor(Color(255,25,25));
                gunTurret.sprite.setColor(Color(255,25,25));
            }
        }
        else if(!getCheck())
        {
            gunPlatform.sprite.setColor(Color(255,255,255));
            gunTurret.sprite.setColor(Color(255,255,255));
        }
        else
        {
            gunPlatform.sprite.setColor(Color(200,50,50));
            gunTurret.sprite.setColor(Color(200,50,50));
        }
    }
    void update(BulletManager& bulManage,Burn_ExplosionManager& brnExplManage,std::vector<Entity*> entities,float timme)
    {
        //Проверка на столкновения с пулями\/Переделай нормально!!!!
        if(bulManage.bullets.begin()!=bulManage.bullets.end())
            for(std::vector<Bullet*>::iterator ti=bulManage.bullets.begin();ti<bulManage.bullets.end();ti++)
                if(bulManage.bullets.begin()!=bulManage.bullets.end())
                {
                    float d=sqrt(pow((*ti)->sprite.getPosition().x-gunPlatform.sprite.getPosition().x,2)+pow((*ti)->sprite.getPosition().y-gunPlatform.sprite.getPosition().y,2));
                    if(d<(*ti)->getA()*timme)
                    {
                    if((*ti)->getIntersection(gunPlatform.sprite.getPosition().x,gunPlatform.sprite.getOrigin().x,gunPlatform.w,gunPlatform.sprite.getPosition().y,gunPlatform.sprite.getOrigin().y,gunPlatform.h,gunPlatform.getCorner()*3.1415/180.0))
                    {
                        brnExplManage.Create((*ti)->getName(),(*ti)->sprite.getPosition().x,(*ti)->sprite.getPosition().y,(*ti)->getCorner());die(1);
                        if(getLife()==0) {brnExplManage.Create("tankBurn",gunPlatform.sprite.getPosition().x,gunPlatform.sprite.getPosition().y,0);}
                        bulManage.bullets.erase(ti);
                    }
                    }
                }//это была анимация попадания
        //Проверка окончена
    if(getLife()>0)
    {
        setTarget((*getTargetIterator())->getEntPosition().x,(*getTargetIterator())->getEntPosition().y);
        gunTurret.targetRotation();//поворачиваем башню
        if(gunTurret.getCorner()>gunPlatform.getCorner()+max_corner){gunTurret.setCorner(gunPlatform.getCorner()+max_corner);}//проверка на максимальные углы
        if(gunTurret.getCorner()<gunPlatform.getCorner()-max_corner){gunTurret.setCorner(gunPlatform.getCorner()-max_corner);}
        schet++;
        if(schet>=reload)
        {//если готов стрелять
            if(gunTurret.getTarget())
            {// и если цель подтверждена
            double dIs=sqrt(pow(gunTurret.getTarCoords().x-gunTurret.sprite.getPosition().x,2)+pow(gunTurret.getTarCoords().y-gunTurret.sprite.getPosition().y,2));
            if(dIs>=gunTurret.w)
            {
                 schet=0;
                        dIs-=rand()%(int)(dIs*tan(gradus*3.1415/18000.0));////и это тоже ПОТОМ ИСПРАВИТЬ!!!!
                        float b=(rand()%gradus-gradus/2)*3.1415/18000.0;
                        float a=gunTurret.getCorner()*3.1415/180.0;//это для того, чтобы
                        float finx=gunTurret.sprite.getPosition().x+dIs*cos(a+b);//пуля попадала в
                        float finy=gunTurret.sprite.getPosition().y+dIs*sin(a+b);//рандомное место цели
                bulManage.Create(bulName,gunTurret.sprite.getPosition().x+(gunTurret.w+10)*cos(a+b),gunTurret.sprite.getPosition().y+(gunTurret.w+10)*sin(a+b),(a+b)*180/3.1415,finx,finy);
                brnExplManage.Create("out-"+bulName,gunTurret.sprite.getPosition().x+gunTurret.w*cos(a),gunTurret.sprite.getPosition().y+gunTurret.w*sin(a),gunTurret.getCorner());//да, надо так много для анимации выстрела
            }
            else schet-=1;
            }
            else schet-=1;
        }

    }
    }
};
