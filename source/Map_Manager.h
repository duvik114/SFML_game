#include <SFML/Graphics.hpp>
#include "Entity_Manager.h"
#include "tinyxml.h"

using namespace sf;

class MapManager
{//менеджер карты
private:
    //std::map<int,Texture> TextureMap;
    Texture mapTexture;
    Sprite mapSprite;
    int mapMas[36][16];//массив с н”мером картинки
public:
    float w,h,tw,th;//длина высота карты и картинки
    MapManager(std::string mapStr,EntityManager& entManage)
    {
        mapStr="maps/mapSets/"+mapStr+".tmx";
        //const char levelStr=mapStr.c_str();
        //преобразование в const char
        TiXmlDocument *lXmlDoc=new TiXmlDocument("maps/mapSets/map1.tmx");
        mapTexture.loadFromFile("maps/tileSets/tile.png");mapSprite.setTexture(mapTexture);//потом исправить на разные наборы тайлсетов!!!!
        if(!lXmlDoc->LoadFile()) {std::cout<<"ERROR";}
        TiXmlElement *tiles=lXmlDoc->FirstChildElement("map");
        tiles->QueryFloatAttribute("width",&w);tiles->QueryFloatAttribute("tilewidth",&tw);w*=tw;
        tiles->QueryFloatAttribute("height",&h);tiles->QueryFloatAttribute("tileheight",&th);h*=th;
        tiles=tiles->FirstChildElement("layer");
        tiles=tiles->FirstChildElement("data");
        tiles=tiles->FirstChildElement("tile");
        for(int i=0;i<w/tw;i++)
            for(int j=0;j<h/th;j++)
            {//процедура записи в массив картинок карты
            if(tiles!=NULL)
                {int k;tiles->QueryIntAttribute("gid",&k);mapMas[i][j]=k;
                tiles=tiles->NextSiblingElement("tile");}
            }
        TiXmlElement *objects=lXmlDoc->FirstChildElement("map");
        objects=objects->FirstChildElement("objectgroup");
        objects=objects->FirstChildElement("object");
        while(objects!=NULL)
        {//создаЄм объекты
            std::string STR=objects->Attribute("name");
            float x,y;objects->QueryFloatAttribute("x",&x);objects->QueryFloatAttribute("y",&y);
            entManage.Create(STR,x,y);objects=objects->NextSiblingElement("object");
        }
    }
    void Draw(RenderWindow& window)
    {
        for(int i=0;i<w/tw;i++)
            for(int j=0;j<h/th;j++)
            {//рисуем карту!
            if(mapMas[i][j]>0)
                {mapSprite.setTextureRect(IntRect(0,(mapMas[i][j]-1)*th,tw,th));
                mapSprite.setPosition(i*tw,j*th);window.draw(mapSprite);}
            }
    }
};
