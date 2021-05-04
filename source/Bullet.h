#pragma once
#include <SFML/Graphics.hpp>
#include<math.h>
#include<string>
#include<map>
#include<iostream>

using namespace sf;

class Bullet
{
private:
    float a,w,h,tarX,tarY,Sin,Cos,corner,K,B;
    bool life=true;
    std::string name;
public:
    Sprite sprite;
    Bullet(Texture& texture,std::string Name,float A,float X,float Y,float center_x,float center_y,float W,float H,float Corner,float TarX,float TarY)
    {
        name=Name;
        sprite.setTexture(texture);
        sprite.setOrigin(center_x,center_y);
        sprite.setRotation(Corner);
        sprite.setPosition(X,Y);//крутим вертим пулю как нам надо
        w=W;h=H;a=A;tarX=TarX;tarY=TarY;
        float dis=sqrt(pow(X-TarX,2)+pow(Y-TarY,2));
        Sin=(TarY-Y)/dis;//dis Sin и Cos для движения
        Cos=(TarX-X)/dis;corner=Corner;
        K=(Y-TarY)/((X-TarX)*1.0);
        B=((X*TarY)-(TarX*Y))/((X-TarX)*1.0);
    }
    std::string getName() {return name;}
    //FloatRect getRect(){return FloatRect(sprite.getPosition().x-sprite.getOrigin().x,sprite.getPosition().y-sprite.getOrigin().y,w,h);}
    float getA(){return a;}
    void update(float timme)
    {
        if(sqrt(pow(sprite.getPosition().x-tarX,2)+pow(sprite.getPosition().y-tarY,2))<=a*timme)//исправить баг, когда пули двигаются назад
            {sprite.setPosition(tarX,tarY);life=false;}
        else{sprite.move(a*timme*Cos,a*timme*Sin);}//проверка долетела ли пуля до цели, если нет - летит дальше
    }
    float getCorner(){return corner;}
    bool getLife() {return life;}
    bool getIntersection(float x,float center_x,float W,float y,float center_y,float H,float Corner)
    {//НЕ ЛЕЗЬ СЮДА,СЕРЬЁЗНО НЕ НАДО,ПОЖАЛЕЙ СВОИ НЕРВЫ,Я САМ НА ЭТУ ХРЕНЬ 3 ДНЯ УБИЛ!!!!
        if((tarX-sprite.getPosition().x)/Cos<sqrt(pow(tarX-x,2)+pow(tarY-y,2)))
        {if(sqrt(pow(sprite.getPosition().x-x,2)+pow(sprite.getPosition().y-y,2))<W){
        float maxX,maxY,minX,minY;
        if(cos(Corner)>0)//возможно не будет работать при углах кратных 90)//да, для Y тоже проверка по cos!
        {//координаты максимальных и минимальных точек по x и по y
            maxX=x+(W-center_x)*cos(Corner);
            minX=x-center_x*cos(Corner);
            maxY=y+(H-center_y)*cos(Corner);
            minY=y-center_y*cos(Corner);
        }
        else
        {//если угол по модулю больше 90 то меняем их местами
            minX=x+(W-center_x)*cos(Corner);
            maxX=x-center_x*cos(Corner);
            minY=y+(H-center_y)*cos(Corner);
            maxY=y-center_y*cos(Corner);
        }
        float k,b;//определяем уравнения прямых для крайних точек
        k=((y+(W-center_x)*sin(Corner))-(y-center_x*sin(Corner)))/((x+(W-center_x)*cos(Corner))-(x-center_x*cos(Corner)));
        b=((y-center_x*sin(Corner))-(x-center_x*cos(Corner))*k);
        float CENTERx=((sprite.getPosition().y-b)/k);//пересечение по x
        k=((y+(H-center_y)*cos(Corner))-(y-center_y*cos(Corner)))/((x-(H-center_y)*sin(Corner))-(x+center_y*sin(Corner)));//через max-ы и min-ы не делаю, так проще)
        b=((y-center_y*cos(Corner))-(x+center_y*sin(Corner))*k);
        float CENTERy=(sprite.getPosition().x*k + b);//пересечение по y
        if(abs(cos(Corner))==1) {CENTERx=0;CENTERy=0;}//если углы == 180 или 0
        maxX-=CENTERx;//переводим все точки в систему координат связанную с точками пересечения
        maxY-=CENTERy;
        minX-=CENTERx;
        minY-=CENTERy;
        if(((sprite.getPosition().x-CENTERx)*abs(cos(Corner))>minX/abs(cos(Corner)))&&//проверка
           ((sprite.getPosition().x-CENTERx)*abs(cos(Corner))<maxX/abs(cos(Corner)))&&//для x
           ((sprite.getPosition().y-CENTERy)*abs(cos(Corner))>minY/abs(cos(Corner)))&&//проверка
           ((sprite.getPosition().y-CENTERy)*abs(cos(Corner))<maxY/abs(cos(Corner))))//для Y
           {return true;}
        else {return false;}
    }}
    else
    {
        if(((x-center_x)*K+B>(y-center_y))&&((x-center_x)*K+B<(y-center_y+H)))
        {
            sprite.setPosition(x-center_x,(x-center_x)*K+B);
            life=false;return true;
        }
        else if(sprite.getPosition().y>y)
        {
        if(((y-center_y+H-B)/(K*1.0)>(x-center_x))&&((y-center_y+H-B)/(K*1.0)<(x-center_x+W)))
        {
            sprite.setPosition((y-center_y+H-B)/(K*1.0),y-center_y+H);
            life=false;return true;
        }
        else if(((y-center_y-B)/(K*1.0)>(x-center_x))&&((y-center_y-B)/(K*1.0)<(x-center_x+W)))
        {
            sprite.setPosition((y-center_y-B)/(K*1.0),y-center_y);
            life=false;return true;
        }
        }
        else
        {
        if(((y-center_y-B)/(K*1.0)>(x-center_x))&&((y-center_y-B)/(K*1.0)<(x-center_x+W)))
        {
            sprite.setPosition((y-center_y-B)/(K*1.0),y-center_y);
            life=false;return true;
        }
        else if(((y-center_y+H-B)/(K*1.0)>(x-center_x))&&((y-center_y+H-B)/(K*1.0)<(x-center_x+W)))
        {
            sprite.setPosition((y-center_y+H-B)/(K*1.0),y-center_y+H);
            life=false;return true;
        }
        }
        return false;
    }
    }
};
