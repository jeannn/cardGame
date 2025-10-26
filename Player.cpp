#include "Player.h"
#include <string>
#include <iomanip>
#include <stdexcept>

/**
 * Obtenir l’objet Name
 */
std::string Player::getName(){
    return this->joueurNom;
}

/**
 * obtenir le nombre de cartes insidde la main du joueur
 */
int Player::getNumCards(){
    return joueurMain->numCards();
}

/**
*  prints the top card of the player's hand or all of the player's hand 
*/
    void Player::printHand(std::ostream& output, bool in){
        if(!in){
            output << joueurMain->top()->getName()[0] << std::endl;
        }else{
            for(int i = 0; i < joueurMain->numCards(); i++){
                output << joueurMain->getCard(i)->getName()[0] << " ";
            }
             output << std::endl;
        }
    }

//permet d'augmenter le nombre de point du joueur
Player& Player::operator+=(int coins){
            pCoins += coins;
            return *this;
        };


/**
 * crée la chaîne lorsque la carte est jouée et renvoie cette carte 
 */
Card* Player::playCard(Card* input, bool specified_input){
    Card* card = nullptr;
    if (joueurMain->numCards() < 0)
        std::cout << "(PlayCard) Pas assez de carte en main pour le joueur : " << joueurNom << std::endl;
    else{

        if(!specified_input)
            card = joueurMain->top();
        else
            card = input;
            Chain_Base* new_chain;
            bool ExistingChain = false;
            char user_input[2];

        // vérifier si la chaîne n’est pas déjà dans la main du joueur
        for(Chain_Base* chain: joueurChains){ 
            if(chain->getChainType() == card -> getName()){
                ExistingChain = true;
                new_chain = chain;
                if(!specified_input)
                   card = joueurMain -> play();
                if(card == nullptr)  // pour éviter un comportement inattendu, prenez une carte de la main
                   card = joueurMain -> play();
                *new_chain += card;
                break;
            }
        }

      
        // si la chaîne n’a pas été trouvée, créez-en une nouvelle
        if(!ExistingChain){

            Chain_Base* new_chain = nullptr;
            switch (card->getName()[0]) {
                case 'B':
                    new_chain = new Chain<Blue>;
                    break;
                case 'C':
                    new_chain = new Chain<Chili>;
                    break;
                case 'S':
                    new_chain = new Chain<Stink>;
                    break;
                case 'G':
                    new_chain = new Chain<Green>;
                    break;
                case 's':
                    new_chain = new Chain<soy>;
                    break;
                case 'b':
                    new_chain = new Chain<black>;
                    break;
                case 'R':
                    new_chain = new Chain<Red>;
                    break;
                case 'g':
                    new_chain = new Chain<garden>;
                    break;
                default:
                    std::cout << "(playCard) Verifiez le nom de la carte. Valeur reçue : " << card->getName() << std::endl;
                    exit(1);
                }
            
            if(joueurChains.size() == num_max_chain){

              std::cout << "Joueur " <<joueurNom << " a atteint la valeur maximale de la chaine ("<<num_max_chain<<")." << std::endl;
              std::cout << "> Chaîne de vente de type : " << joueurChains.front()->getChainType() << std::endl;

              switch (joueurChains.front()->getChainType()[0]) {
                case 'B':
                    {
                        Chain<Blue>* chain = dynamic_cast<Chain<Blue>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pieces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'C':
                    {
                        Chain<Chili>* chain = dynamic_cast<Chain<Chili>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'S':
                    {
                        Chain<Stink>* chain = dynamic_cast<Chain<Stink>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'G':
                    {
                        Chain<Green>* chain = dynamic_cast<Chain<Green>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 's':
                    {
                        Chain<soy>* chain = dynamic_cast<Chain<soy>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'b':
                    {
                        Chain<black>* chain = dynamic_cast<Chain<black>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'R':
                    {
                        Chain<Red>* chain = dynamic_cast<Chain<Red>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                case 'g':
                    {
                        Chain<garden>* chain = dynamic_cast<Chain<garden>*>(joueurChains.front());
                        std::cout << "> Acquisition " << chain->sell() << " pièces" << std::endl;
                        pCoins += chain->sell();
                    }
                    break;
                default:
                    std::cout << "(playCard) Vérifiez le type de chaîne. Valeur reçue : " << joueurChains.front()->getChainType() << std::endl;
                    exit(1);
            }

             
              joueurChains.erase(joueurChains.begin()); // enlever la chaîne au début

            }
            else if(joueurChains.size() < chain_approuvee){
                joueurChains.push_back(new_chain);
                if( (*new_chain).getSize() == 0 ){ // mettre à jour le type de chaîne si le type de chaîne de Chain_Base si la chaîne est vide
                     (*new_chain).setChainType(card->getName());
                }
                card = joueurMain->play();
                *new_chain += card;
            }else{
                std::cout << ">>> joueur " <<joueurNom << " a atteint la valeur maximale autorisée de la chaîne ("<<chain_approuvee<<")." << std::endl;
                std::cout << std::endl << "> Voulez-vous acheter une troisième chaîne ? (o/n)" << std::endl;
                std::cin >> user_input;
                if(user_input[0] == 'y'){
                    // acheter une troisième chaîne
                    buyThirdChain();
                    // ajouter la carte à l’intérieur de la chaîne nouvellement achetée
                    for(Chain_Base* chain : joueurChains){
                        if(chain->getChainType() == card -> getName()){
                            new_chain = chain;
                            card = joueurMain -> play();
                            *new_chain += card;
                            break;
                        }
                    }
                }
                else {
                    std::cout << "> Vente de la chaîne de type : " << joueurChains.front()->getChainType() << std::endl;

                    switch (joueurChains.front()->getChainType()[0]) {
                        case 'B':
                            {
                                Chain<Blue>* chain = dynamic_cast<Chain<Blue>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'C':
                            {
                                Chain<Chili>* chain = dynamic_cast<Chain<Chili>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'S':
                            {
                                Chain<Stink>* chain = dynamic_cast<Chain<Stink>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'G':
                            {
                                Chain<Green>* chain = dynamic_cast<Chain<Green>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 's':
                            {
                                Chain<soy>* chain = dynamic_cast<Chain<soy>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'b':
                            {
                                Chain<black>* chain = dynamic_cast<Chain<black>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'R':
                            {
                                Chain<Red>* chain = dynamic_cast<Chain<Red>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        case 'g':
                            {
                                Chain<garden>* chain = dynamic_cast<Chain<garden>*>(joueurChains.front());
                                std::cout << "> Acquisition de " << chain->sell() << " pièces" << std::endl;
                                pCoins += chain->sell();
                            }
                            break;
                        default:
                            std::cout << "(playCard) Vérifiez le type de chaîne. Valeur reçue : " << joueurChains.front()->getChainType() << std::endl;
                            exit(1);
                    }

                    joueurChains.erase(joueurChains.begin()); // Supprimer la chaîne au début

                    // Démarrage d'une nouvelle chaîne
                    switch (card->getName()[0]) {
                        case 'B':
                            new_chain = new Chain<Blue>;
                            break;
                        case 'C':
                            new_chain = new Chain<Chili>;
                            break;
                        case 'S':
                            new_chain = new Chain<Stink>;
                            break;
                        case 'G':
                            new_chain = new Chain<Green>;
                            break;
                        case 's':
                            new_chain = new Chain<soy>;
                            break;
                        case 'b':
                            new_chain = new Chain<black>;
                            break;
                        case 'R':
                            new_chain = new Chain<Red>;
                            break;
                        case 'g':
                            new_chain = new Chain<garden>;
                            break;
                        default:
                            std::cout << "(playCard) Vérifiez le nom de la carte. Valeur reçue : " << card->getName() << std::endl;
                            new_chain = nullptr;
                            exit(1);
                    }

                    joueurChains.push_back(new_chain);

                    if( (*new_chain).getSize() == 0 ){ // Mettre à jour le type de chaîne si le type de la chaîne de Chain_Base est vide
                        (*new_chain).setChainType(card->getName());
                    }

                    card = joueurMain->play();
                    *new_chain += card;
                            } // Fin du else
                        } // Fin du else
                    } // Fin du if
                }
                return card;
}


/**
 *  retourne le nombre maximal de chaine autorisé dans le jeu pour le joueur correspondant
 *  
 */
int Player::getMaxNumChains(){
    return num_max_chain;
}


/**
 *  retourne le nombre de chaine non nul que le joueur possède 
 *  
 */
int Player::getNumChains(){
    int counter = 0; 
    for(int i = 0; i < joueurChains.size(); i++){
        if( (joueurChains.at(i))->getSize() > 0) counter++;
    }
    return counter;
}


/**
 * Ajoute une troisième chaîne vide au joueur pour trois pièces. La fonction réduit le nombre de pièces du joueur de trois.
 * Si le joueur n'a pas suffisamment de pièces, une exception NotEnoughCoins est déclenchée.
 */

void Player::buyThirdChain() {
    Card* card = nullptr;
    if ((pCoins % 3 == 0) && (pCoins > 0)) {
        if (joueurChains.size() < num_max_chain) {
            pCoins -= 3;
            card = joueurMain->top();
            Chain_Base* new_chain;

            switch (card->getName()[0]) {
                case 'B':
                    new_chain = new Chain<Blue>;
                    break;
                case 'C':
                    new_chain = new Chain<Chili>;
                    break;
                case 'S':
                    new_chain = new Chain<Stink>;
                    break;
                case 'G':
                    new_chain = new Chain<Green>;
                    break;
                case 's':
                    new_chain = new Chain<soy>;
                    break;
                case 'b':
                    new_chain = new Chain<black>;
                    break;
                case 'R':
                    new_chain = new Chain<Red>;
                    break;
                case 'g':
                    new_chain = new Chain<garden>;
                    break;
                default:
                    std::cout << "(playCard) Vérifiez le nom de la carte. Valeur reçue : " << card->getName() << std::endl;
                    new_chain = nullptr;
                    exit(1);
                    break;
            }

            *new_chain += card;
            joueurChains.push_back(new_chain);
        } else {
            std::cout << "Impossible d'acheter une nouvelle chaîne. Le nombre maximum [" << joueurChains.size() << "] de chaînes a été atteint. " << std::endl;
        }
    } else {
        throw std::runtime_error("PasAssezDePieces");
    }
}



/**
 *  Ajoute une carte à la main du joueur.
 */
void Player::takeCard(Card* card){
    *joueurMain += card;  // Ajoute la carte à la main du joueur
}

/**
 *  Retire la carte du dessus de la main du joueur à la position spécifiée et renvoie la carte correspondante.
 */
Card* Player::removeCard(int pos){
    Card* card = nullptr;
    if(pos >  joueurMain->numCards()-1){
        std::cout << "Veuillez spécifier l'index approprié pour supprimer de la main du joueur. " << std::endl;
        std::cout << "Index saisi : " << pos << std::endl;
        std::cout << "Taille actuelle de la main : " << joueurMain->numCards() << std::endl;
        std::cout << "Carte non supprimée." << std::endl;
    } else {
        card = (*joueurMain)[pos];
    }
    return card;
}

/**
 *  Renvoie le nombre de pièces que le joueur possède.
 */
int Player::getNumCoins(){
    return pCoins;
}

/**
 *  Opérateur d'insertion pour afficher l'objet joueur.
 */
std::ostream& operator<<(std::ostream& output, const Player& player){
    output << player.joueurNom << std::setw(5) << player.pCoins << " pièces "<< std::endl;
    for(auto chain : player.joueurChains){
        output << *chain;
        output << std::endl;
    }
    return output;
}

/**
 *  Écrit les informations du joueur dans un fichier texte.
 */
void Player::savePlayer(int p_id){
    std::ofstream file;
    char id[2];
    sprintf_s(id, "%d", p_id);
    std::string filename ="Sauvegarde-Joueur"+std::string(id)+".txt";
    file.open(filename, std::ios::trunc);

    // La première ligne doit être le nom du joueur.
    file << joueurNom << std::endl;

    // La deuxième ligne doit être le nombre de pièces du joueur.
    file << pCoins << std::endl;

    // Sauvegarde de la main.
    joueurMain->saveHand(file);

    file << std::endl << "-chaînes" << std::endl;

    for(int i = 0 ; i < joueurChains.size() ; i++){
        file << std::endl << "---" << std::endl;
        joueurChains.at(i)->saveChain(file);
    }
    
    file << std::endl << "-fin-chaînes" << std::endl;

    file.close();

    std::cout << "Joueur-"+std::string(id) << " sauvegardé. " << std::endl;
}

/**
 *  Renvoie la main du joueur.
 */
Hand* Player::getHand(){
    return joueurMain;
}

/**
 *  Renvoie les chaînes du joueur.
 */
std::vector<Chain_Base*>* Player::getChains(){
    return &joueurChains;
}

/**
*  Construct a new Player object from an istream
*/
Player::Player(std::istream& input, const CardFactory* cf): num_max_chain(3), chain_approuvee(2){
            std::string line;
            std::string typeChain;
            Card* card = nullptr;
            joueurMain = new Hand();
            int  chain_idx = -1; 
            int  count = 0;
            bool nomInitialise   = false;
            bool pieceInitialise  = false;
            bool mainInitialise   = false;
            bool chainsInitialise = false;
            bool typeChainInitialise = false;
            
            while (std::getline(input, line))
            {
                std::istringstream iss(line);
                std::string data;
                if (!(iss >> data)) { 
                    continue;
                } 
                if(!nomInitialise) {
                    joueurNom = data;
                    nomInitialise = true;
                    continue;
                }
                if(!pieceInitialise){
                    const char *str_data =  &data[0];
                    sscanf_s(str_data, "%d", &pCoins);
                    pieceInitialise = true;
                    continue;
                }

                // initialized the hand
                if(!mainInitialise){
                    if(data == "-chains"){
                        mainInitialise = true; // nous avons atteint la fin du contenu de la main
                        continue;
                    } 
                    else{
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
                                std::cout << "(Constructeur de joueurs) Vérifiez le nom de la carte dans le fichier. Valeur reçue : " << data << std::endl;
                                exit(1);
                                break;
                        }

                      //
                      if(card != nullptr) *joueurMain+=card;
                   }
                }

                // initialize the chains
                if(!chainsInitialise && mainInitialise){ // wait for the chain to be initialized 

                    if(data == "-end-chains") {
                        chainsInitialise = true;
                        continue;
                    }
                    else{
                       if(data == "---"){
                           typeChainInitialise = false;
                           continue; // get the chain data
                       }else{
                           if(!typeChainInitialise){
                             // the first line is the chain type
                             typeChain = data;
                             typeChainInitialise = true;

                             Chain_Base* new_chain;
                             switch (typeChain[0]) {
                                case 'B':
                                    new_chain = new Chain<Blue>;
                                    break;
                                case 'C':
                                    new_chain = new Chain<Chili>;
                                    break;
                                case 'S':
                                    new_chain = new Chain<Stink>;
                                    break;
                                case 'G':
                                    new_chain = new Chain<Green>;
                                    break;
                                case 's':
                                    new_chain = new Chain<soy>;
                                    break;
                                case 'b':
                                    new_chain = new Chain<black>;
                                    break;
                                case 'R':
                                    new_chain = new Chain<Red>;
                                    break;
                                case 'g':
                                    new_chain = new Chain<garden>;
                                    break;
                                default:
                                    std::cout << "(Constructeur de joueurs) Vérifiez le type de chaîne. Valeur reçue : " << typeChain << std::endl;
                                    new_chain = nullptr;
                                    exit(1);
                                    break;
                            }

                             // add the chain if it has been initialized
                             if(new_chain != nullptr) {
                                 joueurChains.push_back(new_chain);
                                 chain_idx++;
                             }

                          }else{
                              card = nullptr;
                              // collect the card
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
                                    std::cout << "(Constructeur de joueurs) Vérifiez le nom de la carte dans le fichier. Valeur reçue : " << data << std::endl;
                                    exit(1);
                                    break;
                            }
                              if(chain_idx != -1 && card != nullptr){
                                  *(joueurChains.at(chain_idx))+=card;
                              }else{
                                  std::cout << "(Constructeur de joueurs) Aucune chaîne na été ajoutée jusquà présent. chain_idx : " << chain_idx << std::endl;
                              }
                          }
                       }
                    }// fin block else
                }// fin de if
            }// fin boucle while 

            std::cout << "Lecteur initialisé à partir du fichier correctement." <<std::endl;
        }
