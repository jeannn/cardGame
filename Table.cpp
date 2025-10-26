#include "Table.h"


/**
 * revient vrai lorsqu’un joueur a gagné. Le nom du joueur est 
 * retourné par référence (dans l’argument). 
 */
bool Table::win(std::string& pName){
    bool win = false;
    if(deck->size() == 0){
      
       switch (compareCoins(joueur1->getNumCoins(), joueur2->getNumCoins())) {
            case 1:
                pName = joueur1->getName();
                break;
            case -1:
                pName = joueur2->getName();
                break;
            case 0:
                pName = "Egalitee";
                break;
        }

       win = true;
    }
    return win;
}

//effectuer la comparaison des pièces des joueurs
int Table::compareCoins(int coinsJoueur1, int coinsJoueur2) {
    if (coinsJoueur1 > coinsJoueur2) {
        return 1;
    } else if (coinsJoueur1 < coinsJoueur2) {
        return -1;
    } else {
        return 0;
    }
}


/**
 *   prints the top card of the player's hand (with argument false) or all 
 *   of the player's hand (with argument true).
 */
void Table::printHand(bool in){
     Player* current = joueurActu == 0 ? joueur1 : joueur2; // get the current player
     current -> printHand(std::cout, in);
}

/**
 *  return the p1 when p_id = 0 and p2 when the p_id is something else
 */
Player* Table::getPlayer(int id){
    joueurActu = id;
    if (id==0) return joueur1;
    else return joueur2;
}


/**
 *  insertion operator to display the table information
 */
std::ostream& operator<<( std::ostream& output,  const Table&  tb){

    output << "> Joueur 1 : " << std::endl << std::endl << *(tb.joueur1) << std::endl;
    output << "> Joueur 2 : " << std::endl << std::endl << *(tb.joueur2) << std::endl;
    output << "> Defausse pile (sommet) : "  << *tb.dp << std::endl << std::endl;
    output << "> Zone de commerce : "  << *tb.tradeAr << std::endl;
    output << "_______________________" << std::endl;
    return output;
};


/**
 * 
 *  write the game into the related files
 * 
 */
void Table::saveTable(){
    
    std::ofstream file;

    file.open("Saved-Deck.txt", std::ios::trunc);
    deck->saveDeck(file);

    file.close();

    file.open("Saved-DiscardPile.txt", std::ios::trunc);
    dp->saveDiscardPile(file);
    file.close();

    file.open("Saved-TradeArea.txt", std::ios::trunc);
    tradeAr->saveTradeArea(file);
    file.close();

    joueur1->savePlayer(1);
    joueur2->savePlayer(2);

}


/**
 *  permet de recuperer l'information dans le fichier correspondant à l'id du joueur correspondant
 */
void Table::reloadPlayer(int p_id){
    std::ifstream file;
    char id[2];
    sprintf_s(id, "%d", p_id);
    std::string filename ="Saved-P"+std::string(id)+".txt";
    file.open(filename);
    if(file.is_open()){
        if(p_id == 1){
            joueur1 = new Player(file, cf);
        }else{ 
            joueur2 = new Player(file, cf);
        }
    }

    file.close();
    
}

/**
 *  permet de recuperer le deck sauvegardé dans un fichier
 * 
 * 
 */
void Table::reloadDeck(){
    std::ifstream deckFile("Saved-Deck.txt"); 
    if(deckFile.is_open()){
        deck = new Deck(deckFile,cf);
    }else{
        // file not found
        deck =  cf -> getDeck();
        std::cout << "Saved-Deck.txt introuvable. Le deck a été généré à partir de CardFactory." << std::endl;
    }
}

/**
 *  reloads the discard pile from the saved file
 * 
 */
void Table::reloadDiscardPile(){
    std::ifstream dpFile("Saved-DiscardPile.txt"); 
    if(dpFile.is_open()){
        dp = new DiscardPile(dpFile,cf);
    }else{
        // file not found
        dp =  new DiscardPile;
        std::cout << "Saved-DiscardPile.txt introuvable. Utilisation d un défausse vide." << std::endl;
    }
}


/**
 *  reloads the trade area from the saved file
 * 
 */
void Table::reloadTradeArea(){
    std::ifstream trArFile("Saved-TradeArea.txt"); 
    if(trArFile.is_open()){
        tradeAr = new TradeArea(trArFile,cf);
    }else{
        // file not found
        tradeAr =  new TradeArea;
        std::cout << "Saved-TradeArea.txt introuvable. Utilisation d une zone commerciale vide." << std::endl;
    }
}



/**
 *  returns the deck initialized in the table object
 */
Deck* Table::getDeck(){
    if(deck == nullptr){
        deck =  cf -> getDeck();
    }
    return deck;
}

/**
 * renvoie la défausse de la table
 */
DiscardPile* Table::getDiscardPile(){
    return dp;
}
/**
 * renvoie la zone de commerce de la table
 */
TradeArea* Table::getTradeArea(){
    return tradeAr;
}