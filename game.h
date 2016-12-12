#ifndef __GAME_OF_LIFE_H_INCLUDED__
#define __GAME_OF_LIFE_H_INCLUDED__

#include <vector>
#include <string>


class GameOL{
  public:
    GameOL();
    ~GameOL();
    void init(std::string const & file_name);
    void print() const;
    void print(std::string const &  file_name) const;
    void update();
  private:
    // broj  ivih susjeda danog elementa (i,j)
    int  broj_susjeda(int i, int j) const;
    bool postoji(int i, int j) const;
    std::vector<int> mapa;
    int r,s;
};
#endif