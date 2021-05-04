#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Tank.h"
#include "Objectt.h"
#include "Gun.h"
#include "Entity_Manager.h"
#include "Map_Manager.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900,500), "SFML works!",Style::Fullscreen);
    window.setFramerateLimit(30);//fpssss
    View view(FloatRect(0,0,window.getSize().x,window.getSize().y));
    Texture probitieTexture;
    probitieTexture.loadFromFile("images/probitie.png");
    Texture tankBurnTexture1;
    tankBurnTexture1.loadFromFile("images/burn1.png");
    Texture tankBurnTexture2;
    tankBurnTexture2.loadFromFile("images/burn2.png");
    Texture tankBulletTexture;
    tankBulletTexture.loadFromFile("images/bullet.png");
    Texture miniBulletTexture;
    miniBulletTexture.loadFromFile("images/miniBullet.png");
    Burn_ExplosionManager brnExplManage;
    brnExplManage.addNewTexture("tankBullet",probitieTexture);
    brnExplManage.addNewTexture("tankBurn1",tankBurnTexture1);
    brnExplManage.addNewTexture("tankBurn2",tankBurnTexture2);
    BulletManager bulManage;
    bulManage.addNewTexture("tankBullet",tankBulletTexture);
    bulManage.addNewTexture("Bullet",miniBulletTexture);
    EntityManager entManage;
    MapManager level("jsid",entManage);
    entManage.afterCreate();
    Clock clock;
    bool pause=false;
    while (window.isOpen())
    {
        float timme=clock.getElapsedTime().asMicroseconds();
        clock.restart();timme/=1000;
        Event event;
        Vector2i ppos=Mouse::getPosition(window);//мышка
        Vector2f pos=window.mapPixelToCoords(ppos);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::Escape)
                    window.close();
                if(event.key.code == Keyboard::P)
                {//пауза
                    if(!pause) {pause=true;}
                    else {pause=false;}
                }
            }
            if (event.type == Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta==1)
                    view.zoom(0.8f);//приближаем
                if(event.mouseWheel.delta==-1)
                    view.zoom(1.2f);//отдаляем
            }
        }
        if(view.getSize().y>level.h) {view.zoom(level.h/view.getSize().y);}
        if(Keyboard::isKeyPressed(Keyboard::A))
            view.move(-(view.getSize().x/250),0);
        if(Keyboard::isKeyPressed(Keyboard::D))
            view.move((view.getSize().x/250),0);
        if(Keyboard::isKeyPressed(Keyboard::S))
            view.move(0,(view.getSize().y/250));
        if(Keyboard::isKeyPressed(Keyboard::W))
            view.move(0,-(view.getSize().y/250));
        if(view.getCenter().x+view.getSize().x/2.0>level.w)
            view.move(level.w-(view.getCenter().x+view.getSize().x/2.0),0);
        if(view.getCenter().y+view.getSize().y/2.0>level.h)
            view.move(0,level.h-(view.getCenter().y+view.getSize().y/2.0));
        if(view.getCenter().x-view.getSize().x/2.0<0)
            view.move(abs(view.getCenter().x-view.getSize().x/2.0),0);
        if(view.getCenter().y-view.getSize().y/2.0<0)
            view.move(0,abs(view.getCenter().y-view.getSize().y/2.0));
        window.setView(view);window.clear();level.Draw(window);
        entManage.update(window,bulManage,brnExplManage,timme,pos.x,pos.y,Mouse::isButtonPressed(Mouse::Button::Left),pause);
        bulManage.update(window,brnExplManage,timme,pause);
        brnExplManage.update(window,timme,pause);
        window.display();
    }
}
