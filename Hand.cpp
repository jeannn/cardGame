#include "Hand.h"

// Retourne la premiere carte de la main et la suprime
Card* Hand::play() {
    Card* card = hand.front();
    hand.pop();
    return card;
}

// Retourne la premiere carte de la main sans la suprimer
Card* Hand::top() {
    return hand.front();
}

// Retourne le nombre de cartes dans la main
int Hand::numCards() {
    return hand.size();
}

// Retourne la carte de la main à un index donné
Card* Hand::getCard(int pos) {
    Card* card = nullptr;

    switch (pos > hand.size() - 1) {
        case true:
            std::cout << "(getCard) L'index " << pos << " ne peut pas être utilisé. Taille actuelle de la main = " << hand.size() << std::endl;
            break;
        case false:
            card = getCardAtIndex(pos);
            break;
    }

    return card;
}

Card* Hand::getCardAtIndex(int pos) {
    Card* extractedCard = nullptr;
    std::queue<Card*, std::list<Card*>> tempQueue;
    Card* tempCard = nullptr;
    int currentIdx = 0;

    while (!hand.empty()) {
        if (currentIdx++ == pos) {
            extractedCard = hand.front();
        }

        tempCard = hand.front();
        hand.pop();
        tempQueue.push(tempCard);
    }

    restoreCardsFromTemp(tempQueue);

    return extractedCard;

    }


// Operateur d'insertion pour afficher le contenue de la main
std::ostream& operator<<( std::ostream& output, Hand& hand){
    for( int pos = 0; pos < hand.numCards() ; pos++ ){
        output << hand.getCard(pos) << std::endl;
    }
    return output;
};


// sauvegarder la main dans un fichier
void Hand::saveHand(std::ofstream& filename) {
    saveCardsToFile(filename);
    std::cout << "Main sauvegardee." << std::endl;
}

void Hand::saveCardsToFile(std::ofstream& filename) {
    Card* card = nullptr;
    std::queue<Card*, std::list<Card*>> temp;
    Card* temp_card = nullptr;
    int find_idx = 0;

    while (!hand.empty()) {
        temp_card = hand.front();
        temp_card->saveCard(filename);
        filename << std::endl;
        hand.pop();
        temp.push(temp_card);
    }

    restoreCardsFromTemp(temp);
}

void Hand::restoreCardsFromTemp(std::queue<Card*, std::list<Card*>>& temp) {
    Card* temp_card = nullptr;

    while (!temp.empty()) {
        temp_card = temp.front();
        temp.pop();
        hand.push(temp_card);
    }

    std::cout << "Main sauvegardee." << std::endl;
}

// Get the List Of Cards inside the hand
std::queue <Card*, std::list<Card*>> * Hand::getListOfCards(){
    return &hand;
}


Hand::Hand(std::istream& input, const CardFactory* cf) {
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
        card = createCardFromData(data, cf);

        if (card != nullptr) {
            hand.push(card);
        }
    }

    std::cout << "main avec " << count << " cards initialisée depuis fichier avec succès." << std::endl;
}

Card* Hand::createCardFromData(const std::string& data, const CardFactory* cf) {
    Card* card = nullptr;

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
            std::cout << "(Hand Constructor) Vérifiez le nom de la carte dans le fichier. Valeur reçue : " << data << std::endl;
            exit(1);
            break;
    }

    return card;
}


Card* Hand::operator[](int pos) {
    Card* card = nullptr;
    std::queue<Card*, std::list<Card*>> temp;
    int find_idx = 0;

    while (!hand.empty()) {
        if (find_idx == pos) {
            card = hand.front();
            hand.pop();
        } else {
            temp.push(hand.front());
            hand.pop();
        }
        find_idx++;
    }

    while (!temp.empty()) {
        hand.push(temp.front());
        temp.pop();
    }

    return card;
}

Hand& Hand::operator+=(Card* card) {
    hand.push(card);
    return *this;
}