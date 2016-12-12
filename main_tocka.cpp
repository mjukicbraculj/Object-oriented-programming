#include "tocka.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>



void bez_rek(std::vector<Tocka> polje)
{
    double min1=-1, udalj;
    do
    {
        udalj=0;
        for(unsigned int i=0;i<polje.size()-1;i++)
            udalj+=polje[i].udaljenost(polje[i+1]);
        if(min1==-1) min1=udalj;
        else if(min1>udalj)min1=udalj;
    }while(std::next_permutation(polje.begin(), polje.end()));
    std::cout << "najkraci put nerekurzivno " << min1 << std::endl;
}

// rekurzija sada vraca najkraci put
std::vector<Tocka> rek(Tocka poc, std::set<Tocka> skup, double put, double *mini, std::vector<Tocka> koraci)   //sada rek pamti cijelu stazu
{
    std::vector<Tocka> novi, najmanji;
    //izbacimo poc iz skupa
    skup.erase(poc);
    koraci.push_back(poc);
    if(skup.size()==0)
    {
        if(*mini==-1)
        {
            *mini=put;
            return koraci;
        }
        else if(*mini>put)
        {
            *mini=put;
            return koraci;
        }
    }
    std::set<Tocka>::iterator it;
    for(it=skup.begin();it!=skup.end();it++)
    {
        novi=rek(*it, skup, put+poc.udaljenost(*it), mini, koraci);
        if(novi.size()!=0)najmanji=novi;
    }
    return najmanji;

}
int main()
{
    int x,y, n;
    std::cout << "ucitajte broj tocaka" <<std::endl;
    std::cin>> n;
    std::vector<Tocka> polje, najkraci_koraci, koraci, tmp;
    std::set<Tocka> skup;
    double mini=-1;
    for(int i=0;i<n;i++)
    {
        std::cin >> x >> y;
        Tocka T(x,y);
        polje.push_back(T);
        skup.insert(T);
    }
    std::set<Tocka>::iterator it;
    for(it=skup.begin();it!=skup.end();it++)
        {
            tmp=rek(*it, skup, 0, &mini, koraci);
            if(tmp.size()!=0)najkraci_koraci=tmp;
        }

    std::cout << "u rekurziji najkraci put je: " << mini << std::endl;
    std::cout << "tocke obilazimo u sljedecem redoslijedu: " <<std::endl;
    std::vector<Tocka>::iterator is;
    for(is=najkraci_koraci.begin();is!=najkraci_koraci.end();is++) (*is).ispis();

    std::sort(polje.begin(),polje.end());

    bez_rek(polje);
}
