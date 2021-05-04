#pragma once
#include <SFML/Graphics.hpp>
#include"Objectt.h"

using namespace sf;

class Tank:public Entity
{//класс танков
private:
    float a,/*Dis,*/mashS,mashScorner,mashMaxcorner,minLine=0,maxLine=0,minX=32000,maxX=-1;
    int schet=0,mashSchet=0,reload,mashReload,gradus,mashgradus;//перезарядка и максимальный угол отклонения снарядов
    bool is_move=true,is_shoot=true,is_mashShoot=true;
    std::string bulName,mashBulname;
public:
    Turret tankPlatform;
    Turret tankTurret;
    Turret mashTurret;//доработать появление с заданным углом, если надо будет)
    Tank(std::string name,Texture& platTexture,Texture& turretTexture,Texture& mashTexture,std::string Bulname,std::string MashBulname,float A,int Reload,int MashReload,float platv_corner,float turv_corner,float mashv_corner,float X,float Y,int Life,float platCenter_X,float platCenter_Y,
         float platW,float platH,/*float DiS,*/float turCenter_X,float turCenter_Y,float turW,float turH,float MashX,float MashY,float mashCenterX,float mashCenterY,float mashW,float mashH,float MashMaxcorner,int gradus,int MashGradus,bool is_flip)
    :tankPlatform(platTexture,X,Y,platCenter_X,platCenter_Y,platW,platH,platv_corner,is_flip),tankTurret(turretTexture,X,Y,turCenter_X,turCenter_Y,turW,turH,turv_corner,is_flip),
    mashTurret(mashTexture,X+MashX,Y+MashY,mashCenterX,mashCenterY,mashW,mashH,mashv_corner,is_flip),Entity(Life,name)
    {
        reload=Reload;bulName=Bulname;
        mashBulname=MashBulname;a=A;//Dis=DiS;
        this->gradus=gradus;mashMaxcorner=MashMaxcorner;
        mashS=sqrt(pow(MashX,2)+pow(MashY,2));mashScorner=atan2(MashY,MashX)*180/3.1415;
        mashgradus=MashGradus;mashReload=MashReload;
        //if(is_flip) {mashTurret.sprite.setPosition(X-mashS*cos(mashScorner),Y-mashS*sin(mashScorner));}
        //всё остальное идёт в Turret-ы
    }
    void Draw(RenderWindow& window)
    {
        window.draw(tankPlatform.sprite);
        window.draw(mashTurret.sprite);
        window.draw(tankTurret.sprite);
    }
   // float getDis(){return Dis;}
    void Move(bool dir_back,float timme)
    {//функ-я движения
        float x=a*timme*cos(tankPlatform.getCorner()*3.1415/180.0);
        float y=a*timme*sin(tankPlatform.getCorner()*3.1415/180.0);
        if(tankPlatform.getTarCoords().y==getEntPosition().y)
        {
            if(tankPlatform.getTarCoords().x<=getEntPosition().x) {x=-(a*timme);y=0;}
            else {x=a*timme;y=0;}
        }
        if(dir_back){x=-x;y=-y;}//если надо двигаться назад
        tankPlatform.sprite.move(x,y);
        tankTurret.sprite.move(x,y);
        mashTurret.sprite.move(x,y);
    }
    void setPlatformTarget(float x,float y){tankPlatform.setTarget(x,y);}
    void setTurretTarget(float x,float y){tankTurret.setTarget(x,y);}
    void setMashTarget(float x,float y){mashTurret.setTarget(x,y);}
    Vector2f getEntPosition() {Vector2f vec;vec.x=tankPlatform.sprite.getPosition().x;vec.y=tankPlatform.sprite.getPosition().y;return vec;}
    void setEntPosition(float x,float y) {tankPlatform.sprite.setPosition(x,y);tankTurret.sprite.setPosition(x,y);mashTurret.sprite.setPosition(x,y);}
    float Get(std::string s)
    {
        if(s=="maxLine") {return maxLine;}
        else if(s=="minLine") {return minLine;}
        else if(s=="maxX") {return maxX;}
        else if(s=="minX") {return minX;}
    }
    void Set(std::string s,float val)
    {
        if(s=="maxLine") {maxLine=val;}
        else if(s=="minLine") {minLine=val;}
        else if(s=="maxX") {maxX=val;}
        else if(s=="minX") {minX=val;}
    }
    void MouseIntersection(float mouseX,float mouseY,bool isMouseChecked)
    {
        if(sqrt(pow(tankPlatform.sprite.getPosition().x-mouseX,2)+pow(tankPlatform.sprite.getPosition().y-mouseY,2))<tankPlatform.w)//
        {
            if(!isMouseChecked)
            {
                tankPlatform.sprite.setColor(Color(255,25,25));
                tankTurret.sprite.setColor(Color(255,25,25));
                mashTurret.sprite.setColor(Color(255,25,25));
            }
            else
            {
            tankPlatform.sprite.setColor(Color(255,255,255));
            tankTurret.sprite.setColor(Color(255,255,255));
            mashTurret.sprite.setColor(Color(255,255,255));
            }
            setCheck(isMouseChecked);
        }
        else
        {
            tankPlatform.sprite.setColor(Color(255,255,255));
            tankTurret.sprite.setColor(Color(255,255,255));
            mashTurret.sprite.setColor(Color(255,255,255));
        }
    }
    void update(BulletManager& bulManage,Burn_ExplosionManager& brnExplManage,std::vector<Entity*> entities,float timme)
    {
        //Проверка на столкновения с пулями//ПОМЕНЯТЬ НА БОЛЕЕ КОРРЕКТНУЮ!!!!
        if(bulManage.bullets.begin()!=bulManage.bullets.end())
            for(std::vector<Bullet*>::iterator ti=bulManage.bullets.begin();ti<bulManage.bullets.end();ti++)
                if(bulManage.bullets.begin()!=bulManage.bullets.end())
                {
                    float d=sqrt(pow((*ti)->sprite.getPosition().x-tankPlatform.sprite.getPosition().x,2)+pow((*ti)->sprite.getPosition().y-tankPlatform.sprite.getPosition().y,2));
                    if(d<(*ti)->getA()*timme)
                    {
                    if((*ti)->getIntersection(tankPlatform.sprite.getPosition().x,tankPlatform.sprite.getOrigin().x-4,tankPlatform.w-4,tankPlatform.sprite.getPosition().y,tankPlatform.sprite.getOrigin().y-2,tankPlatform.h-2,tankPlatform.getCorner()*3.1415/180.0))
                    {
                        brnExplManage.Create((*ti)->getName(),(*ti)->sprite.getPosition().x,(*ti)->sprite.getPosition().y,(*ti)->getCorner());die(1);
                        if(getLife()==0) {die(1);brnExplManage.Create("tankBurn",tankPlatform.sprite.getPosition().x,tankPlatform.sprite.getPosition().y,0);}
                        bulManage.bullets.erase(ti);
                    }}
                }//это была анимация попадания
        //Проверка окончена
    if(getLife()>0)
    {
        //Вот это начало консерва
        is_move=true;is_shoot=true;is_mashShoot=true;//разрешение на движение и на стрельбу
        if(entities.begin()!=entities.end())//проходимся по циклу(знаю, жрать будет много, но ничего лучше я и не придумал)
            {for(std::vector<Entity*>::iterator ti=entities.begin();ti!=entities.end();ti++){
            if(((*ti)->getName()=="tank")&&/*((*ti)->getLife()>0)&&*/((*ti)->getEntPosition().x<getEntPosition().x))
            {
            if(sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2))<4000){
                /*float targetDis=sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2));
                float tankDis=sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2));*/
                float dif,c=atan2((*ti)->getEntPosition().y-getEntPosition().y,(*ti)->getEntPosition().x-getEntPosition().x)*180/3.1415;
                if(((tankTurret.getCorner()>0)&&(c<0))||((tankTurret.getCorner()<0)&&(c>0))) {dif=tankTurret.getCorner()+c;}
                else {dif=tankTurret.getCorner()-c;}dif=abs(dif);
                if(dif<gradus/100.0) {is_shoot=false;}
            }}
            if(((*ti)->getName()=="tank")&&/*((*ti)->getLife()>0)&&*/((*ti)->getEntPosition().x<getEntPosition().x))
            {
            if(sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2))<4000){
                /*float targetDis=sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2));
                float tankDis=sqrt(pow((*ti)->getEntPosition().x-getEntPosition().x,2)+pow((*ti)->getEntPosition().y-getEntPosition().y,2));*/
                float dif,c=atan2((*ti)->getEntPosition().y-getEntPosition().y,(*ti)->getEntPosition().x-getEntPosition().x)*180/3.1415;
                if(((mashTurret.getCorner()>0)&&(c<0))||((mashTurret.getCorner()<0)&&(c>0))) {dif=mashTurret.getCorner()+c;}
                else {dif=mashTurret.getCorner()-c;}dif=abs(dif);
                if(dif<mashgradus/100.0) {is_mashShoot=false;}
            }}
            //смотрим не ссылаетс ли итератор на этот же объект и не слишком ли он ?позади?
            if((((*ti)->getEntPosition().x!=getEntPosition().x)||((*ti)->getEntPosition().y!=getEntPosition().y))&&((*ti)->getEntPosition().x<=getEntPosition().x+111)&&((*ti)->getName()=="tank")){//пока добавлю сюда танк

            if(tankPlatform.getTarCoords().x==0)//
            {
                if(abs((*ti)->getEntPosition().x-getEntPosition().x)<3000){
                float dist=getEntPosition().y-(*ti)->getEntPosition().y;
                if(abs(dist)<111){
                if(getEntPosition().x-(*ti)->getEntPosition().x>=1112) {maxX=(*ti)->getEntPosition().x+1112;}
                else {maxX=getEntPosition().x;}
                if(dist>=0){setPlatformTarget(maxX,(*ti)->getEntPosition().y+112);}
                if(dist<0) {setPlatformTarget(maxX,(*ti)->getEntPosition().y-112);}
                maxLine=(*ti)->getEntPosition().y;minLine=(*ti)->getEntPosition().y;minX=(*ti)->getEntPosition().x;
            }}}
            else
            {
                if(abs((*ti)->getEntPosition().x-getEntPosition().x)<4000){
                if(((*ti)->getName()=="tank")&&abs((getEntPosition().x-(*ti)->getEntPosition().x<101))&&(abs(getEntPosition().y-(*ti)->getEntPosition().y)<101)){
                    if((*ti)->getEntPosition().y<getEntPosition().y){
                    if((getEntPosition().y<(*ti)->Get("minLine")+(maxLine-(*ti)->Get("minLine"))/2.0)&&((*ti)->getLife()>0)){is_move=false;}
                    else {setPlatformTarget(maxX,maxLine+112);}}
                    else if((getEntPosition().y>=minLine+((*ti)->Get("maxLine")-minLine)/2.0)&&((*ti)->getLife()>0)){is_move=false;}
                    else {setPlatformTarget(maxX,minLine-112);}}
                else
                {if/*(*/((*ti)->getEntPosition().y>maxLine){
                if((*ti)->getEntPosition().y-maxLine<222)
                {if(((*ti)->getName()=="tank")&&((*ti)->getEntPosition().y-getEntPosition().y<222)&&(getEntPosition().x-(*ti)->getEntPosition().x<111))
                {
                    if((getEntPosition().y>=minLine+((*ti)->Get("maxLine")-minLine)/2.0)&&((*ti)->getLife()>0)){is_move=false;}
                    else {setPlatformTarget(maxX,minLine-112);}
                }
                else {if((*ti)->getEntPosition().x<minX) {minX=(*ti)->getEntPosition().x;}
                if((*ti)->getEntPosition().x+1112>maxX)
                    {
                        if(getEntPosition().x-(*ti)->getEntPosition().x>=1112) {maxX=(*ti)->getEntPosition().x+1112;}
                        else {maxX=getEntPosition().x;}
                    }
                maxLine=(*ti)->getEntPosition().y;
                if(getEntPosition().y>=minLine+(maxLine-minLine)/2.0) {setPlatformTarget(maxX,maxLine+112);}
                else {setPlatformTarget(maxX,minLine-112);}}
                }}
                else if/*(*/((*ti)->getEntPosition().y<minLine){
                if(minLine-(*ti)->getEntPosition().y<222)
                {if(((*ti)->getName()=="tank")&&(getEntPosition().y-(*ti)->getEntPosition().y<222)&&(getEntPosition().x-(*ti)->getEntPosition().x<111))
                {
                    if((getEntPosition().y<(*ti)->Get("minLine")+(maxLine-(*ti)->Get("minLine"))/2.0)&&((*ti)->getLife()>0)){is_move=false;}
                    else {setPlatformTarget(maxX,maxLine+112);}
                }
                else {if((*ti)->getEntPosition().x<minX) {minX=(*ti)->getEntPosition().x;}
                if((*ti)->getEntPosition().x+1112>maxX)
                    {
                        if(getEntPosition().x-(*ti)->getEntPosition().x>=1112) {maxX=(*ti)->getEntPosition().x+1112;}
                        else {maxX=getEntPosition().x;}
                    }
                minLine=(*ti)->getEntPosition().y;
                if(getEntPosition().y>=minLine+(maxLine-minLine)/2.0) {setPlatformTarget(maxX,maxLine+112);}
                else {setPlatformTarget(maxX,minLine-112);}}
                }}}}
            }}
            }}
        //Вот это конец консерва
        setTurretTarget((*getTargetIterator())->getEntPosition().x,(*getTargetIterator())->getEntPosition().y);/////////////////////////////////
        mashTurret.sprite.setPosition(tankPlatform.sprite.getPosition().x+mashS*cos((tankPlatform.getCorner()+mashScorner)*3.1415/180.0),tankPlatform.sprite.getPosition().y+mashS*sin((tankPlatform.getCorner()+mashScorner)*3.1415/180.0));
        schet++;mashSchet++;
        tankTurret.targetRotation();//задаём цель башне
        mashTurret.targetRotation();//и пулемёту
        float Cor=mashTurret.getCorner();
        if(cos(tankPlatform.getCorner()*3.1415/180.0)<0)
        {
            if((tankPlatform.getCorner()>0)&&(Cor<0)) {Cor+=360;}
            if((tankPlatform.getCorner()<0)&&(Cor>0)) {Cor-=360;}
        }
        if(Cor>tankPlatform.getCorner()+mashMaxcorner) {mashTurret.setCorner(tankPlatform.getCorner()+mashMaxcorner);}
        if(Cor<tankPlatform.getCorner()-mashMaxcorner) {mashTurret.setCorner(tankPlatform.getCorner()-mashMaxcorner);}
        //логика объекта типа танк
        //float dis=sqrt(pow(tankPlatform.getTarCoords().x-getEntPosition().x,2)+pow(tankPlatform.getTarCoords().y-getEntPosition().y,2));
        /*if(dis<=Dis){is_move=false;}*/
        tankPlatform.targetRotation();
        //Консерв встроен частично и сюда
        if((tankPlatform.getTarget())&&(is_move))
        {
            if((sqrt(pow(tankPlatform.getTarCoords().x-getEntPosition().x,2)+pow(tankPlatform.getTarCoords().y-getEntPosition().y,2))<=a*timme)/*&&(tankPlatform.getTarCoords().x!=0)*/)
            {
                setEntPosition(tankPlatform.getTarCoords().x,tankPlatform.getTarCoords().y);setPlatformTarget(0,getEntPosition().y);
                mashTurret.sprite.setPosition(tankPlatform.sprite.getPosition().x+mashS*cos((tankPlatform.getCorner()+mashScorner)*3.1415/180.0),tankPlatform.sprite.getPosition().y+mashS*sin((tankPlatform.getCorner()+mashScorner)*3.1415/180.0));
            }
            else {Move(false,timme);}
        }
        if((tankPlatform.getTarCoords().x==getEntPosition().x)&&(tankPlatform.getTarCoords().y==getEntPosition().y)) {setPlatformTarget(0,getEntPosition().y);}
        //Дальше консерва не будет
        //логика закончЕна
        if(schet>=reload)
        {//если он готов стрелять
            if(tankTurret.getTarget())
            {//и если цель подтверждена
            double dIs=sqrt(pow(tankTurret.getTarCoords().x-tankTurret.sprite.getPosition().x,2)+pow(tankTurret.getTarCoords().y-tankTurret.sprite.getPosition().y,2));
            if((dIs>tankPlatform.w)&&(is_shoot))
            {
                schet=0;
                        dIs-=rand()%(int)(dIs*tan(gradus*3.1415/18000.0));////и это тоже ПОТОМ ИСПРАВИТЬ!!!!
                        float b=(rand()%gradus-gradus/2)*3.1415/18000.0;
                        float a=tankTurret.getCorner()*3.1415/180.0;//это для того, чтобы
                        float finx=tankTurret.sprite.getPosition().x+dIs*cos(a+b);//пуля попадала в
                        float finy=tankTurret.sprite.getPosition().y+dIs*sin(a+b);//рандомное место цели
                bulManage.Create(bulName,tankTurret.sprite.getPosition().x+tankPlatform.w*cos(a+b),tankTurret.sprite.getPosition().y+tankPlatform.w*sin(a+b),(a+b)*180/3.1415,finx,finy);
                brnExplManage.Create("out-"+bulName,tankTurret.sprite.getPosition().x+tankTurret.w*cos(a),tankTurret.sprite.getPosition().y+tankTurret.w*sin(a),tankTurret.getCorner());//да, надо так много для анимации выстрела
            }
            else schet-=1;
            }
            else schet-=1;
        }
        if(mashSchet>=mashReload)
        {//если он (пулемёт) готов стрелять
            if(mashTurret.getTarget())
            {//и если цель подтверждена
            double dIs=sqrt(pow(mashTurret.getTarCoords().x-mashTurret.sprite.getPosition().x,2)+pow(mashTurret.getTarCoords().y-mashTurret.sprite.getPosition().y,2));
            if((dIs>=(tankPlatform.w/2-abs(mashS*cos(mashScorner*3.1415/180.0)))*2)&&(is_mashShoot))//ПОМЕНЯЙ!!!!
            {
                mashSchet=0;
                        dIs-=rand()%(int)(dIs*tan(mashgradus*3.1415/18000.0));////и это тоже ПОТОМ ИСПРАВИТЬ!!!!
                        float b=(rand()%mashgradus-mashgradus/2)*3.1415/18000.0;
                        float a=mashTurret.getCorner()*3.1415/180.0;//это для того, чтобы
                        float finx=mashTurret.sprite.getPosition().x+dIs*cos(a+b);//пуля попадала в
                        float finy=mashTurret.sprite.getPosition().y+dIs*sin(a+b);//рандомное место цели
                bulManage.Create(mashBulname,mashTurret.sprite.getPosition().x+tankPlatform.w*cos(a+b),mashTurret.sprite.getPosition().y+tankPlatform.w*sin(a+b),(a+b)*180/3.1415,finx,finy);//исправь место появления пулИ!!!!
                brnExplManage.Create("out-"+mashBulname,mashTurret.sprite.getPosition().x+mashTurret.w*cos(a),mashTurret.sprite.getPosition().y+mashTurret.w*sin(a),mashTurret.getCorner());//да, надо так много для анимации выстрела
            }
            else mashSchet-=1;
            }
            else mashSchet-=1;
        }
    }
    }
};

