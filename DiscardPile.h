

#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include "Card.h"
class CardFactory;

class DiscardPile:  
    public std::vector<Card*>{
    public:
        DiscardPile(): std::vector<Card*>(){};
        DiscardPile(std::istream& input, const CardFactory* cf);
        DiscardPile& operator+=(Card* c);
        Card* pickUp();
        Card* top();
        void print(std::ostream&);
        friend std::ostream& operator<<( std::ostream &output, const DiscardPile& dp );
        void saveDiscardPile(std::ofstream& filename);
};

#endif