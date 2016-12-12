#ifndef  _TOCKA_H_IS_INCLUDED_
#define  _TOCKA_H_IS_INCLUDED_

class Tocka
{
    private:
    double x, y;
    public:
    Tocka() {}
    Tocka(int i, int j){x=i; y=j;}
    void ispis();
    double udaljenost(Tocka T);
    friend bool operator<(const Tocka T1,const Tocka T2);
    ~Tocka(){}
};

#endif