#include "Chain.h"
#include <iomanip>

//retourne le nombre de cartes dans la chaine
int Chain_Base::getSize(){
    return chain.size();
}

// Modifie le type de la chaine
void Chain_Base::setChainType(std::string type){
    chainType = type;
}


// Retourne le type de la chaine 
std::string Chain_Base::getChainType(){
    return chainType;
}

// Sauvagarde la chaine dans un fichier
void Chain_Base::saveChain(std::ofstream& fichier) {
    fichier << std::endl << chainType << std::endl;
    int i = chain.size() - 1;
    while (i > 0) {
        chain.at(i)->saveCard(fichier);
        fichier << std::endl;
        i--;
    }
    std::cout << "Chaine savegardée." << std::endl;
}


// operateur d'insertion de flux pour chaine
std::ostream& operator<<(std::ostream& output, const Chain<Card*>& a) {
    output << a.chainType << " ";
    int i = a.chain.size() - 1;
    while (i > 0) {
        a.chain.at(i)->print(output);
        output << " ";
        i--;
    }
    return output;
};


// operateur d'insertion de flux pour chaine de base
std::ostream& operator<<(std::ostream& output, const Chain_Base& a) {
    output << a.chainType << " ";
    int i = a.chain.size() - 1;
    while (i > 0) {
        a.chain.at(i)->print(output);
        output << " ";
        i--;
    }
    return output;
}