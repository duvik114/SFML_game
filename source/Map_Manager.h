#include <SFML/Graphics.hpp>
#include "Entity_Manager.h"
#include "tinyxml.h"

using namespace sf;

class MapManager
{//�������� �����
private:
    //std::map<int,Texture> TextureMap;
    Texture mapTexture;
    Sprite mapSprite;
    int mapMas[36][16];//������ � ������� ��������
public:
    float w,h,tw,th;//����� ������ ����� � ��������
    MapManager(std::string mapStr,EntityManager& entManage)
    {
        mapStr="maps/mapSets/"+mapStr+".tmx";
        //const char levelStr=mapStr.c_str();
        //�������������� � const char
        TiXmlDocument *lXmlDoc=new TiXmlDocument("maps/mapSets/map1.tmx");
        mapTexture.loadFromFile("maps/tileSets/tile.png");mapSprite.setTexture(mapTexture);//����� ��������� �� ������ ������ ���������!!!!
        if(!lXmlDoc->LoadFile()) {std::cout<<"ERROR";}
        TiXmlElement *tiles=lXmlDoc->FirstChildElement("map");
        tiles->QueryFloatAttribute("width",&w);tiles->QueryFloatAttribute("tilewidth",&tw);w*=tw;
        tiles->QueryFloatAttribute("height",&h);tiles->QueryFloatAttribute("tileheight",&th);h*=th;
        tiles=tiles->FirstChildElement("layer");
        tiles=tiles->FirstChildElement("data");
        tiles=tiles->FirstChildElement("tile");
        for(int i=0;i<w/tw;i++)
            for(int j=0;j<h/th;j++)
            {//��������� ������ � ������ �������� �����
            if(tiles!=NULL)
                {int k;tiles->QueryIntAttribute("gid",&k);mapMas[i][j]=k;
                tiles=tiles->NextSiblingElement("tile");}
            }
        TiXmlElement *objects=lXmlDoc->FirstChildElement("map");
        objects=objects->FirstChildElement("objectgroup");
        objects=objects->FirstChildElement("object");
        while(objects!=NULL)
        {//������ �������
            std::string STR=objects->Attribute("name");
            float x,y;objects->QueryFloatAttribute("x",&x);objects->QueryFloatAttribute("y",&y);
            entManage.Create(STR,x,y);objects=objects->NextSiblingElement("object");
        }
    }
    void Draw(RenderWindow& window)
    {
        for(int i=0;i<w/tw;i++)
            for(int j=0;j<h/th;j++)
            {//������ �����!
            if(mapMas[i][j]>0)
                {mapSprite.setTextureRect(IntRect(0,(mapMas[i][j]-1)*th,tw,th));
                mapSprite.setPosition(i*tw,j*th);window.draw(mapSprite);}
            }
    }
};
