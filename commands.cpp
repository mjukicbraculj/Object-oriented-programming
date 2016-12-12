#include "commands.h"
#include <iostream>


// Game konstruktor.
// Otvara ekran širine 800x600 pixela s naslovom zadatak 11.
// Zatim učitava sliku i font, te kreira dva objekta scene.
Game::Game() : mWindow(sf::VideoMode(800,600), "zadatak 11")
{
   // učitaj sliku aviona
   if (!mTexture.loadFromFile("Raptor.png"))
        throw std::runtime_error("Cannot open file Raptor.png!");

   // učitaj fontove
   if (!mFont.loadFromFile("Sansation.ttf"))
        throw std::runtime_error("Cannot open file Sansation.ttf!");

   // kreiraj dva objekta na sceni -- sliku i tekst
   // Kako su dinamički alocirani prepuštamo unique_ptr klasi brigu o
   // dealokaciji.
   mSceneGraph[0] = std::unique_ptr<SpriteNode>(new SpriteNode(mTexture));
   mSceneGraph[0]->setPosition(200,300);
   mSceneGraph[1] = std::unique_ptr<TextNode>(new TextNode(mFont));
   mSceneGraph[1]->setPosition(600,300);
   // Ove zastavise ukazuju treba li objekt rotirati (true) ili ne (false)
   mRotate[0] = false;
   mRotate[1] = false;
}

// game-loop. Ovo je glavna petlja programa.
void Game::run(){
    // beskonačna petlja koja se izvršava sve dok ne zatvorimo
    // prozor.
   while(mWindow.isOpen())
   {
     processEvents();
     update();
     render();  // iscrtavanje
   }
}

// obrada događaja
void Game::processEvents(){
    // Poništimo prethodno stanje zastavica
      //mRotate[0] = false;
      //mRotate[1] = false;
        Command C;
      // Od prozora zahtjevamo sve događaje koji su se desili
      sf::Event event;
      while(mWindow.pollEvent(event))
      {
          // event.type je tip događaja.
          // sf::Event::Closed znači prozor je zatvoren
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type == sf::Event::KeyPressed){
            // sf::Event::KeyPressed = stisnuta je tipka na tastaturi
            // event.key.code daje kod stisnute tipke.
            sf::Keyboard::Key code = event.key.code;
            // event.key.alt signalizira da li je istovremeno stisnuta tipka ALT
            bool alt = event.key.alt;
            // event.key.control signalizira da li je istovremeno stisnuta tipka CRTL
            bool ctrl = event.key.control;
            // odluka o tome što ćemo rotirati u update() metodi
            if(alt  && code == sf::Keyboard::R)  //mRotate[0] = true;  // rotiraj sliku
            {
                C.category=1;
                C.action=[](SceneNode* S){S->rotate(-10.0f);};
            }
            if(ctrl && code == sf::Keyboard::R) //mRotate[1] = true;  // rotiraj tekst
            {
                C.category=0;
                C.action=[](SceneNode* S){S->rotate(-10.0f);};
            }
            if(ctrl && code == sf::Keyboard::Up){C.category=0; C.action=[](SceneNode *S){S->move(0,-10.0f);};}
            if(ctrl && code == sf::Keyboard::Down){C.category=0; C.action=[](SceneNode *S){S->move(0,10.0f);};}
            if(ctrl && code == sf::Keyboard::Left){C.category=0; C.action=[](SceneNode *S){S->move(-10.0f,0);};}
            if(ctrl && code == sf::Keyboard::Right){C.category=0; C.action=[](SceneNode *S){S->move(10.0f,0);};}
            if(alt && code == sf::Keyboard::Up){C.category=1; C.action=[](SceneNode *S){S->move(0,-10.0f);};}
            if(alt && code == sf::Keyboard::Down){C.category=1; C.action=[](SceneNode *S){S->move(0,10.0f);};}
            if(alt && code == sf::Keyboard::Left){C.category=1; C.action=[](SceneNode *S){S->move(-10.0f,0);};}
            if(alt && code == sf::Keyboard::Right){C.category=1; C.action=[](SceneNode *S){S->move(10.0f,0);};}

            mQueue.push(C);
        }

      }
}

// update vrši rotaciju objekta u grafu scene
// (i sve druge tražene transformacije)
void Game::update(){
    while(!mQueue.empty()){
        for(unsigned int i=0; i<2; ++i)
        {
            // Konkretan posao rotacije će vršiti objekt scene.
            // Ovdje samo zovemo update() obkjekta ako je to signalizirano
            // zastavicom.
            mSceneGraph[i]->onCommand(mQueue.front());
        }
        mQueue.pop();
    }
}

// Iscrtavanje
// -- očisti prozor,
// -- iscrtaj sve objekte na sceni (to se radi u "pozadini"),
// -- prikaži novo stanje prozora
// Metodu ne mijenjati.
void Game::render()
{
    mWindow.clear();
    for(auto & node : mSceneGraph) mWindow.draw(*node);
    mWindow.display();
}
