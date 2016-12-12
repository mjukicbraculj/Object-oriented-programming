#ifndef PORUKA_H_INCLUDED
#define PORUKA_H_INCLUDED

#include <string>
#include <set>

class Poruka;

class Kategorija{
public:
    // pri konstrukciji je obavezan opis kategorije
    explicit Kategorija(std::string const & opis);
    // kontrola kopiranja
    Kategorija(Kategorija const&) = delete;
    Kategorija(Kategorija &&) = delete;
    Kategorija& operator=(Kategorija const &) = delete;
    Kategorija& operator=(Kategorija &&) = delete;
    ~Kategorija();

    // dodaj poruku u kategoriju
    void dodaj_poruku(Poruka * p);
    // ukloni poruku iz kategorije
    void ukloni_poruku(Poruka * p);
    // vrati opis kategorije
    std::string opis() const { return mopis; }
private:
    // pokazivači na poruke u kategoriji
    std::set<Poruka*> mporuke;
    // opis kategorije
    std::string mopis;
};

class Poruka{
    friend class Kategorija;
  public:
    // pri konstrukciji poruke obavezano je dati sadržaj poruke
      explicit Poruka(std::string const & sadrzaj = "");
      // Kontrola kopiranja
      Poruka(Poruka const & p);
      Poruka(Poruka && p);
      Poruka& operator=(Poruka const& p);
      Poruka& operator=(Poruka&& p);
      ~Poruka();
      // dodaj poruku u kategoriju
      void dodaj(Kategorija& k);
      // ukloni poruku iz kategorije
      void ukloni(Kategorija& k);
      // vrati poruku
      std::string sadrzaj() const { return msadrzaj; }
      // vrati sve kategorije u kojima je poruka (odvojene bjelinom, kao jedan string)
      std::string kategorije() const;
  private:
    std::string msadrzaj;
    std::set<Kategorija*> mkategorije;
};

#endif // PORUKA_H_INCLUDED
