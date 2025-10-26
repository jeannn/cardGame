#ifndef HAND_H
#define HAND_H

#include "Card.h"

#include <queue>
#include <list>
#include <sstream>
#include <cstdlib>

class CardFactory;

class Hand{

        std::queue <Card*, std::list<Card*>> hand; 

    public:
        Hand(){};
        Hand(std::istream& input, const CardFactory* cf);
        Hand& operator+=(Card* card);
        Card* play();
        Card* top();
        Card* getCard(int pos);
        std::queue <Card*, std::list<Card*>>* getListOfCards();
        Card* operator[](int pos);
        int numCards();
        friend std::ostream& operator<<( std::ostream&,  Hand& );
        void saveHand(std::ofstream& filename);
        Card* createCardFromData(const std::string& data, const CardFactory* cf);
        void saveCardsToFile(std::ofstream& filename);
        void restoreCardsFromTemp(std::queue<Card*, std::list<Card*>>& temp);
        Card* getCardAtIndex(int pos);



};

#endif 