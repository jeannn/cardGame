#include "CardFactory.h"

CardFactory* CardFactory::instance = 0; // initialize l'instance a 0

// creer une instance de CardFactory
CardFactory* CardFactory::getFactory(){
      if(!instance)
        instance = new CardFactory;
     return instance;
}

// retourne le deck du jeu melangé
Deck* CardFactory::getDeck(){
    unsigned seed = 0;
    std::shuffle(deck->begin(), deck->end(), std::default_random_engine(seed)); // Melange les cartes 
    return deck;
}

// Construit un object Cardfactory avec les 104 Cartes
CardFactory::CardFactory(){
    deck =  new Deck(); // initialise le deck

    // ajoute 20 Cartes Blue
    int i= 20; 
    while(i >  0){
        Blue* bleu = new Blue;
        deck ->push_back(bleu);i--;
    }

    // ajoute 18 Cartes Chili
    i=18;
    while(i > 0){
        Chili* chili = new Chili;
        deck -> push_back(chili);i--;
    }

    // ajoute 16 Cartes Stink 
    i=16;
    while(i >0){
        Stink* stink = new Stink;
        deck -> push_back(stink);i--;
    }

    // ajoute 14 Cartes Green 
    i=14;
    while(i > 0){
        Green* green = new Green;
        deck -> push_back(green);i--;
    }

    // ajoute 12 Cartes soy 
    i=12;
    while(i >0){
        soy* soyy = new soy;
        deck -> push_back(soyy);i--;
    }

    // ajoute 10 Cartes black
    i=10; 
    while(i > 0){
        black* noir = new black;
        deck -> push_back(noir);i--;
    }

    // ajoute 8 Cartes Red 
    i=8; 
    while( i > 0){
        Red* rouge = new Red;
        deck -> push_back(rouge);i--;
    }

    // ajoute 6 Cartes garden
    i=6;
    while( i > 0){
        garden* jardin = new garden;
        deck -> push_back(jardin);i--;
    }
}