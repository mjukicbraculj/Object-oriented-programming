#include <string>

bool user_continue()
{
    std::cout << "igra?(DA/NE)" << std::endl;
    std::string str;
    std::cin >> str;
    if(str=="DA") return 1;
    return 0;
}

int main(int argc, char * argv[])
{
  // ueitaj ulazno stanje iz datoteke. Datoteka je pocetno_stanje.txt
  // ili je zadana argumentom komandne linije
  std::string input_file("pocetno_stanje.txt");
  if(argc > 1)
    input_file = argv[1];

  GameOL gol;  // defaultni konstruktor

  // Inicijaliziraj Game Of Live objekt s poeetnim stanjem
  // koje je zadano u datoteci input_file
  gol.init(input_file);
  // iscrtaj poeetno stanje
  gol.print();

  while( user_continue() )
  {
    gol.update();  // prijelaz automata u novo stanje
    gol.print();
    //std::cout << "Next step ? ";
  }
  // ispiši završno stanje u datoteku
  gol.print("zavrsno_stanje.txt");

  return 0;
}