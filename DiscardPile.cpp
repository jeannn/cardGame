#include "DiscardPile.h"

// Retourne la derniere carte de discardPile et la suprime
Card* DiscardPile::pickUp(){
    Card* card =  this->back();
    this->pop_back();
    return card;
}

// Retourne la derniere carte de discardPile sans suprimer
Card* DiscardPile::top(){
    return this->back();
}

// Imrpime les cartes de discardPile 
void DiscardPile::print(std::ostream& os) {
    int i = 0;
    while (i < this->size()) {
        os << this->at(i)->getName()[0] << " ";
        i++;
    }
}

// operateur d'insertion de flux pour la derniere carte de Discardpile
std::ostream& operator<<( std::ostream &output, const DiscardPile& dp ){
    if(dp.size() > 0)
       (dp.back())->print(output);
    else 
       output << "";

    return output;
}

// Constructeur à partir d'un fichier 
DiscardPile::DiscardPile(std::istream& input, const CardFactory* cf) : std::vector<Card*>() {
    std::string line;
    Card* card = nullptr;
    int count = 0;
    while (std::getline(input, line)) {
        std::istringstream est(line);
        std::string data;
        if (!(est >> data)) {
            continue;
        }
        count++;
        Card* card;
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
                std::cout << "(DiscardPile Constructor) Vérifiez le nom de la carte dans le fichier. Valeur reçue : " << data << std::endl;
                exit(1);
        }

        if (card != nullptr)
            this->push_back(card);
    }

    std::cout << "DiscardPile avec " << count << " cartes initialisées à partir du fichier avec succès." << std::endl;
}

//write the discard pile inside a file
void DiscardPile::saveDiscardPile(std::ofstream& output_file) {
    int i = 0;
    while (i < this->size()) {
        this->at(i)->saveCard(output_file);
        output_file << std::endl;
        i++;
    }
    std::cout << "Discard Pile sauvegardé." << std::endl;
}

// Ajoute la carte a la fin de discard pile avec l'operateur +=
DiscardPile& DiscardPile::operator+=(Card* c) {
    this->push_back(c);
    return *this;
}