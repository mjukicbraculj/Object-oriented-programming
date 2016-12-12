#include "tocka.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

double Tocka::udaljenost(Tocka a)
{
    return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
}
void Tocka::ispis()
{
    std::cout << x << " " << y << std::endl;
}

bool operator<(const Tocka A, const Tocka B)
{
    if(A.x<B.x || (A.x==B.x && A.y<B.y)) return true;
    return false;
}