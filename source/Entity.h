#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet_Manager.h"
#include "Burn_Explosion_Manager.h"

using namespace sf;

class Entity
{// родительский класс для всех орудий(пушки, танки, итд)
private:
    int life;//добавить больше общих переменных
    std::string Name;
    std::vector<Entity*>::iterator Target;//
    bool is_Checked=false;
public:
    Entity(int Life,std::string name){life=Life;Name=name;}
    int getLife(){return life;}
    void die(int k){life-=k;}
    std::string getName() {return Name;}
    void setTargetIterator(std::vector<Entity*>::iterator T) {Target = T;}
    std::vector<Entity*>::iterator getTargetIterator() {return Target;}//
    bool getCheck(){return is_Checked;}
    void setCheck(bool l) {is_Checked=l;}
    virtual void MouseIntersection(float mouseX,float mouseY,bool isMouseChecked)=0;
    virtual void update(BulletManager& bulManage,Burn_ExplosionManager& brnExplManage,std::vector<Entity*> entities,float timme) = 0;
    virtual void Draw(RenderWindow& window) = 0;
    virtual Vector2f getEntPosition() = 0;
    virtual float Get(std::string s) = 0;
    virtual void Set(std::string s,float val) = 0;
    //virtual FloatRect getRect() = 0;//функции которые по-любому им нужны
};
