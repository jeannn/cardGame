#include "Deck.h"
using namespace std;

// retourne et suprime la derniere carte du deck
Card* Deck::draw(){
    Card* card =  this->back(); 
    this->pop_back(); 
    return card;  
}

// Definition de l'operateur d'assignement pour la class Deck
Deck& Deck::operator=(const Deck& deck){
    int i = 0 ;
    while( i < deck.size() && i < 104){
        this->push_back(deck[i]);
        i++;
    }
    return *this;
}

// operateur d'insertion de flux pour Deck 
ostream& operator<<( ostream& outp, const Deck& deck ){
    int i=0;
    while(i < deck.size()){
        outp << deck.at(i)->getName()[0] << endl;
        i++;
    }
    return outp;
}

// Constructeur de recopie 
Deck::Deck(const Deck& d){
    // efface le vieux deck
    this->clear(); 

    // obtient le contenu du deck actuel
    int i = 0; 
    while(i < 104){
        this->push_back(d.at(i));i++;
    }
    std::cout << "Deck de taille("<<d.size()<<") copié."<<std::endl;
}

Deck::Deck(std::istream& input, const CardFactory* cf):std::vector<Card*> (){
    std::string ligne;
    Card* card = nullptr;
    int count = 0;
    while (std::getline(input, ligne)){
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
        std::cout << "(Deck Constructor) Vérifier le nom de la card dans le fichier. Valeur reçue : " << data << std::endl;
        exit(1);
    }

    if(card != nullptr) {
        this->push_back(card);
        }
    }
    std::cout << "Deck avec " << count << " cards initialisé depuis le fichier avec succès." <<std::endl;
};


// sauvegarde le deck dans un fichier
void Deck::saveDeck(std::ofstream& fichier){
    int i=this->size();
    while (i >0){
        this->at(i)->saveCard(fichier);
        fichier << std::endl;
        i--;
    }
    std::cout << "Deck enregistré." << std::endl;
}

// Destructeur de Deck
Deck::~Deck(){
    int i = this->size();
    while (i > 0) {
        delete this->at(i);
        i--;
    }
    std::cout << "Deck de taille("<<this->size()<<") détruit."<<std::endl;
}