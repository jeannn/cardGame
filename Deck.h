
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#ifndef DECK_H
#define DECK_H
#include "Card.h"

class CardFactory;

class Deck: public std::vector<Card*>{
     public :
        // Constructeur de Deck
        Deck(): std::vector<Card*>(){};

        // Constructeur de Deck à partir d'un fichier
        Deck(std::istream& input, const CardFactory* cf);

        // Constructeur de recopie
        Deck(const Deck& d);

        // Destructeur
        ~Deck();

        Card* draw();
        Deck& operator=(const Deck&);
        friend std::ostream& operator<<( std::ostream &output, const Deck& d );
        void saveDeck(std::ofstream& filename);
};

#endif