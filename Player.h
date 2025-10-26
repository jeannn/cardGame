#ifndef PLAYER_H
#define PLAYER_H


#include <cstdlib>
#include <vector>
#include "Hand.h"
#include "Chain.h"


class Player{
    std::string joueurNom; // player name
    Hand* joueurMain; // player hand
    std::vector<Chain_Base*> joueurChains; // player chains
    int pCoins;  // number of coins held by the player
    const int num_max_chain;
    const int chain_approuvee;
    public:
        /**
         *  Construct a new Player object
         */
        Player(std::string& name): num_max_chain(3), chain_approuvee(2){
            joueurNom = name;
            pCoins = 0;
            joueurMain = new Hand();
        };
        
        Player(std::istream& input, const CardFactory* cf);
        
        /**
         * Destroy the Player object
         * 
         */
        ~Player(){
            delete joueurMain;
        };

        Player& operator+=(int coins);

        /**
         *  retourne la chaine à l'index i correspondant
         */
        Chain_Base& operator[](int i){
            return *(joueurChains.at(i));
        };

        void takeCard(Card*); 
        Card* playCard(Card* input = nullptr, bool specified_input = false);     
        Card* removeCard(int = 0); 
        std::string getName();
        int getNumCoins();
        int getMaxNumChains();
        int getNumChains();
        int getNumCards();
        Hand* getHand();
        std::vector<Chain_Base*>* getChains();
        void buyThirdChain();
        void printHand(std::ostream& output, bool in);
        friend std::ostream& operator<<(std::ostream&,  const Player& );
        void savePlayer(int p_id);
        void checkEndedChains();  
};
#endif