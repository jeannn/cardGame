#ifndef TRADEAREA_H
#define TRADEAREA_H

#include "Card.h"
#include <list>
#include <sstream>
#include <cstdlib>


class CardFactory;

class TradeArea{
     std::list<Card*> tradeAr; 
     const int MAX_CARDS;
     public:
        // Construct a new Trade Area object
        TradeArea():MAX_CARDS(3){};
        // Construct a new Trade Area object from an istream
        TradeArea(std::istream& input, const CardFactory* cf);
        bool legal(Card*);
        Card* trade(std::string);
        int numCards();
        friend std::ostream& operator<<( std::ostream&, const TradeArea&  );
        void saveTradeArea(std::ofstream& filename);
        std::list<Card*> getListOfCards();
        TradeArea& operator+=(Card* card);

};

#endif