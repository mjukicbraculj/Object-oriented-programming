#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
GameOL::GameOL() {}
GameOL::~GameOL() {}

bool GameOL::postoji(int i, int j) const
{
    if(i>=0 && i<r && j>=0 && j<s) return 1;
    return 0;
}

int GameOL::broj_susjeda(int i, int j) const
{
    int g1=0,g2=0,g3=0,d1=0,d2=0,d3=0,l=0,d=0;

    if(postoji(i-1,j-1))g1=mapa[(i-1)*s+j-1];
    if(postoji(i-1,j)) g2=mapa[(i-1)*s+j];
    if(postoji(i-1,j+1)) g3=mapa[(i-1)*s+j+1];
    if(postoji(i,j-1)) l=mapa[i*s+j-1];
    if(postoji(i,j+1)) d=mapa[i*s+j+1];
    if(postoji(i+1,j-1)) d1=mapa[(i+1)*s+j-1];
    if(postoji(i+1,j)) d2=mapa[(i+1)*s+j];
    if(postoji(i+1,j+1)) d3=mapa[(i+1)*s+j+1];

    return g1+g2+g3+l+d+d1+d2+d3;
}
void GameOL::update()
{
    std::vector<int> novi(r*s);
    novi=mapa;
    for(int i=0;i<r; i++)
    {
        for(int j=0; j<s; j++)
        {
            int susjedi=broj_susjeda(i,j);
            //std::cout << susjedi << " ";
            if(susjedi>=4 || susjedi<=1)novi[i*s+j]=0;
            else if(mapa[i*s+j]==1 && (susjedi==2 || susjedi==3)) novi[i*s+j]=1;
            else if(mapa[i*s+j]==0 && susjedi==3) novi[i*s+j]=1;
            else continue;
        }
    }
    mapa=novi;
}

void GameOL::print() const
{
    for(int i=0;i<r;i++)
    {
       for(int j=0; j<s; j++)
       {
        if(mapa[i*s+j]==1) std::cout << "*";
        else std::cout << " ";
       }
       std::cout << std::endl;
    }
}

void GameOL::init(std::string const & file_name)
{
    std::ifstream f;
    f.open(file_name.c_str());
    if(!f)
    {
        throw std::runtime_error("greska");
    }
    std::string str;
    f >> r >> s;
    int i=0;
    mapa.resize(r*s,0);
    std::getline(f, str);   //da dovrsimo prvu liniju
    //std::cout << r << " " << s << std::endl;
    while(std::getline(f,str))
    {
        if(i>=r*s)break; //ako bi datoteka imala vise redaka nego je predvidjeno
        for(int j=0;(j< int(str.size()) && j<s); j++)
        {
            if(str[j]=='*') mapa[i+j]=1;
        }
        i+=s;
        str.clear();
    }
}

void GameOL::print(std::string const &filename) const
{
    std::ofstream o;
    o.open(filename.c_str());
    o << r << " " << s << std::endl;
    for (int i=0; i<r; i++)
    {
        for(int j=0; j<s; j++)
        {
            if(mapa[i*s+j]==1) o << "*";
            else o << " ";
        }
        o << std::endl;
    }
}

