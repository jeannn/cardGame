#include <iostream>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "Card.h"
#include "Deck.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Chain.h"
#include "Player.h"
#include "Table.h"
#include "TradeArea.h"
#include <fstream>
#include <sstream>


using namespace std;


int main(){

    std::string joueur1_nom;
    std::string joueur2_nom;
    std::string vainceur_nom;

    // initialisation
    const int numero_joueur_max = 2;
    Player* joueur1 = nullptr;
    Player* joueur2 = nullptr;

    // tableau de joueurs
    Player** pArr =  new Player*[numero_joueur_max];
    DiscardPile* discardP = new DiscardPile;
    CardFactory* cardFact = CardFactory::getFactory();
    Deck* deck =  nullptr;
    TradeArea* tradeAr = new TradeArea;
    Table* tableau = new Table(*joueur1, *joueur2, *discardP, *tradeAr, *deck, *cardFact);

    char entree_utilisateur[2];
    bool partieEnregistree;

    // charger la partie depuis un fichier sauvegardé ici
    std::cout << "Voulez-vous recharger une partie ? (o/n)" << std::endl;
    std::cin >> entree_utilisateur;

    // rechercher le fichier ; sinon, continuer
    switch(entree_utilisateur[0]){
    case 'o':
        // recharger le deck
        tableau->reloadDeck();
        deck = tableau->getDeck();

        tableau->reloadPlayer(1); // obtenir le joueur 1
        tableau->reloadPlayer(2); // obtenir le joueur 2

        joueur1 = tableau->getPlayer(1);
        joueur2 = tableau->getPlayer(2);

        tableau->reloadDiscardPile();   // recharger la pile de défausse
        discardP = tableau->getDiscardPile(); // obtenir la pile de défausse

        tableau->reloadTradeArea();
        tradeAr = tableau->getTradeArea(); // obtenir la zone de commerce
        break;

    default:
        std::cout << std::endl;
        std::cout << "Entrez le nom du premier joueur : ";
        std::cin  >> joueur1_nom;
        std::cout << std::endl;
        std::cout << "Entrez le nom du deuxième joueur : ";
        std::cin  >> joueur2_nom;
        std::cout << std::endl;

        joueur1 = new Player(joueur1_nom);
        joueur2 = new Player(joueur2_nom);

        pArr[0] = joueur1;
        pArr[1] = joueur2;

        tableau = new Table(*joueur1,*joueur2,*discardP, *tradeAr, *deck, *cardFact);

        deck = tableau->getDeck();        // obtenir le deck
        discardP   = tableau->getDiscardPile(); // obtenir la pile de défausse
        tradeAr = tableau->getTradeArea();   // obtenir la zone de commerce

        std::cout << "Initialisation de chaque joueur avec 5 cartes. " << std::endl;
        std::cout << "Taille actuelle du deck : " << deck->size() << std::endl;

        // initialiser 5 cartes à la main de chaque joueur
        int player = 0;
        while(player < numero_joueur_max){
            int card = 0;
            while(card < 5){
                pArr[player]->takeCard(deck->draw());
                card++;
            }
            player++;
        }
        break;
}

    while(deck->size() != 0){
    std::cout << "nombre de cartes restant dans le deck : " << deck->size() << std::endl;
    std::cout << std::endl << ">>>>>>>>>>> veux tu enregistrer la partie ? (o/n)" << std::endl;
    std::cin >> entree_utilisateur;
    switch(entree_utilisateur[0]){
        case 'y':
            // proceed with the logic for pausing the game
            tableau->saveTable();
            std::cout << "partie enregistree. aurevoir." << std::endl;
            return 0; // exit the function or break the loop, depending on your structure
        default:
            // proceed with the game
            int i = 0;
            while(i < numero_joueur_max){
                // display table
                std::cout << std::endl <<  ">>>> Information sur la Table : <<<<" << std::endl << std::endl << *tableau << std::endl;

                // proceed with the logic
                std::cout << std::endl;
                std::cout << ">>>> Tour du Joueur " << i+1 << ". " << std::endl;
                std::cout << std::endl;

                Player* p = tableau->getPlayer(i);  // obtenir le joueur actuel

                std::cout <<  "> Piocher la carte du dessus du deck..." << std::endl;
                //  Le joueur pioche la carte du dessus du Deck
                p->takeCard(deck->draw());

                std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                p->printHand(std::cout, true);
                std::cout << std::endl;

                // Ajouter des cartes à chaîner depuis la TradeArea ou les défausser
                if(tradeAr->numCards() > 0) {
                    bool carteAjoutee = false;
                    // Ajouter des cartes à chaîner depuis la TradeArea ou les défausser
                    for(Card* card : tradeAr->getListOfCards()){
                        for(Chain_Base* chain : *(p->getChains())){
                            if(card->getName() == chain->getChainType()){
                                *chain += tradeAr->trade(card->getName());
                                carteAjoutee = true;
                            }
                        }

                        // défausser la carte dans la pile de défausse si la carte n'a pas été ajoutée
                        if(!carteAjoutee){
                            std::cout << "> Carte : " ;
                            card->print(std::cout);
                            std::cout << " ajoutee a la pile de défausse " << std::endl;
                            *discardP+=tradeAr->trade(card->getName());
                        }
                    }
                }

                std::cout << std::endl << "> Jouer la carte du dessus de la Main (" << p->getHand()->top()->getName()[0] <<")" << std::endl;
                // Jouer la carte du dessus de la Main.
                // Si la chaîne est terminée, les cartes de la chaîne sont retirées et le joueur reçoit des pièces.
                p->playCard();

                std::cout << std::endl <<  *p << std::endl;
                std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                p->printHand(std::cout, true);
                std::cout << std::endl;
                std::cout << std::endl << "> Jouer la carte du dessus ? (o) ou Defausser la carte dans la Pile de Defausse ? (n) " << std::endl;
                std::cin >> entree_utilisateur;

                switch(entree_utilisateur[0]){
                    case 'o':
                        std::cout <<  "> Jouer la carte du dessus de la Main (" << p->getHand()->top()->getName()[0] <<")" << std::endl;
                        // Jouer maintenant la carte du dessus de la Main.
                        // Si la chaîne est terminée, les cartes de la chaîne sont retirées et le joueur reçoit des pièces.
                        p -> playCard();

                        std::cout << std::endl <<  *p << std::endl;

                        std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                        p->printHand(std::cout, true);
                        std::cout << std::endl;
                        break;

                    default:
                        int idx;
                        Card* card = nullptr;
                        // Afficher la main complète du joueur et le joueur sélectionne une carte arbitraire
                        std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                        p->printHand(std::cout, true);

                        // p->printHand(std::cout, false);
                        std::cout << "Taille actuelle de la main : " << p->getNumCards() << std::endl;
                        std::cout << "Entrez l'indice de la carte que vous souhaitez supprimer : " << std::endl;
                        std::cin  >> idx;

                        // Défausser la carte arbitraire de la main du joueur et la placer dans la pile de défausse.
                        card = p->removeCard(idx);
                        if(card == nullptr)
                            std::cout << "La carte n'a pas pu etre supprimee. Veuillez vérifier l'indice saisi : " << idx << std::endl;

                        // entrer le bon indice
                        while(card == nullptr){
                            std::cout << "Taille actuelle de la main : " << p->getNumCards() << std::endl;
                            std::cout << "Entrez l'indice de la carte que vous souhaitez supprimer : " << std::endl;
                            std::cin  >> idx;
                            // Défausser la carte arbitraire de la main du joueur et la placer dans la pile de défausse.
                            card = p->removeCard(idx);
                        }

                        // ajouter la carte à la pile de défausse
                        std::cout << "> Carte : " ;
                        card->print(std::cout);
                        std::cout << " ajoutee a la pile de défausse " << std::endl;
                        *discardP+= card;
                        break;
                }

                // Tirer trois cartes du deck et placer les cartes dans la zone de commerce
                std::cout << std::endl << ">>>> Piocher trois cartes du deck vers la zone de commerce. " << std::endl << std::endl;
                int draw = 0;
                while (draw < 3) {
                    *tradeAr += (deck->draw());
                    draw++;
                }
                std::cout << "> Zone de Commerce : " << *tradeAr << std::endl;

                // tant que la carte du dessus de la pile de défausse correspond à une carte existante dans la zone de commerce
                if(discardP->size() > 0){
                    while( tradeAr->legal(discardP-> top())){
                        *tradeAr += (discardP->pickUp());
                    }
                }
                std::cout << std::endl;

                for(Card* card : tradeAr->getListOfCards()){
                    std::cout << std::endl << "> Voulez-vous enchainer la carte [";
                    card -> print(std::cout);
                    std::cout << "] ? (o/n) " << std::endl;
                    std::cin >> entree_utilisateur;
                    switch(entree_utilisateur[0]){
                        case 'o':
                            // enchaîner la carte.
                            p -> playCard(tradeAr -> trade(card->getName()),  true);
                            std::cout << std::endl <<  *p << std::endl;
                            std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                            p->printHand(std::cout, true);
                            std::cout << std::endl;
                            break;
                        default:
                            std::cout << std::endl << "> carte laissee dans la zone de commerce." << std::endl;
                            break;
                    }
                }
                // Tirer deux cartes du Deck et ajouter les cartes à la main du joueur (à l'arrière).
                for(int j = 0; j < 2; j++){
                    if(deck->size() > 0 )
                        p -> takeCard(deck->draw());
                }
                std::cout << std::endl << "> Main du Joueur " << i+1 << " : " << std::endl;
                p->printHand(std::cout, true);
                std::cout << std::endl;
                std::cout << std::endl << "> Pile de Defausse toutes les cartes : " ;
                discardP->print(std::cout);
                std::cout << std::endl;
                i++;
            }
            break;
    }
} // fin de la boucle while avec le deck


    if(deck->size() == 0){
       // afficher la table
       std::cout << std::endl <<  ">>>> Information sur la Table : <<<<" << std::endl << std::endl << *tableau << std::endl;
       std::cout << "> Aucune carte restante dans le deck. Taille du deck = " << deck->size() << std::endl;
       tableau->win(vainceur_nom);
       std::cout << std::endl << "> Le gagnant est : " << vainceur_nom << std::endl;
    }
    
    return 0;
};


