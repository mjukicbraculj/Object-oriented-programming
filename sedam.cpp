/*Umjesto više funkcija napravite jednu klasu koja će dati istu funkcionalnost. Što će ući u javno sučelje, a što
u privatni dio klase?

    Kako osigurati da je objekt u konzistentnom stanju pri pozivu metode podudaranje()?
    Koje je javne metode bilo prirodno dodati klasi?
*/

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <functional>
#include <exception>
#include <stdexcept>
class rijeci
{
    private:
    std::set<std::string> skup;
    void separator(std::string const &text);
    public:
    rijeci(){}
    void ucitavanje(std::string ime);
    void ispis();
    int velicina();
    double operator+ (rijeci const &a) const;  //const za konzistentnost
    void operator=(rijeci const &a);
    bool element(std::string a);
    void dodaj(std::string const s);
    void izbrisi(std::string const s);
    ~rijeci(){}
};

void rijeci::separator(std::string const &text)
{
    int i=-1, j=0;
    std::string kopija;
    for (int i=0; i<=text.size(); i++)
    {
        if(ispunct(text[i])||text[i]==' '|| text[i]=='\n'||i==text.size())
        {
            if(kopija!="")skup.insert(kopija);
            kopija.clear();
        }
        else kopija+=text[i];
    }
}
void rijeci::ucitavanje(std::string ime)
{
    std::ifstream f;
    f.open(ime.c_str());
    if(!f)
    {
        throw std::runtime_error("greska");
    }
    std::string str;
    std::string text1;
    while(std::getline(f, str))
    {
        text1+=str+" ";
        str.clear();
    }
    separator(text1);
}

void rijeci::ispis()
{
    std::for_each(skup.begin(), skup.end(), [](std::string s){std::cout << s << std::endl;});
}

int rijeci::velicina()
{
    return skup.size();
}

double rijeci::operator+ (rijeci const &a) const
{
    rijeci c;
    std::set_intersection (skup.begin(), skup.end(), a.skup.begin(), a.skup.end(), inserter(c.skup, c.skup.end()));
    std::cout << "presjek ima " << c.velicina() << " rijeci" << std::endl;

    double x;
    x=c.skup.size()/(sqrt(skup.size())*sqrt(a.skup.size()));
    return x;

}
void rijeci::operator=(rijeci const &a)
{
    std::set<std::string>::iterator it;
    for (it=a.skup.begin();it!=a.skup.end();it++)
        skup.insert(*it);
}

bool rijeci::element(std::string a)
{
    if(skup.find(a)!=skup.end())return 1;
    return 0;
}

void rijeci::dodaj (std::string const s)
{
    rijeci novi;
    novi.separator(s);
    std::set<std::string>::iterator it;
    for (it=novi.skup.begin();it!=novi.skup.end();it++)
        skup.insert(*it);
}

void rijeci::izbrisi(std::string const s)
{
    rijeci novi;
    novi.separator(s);
    std::set<std::string>::iterator it;
    for (it=novi.skup.begin();it!=novi.skup.end();it++)
            skup.erase(*it);

}


int main ()
{
    rijeci a, b;
    std::string ime1, ime2;
    std::cout << "upisite ime datoteke" <<std::endl;
    std::cin >> ime1;
    a.ucitavanje(ime1);
    a.ispis();
    std::cout << a.velicina() <<std::endl;
    std::cout << "upisite ime datoteke" <<std::endl;
    std::cin >> ime2;
    b.ucitavanje(ime2);
    b.ispis();
    std::cout << b.velicina() <<std::endl;
    double x=a+b;
    std::cout << x << std::endl;
    rijeci const d=a;
    double y=d+b;
    std::cout << y << std::endl;
    if(a.element(std::string("nesto")))
            std::cout<< "rijec nesto se nalazi u a" << std::endl;
    a.dodaj("jos rijeci u a");
    a.ispis();
    std::cout << a.velicina()<< std::endl;
    a.izbrisi("jos");
    a.ispis();
    std::cout << a.velicina()<< std::endl;
    return 0;
}





