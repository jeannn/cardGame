
#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include <typeinfo>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include "Card.h"

class CardFactory;

class Chain_Base{
    protected:
        std::vector<Card*>  chain;
        std::string chainType;

    public:
        int getSize();
        std::string getChainType();
        void setChainType(std::string type);
        void saveChain(std::ofstream& filename);
        Chain_Base& operator+=(Card* card){
            chain.push_back(card);
            return *this;
        };
        virtual ~Chain_Base() {};
        friend std::ostream& operator<<( std::ostream &output, const Chain_Base & d );
};


template <typename T = Card> 
class Chain : public virtual Chain_Base{
    public:
        // Constructeur pour chaine
        Chain(){ 
            chainType = typeid(T).name();
            if(std::isdigit(chainType.at(0)) ){
                chainType =  chainType.substr(1,chainType.size()); // remove the first unexpected digit in the type name
            }
        };

        // Constructeur Chain à partir d'un fichier
      Chain(std::istream& input, const CardFactory* cf) {
        std::string ligne;
        Card* card = nullptr;
        int count = 0;
        while (std::getline(input, ligne)) {
            std::istringstream est(ligne);
            std::string data;
            if (!(est >> data)) {
                continue;
            }
            count++;

            switch (data[0]) {
                case 'B':
                    card = new Blue;
                    break;
                case 'C':
                    card = new Chili;
                    break;
                case 'S':
                    card = new Stink;
                    break;
                case 'G':
                    card = new Green;
                    break;
                case 's':
                    card = new soy;
                    break;
                case 'b':
                    card = new black;
                    break;
                case 'R':
                    card = new Red;
                    break;
                case 'g':
                    card = new garden;
                    break;
                default:
                    std::cout << "(Chain Constructor) Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << data << std::endl;
                    exit(1);
            }

            if (card != nullptr) {
                (*this) += card;
            }
        }

        std::cout << "Chain avec " << count << " cards initialisé depuis fichier avec succès." << std::endl;
    };

        // Definition de l'operateur += pour Chain
        Chain<T>& operator+=(Card* card){
            if(getSize() == 0)
               chainType = typeid(card).name();//mise a jour du Type de la chain
            if(typeid(T) == typeid(card) ){
                chain.push_back(card);
                return *this;
            } 
            else throw std::runtime_error("IllegalType");
        };

        /*compte les cartes numériques dans la chaîne actuelle et renvoie les pièces numériques 
        selon la fonction Card ::getCardsPerCoin*/

        int sell() {
            T element; // Initialise une carte pour accéder à la méthode getCardsPerCoin
            int value = 0;
            int max_coins = 4;
            if (chain.size() > 0) {
                // Regarde la valeur de la pièce
                for (int coin = 1; coin <= max_coins; coin++) {
                    if (chain.size() == element.getCardsPerCoin(coin)) {
                        value = coin;
                        break;
                    } else if (chain.size() < element.getCardsPerCoin(coin)) {
                        value = coin - 1; // Obtient la plus petite valeur de pièce
                        break;
                    }
                }
            }
            if (value == -1) {
                value = 0; // La remet à 0
            }
            return value;
        }

    friend std::ostream& operator<<( std::ostream &output, const Chain<Card*> & d );
};

#endif