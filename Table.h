#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include  "CardFactory.h"

class Table{
    Player* joueur1;
    Player* joueur2;
    int joueurActu; // id of the current player
    DiscardPile* dp;
    TradeArea* tradeAr;
    Deck* deck;
    CardFactory* cf;
    
    public:
        /**
         *  Construct a new Table object
         */
        Table(Player& j_un, Player& j_deux, DiscardPile& dis_pile, TradeArea& tr_arr, Deck& dck, CardFactory& cfactory){
            joueur1 = &j_un;
            joueur2 = &j_deux;
            dp = &dis_pile;
            tradeAr = &tr_arr;
            deck = &dck;
            cf = &cfactory;
        }

        /**
         *  Destroy the Table object
         * 
         */
        ~Table(){
            delete joueur1;
            delete joueur2;
            delete dp;
            delete tradeAr;
            delete deck;
            delete cf;
        }
        bool win(std::string&);
        void printHand(bool);
        friend std::ostream& operator<<(std::ostream&,  const Table&);
        void saveTable();
        void reloadPlayer(int);
        void reloadDeck();
        void reloadDiscardPile();
        void reloadTradeArea();
        Deck* getDeck();
        Player* getPlayer(int);
        DiscardPile* getDiscardPile();
        TradeArea* getTradeArea();
        int compareCoins(int coinsJoueur1, int coinsJoueur2);

};

#endif