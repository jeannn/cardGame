#include "TradeArea.h"

/**
 *  returns true if the card can be legally added to the TradeArea, i.e., a 
card of the same bean is already in the TradeArea.
 */
bool TradeArea::legal (Card* card){

    bool found = false;
    std::list<Card*>::iterator i;
    for( i = tradeAr.begin(); i != tradeAr.end(); i++){
        if( (*i)->getName() == card->getName()) found = true;
    }

    return found;
}

/**
 *  removes a card of the corresponding bean name from the trade area. 
 */
Card* TradeArea::trade (std::string card){

    Card* cardFound = nullptr;
    std::list<Card*>::iterator i;

    for(i = tradeAr.begin(); i != tradeAr.end(); i++){
        if( (*i)->getName() == card){
            cardFound = *i;
            tradeAr.erase(i); // delete the card found
            break;
        } 
    }
    return cardFound;
}

/**
 *  retourne the number of card inside the Trade Area
 */
int TradeArea::numCards(){ return tradeAr.size(); }


/**
 *  insertion operator to display the trade area object
 */
std::ostream& operator<<(std::ostream& output, const TradeArea& tr_arr){

    for(auto card : tr_arr.tradeAr){
        output << card->getName()[0] << " ";
    }

    return output;
}

// add a card inside the trade area
        TradeArea& TradeArea::operator+=(Card* card){
             if(this->legal(card)){
                 tradeAr.push_back(card);
             }else{
                 if(tradeAr.size() < 3){
                     tradeAr.push_back(card);
                 }else{
                     std::cout<< "La carte [" << card->getName() << "] ne peut pas être ajouté à la zone de commerce." << std::endl;
                 }
             }
             return *this;
        }


// write the TradeArea information inside a file
void TradeArea::saveTradeArea(std::ofstream& filename){
    for(auto card: tradeAr){
        card->saveCard(filename);
        filename<<std::endl;
    }

    std::cout << "TradeArea sauvegardee." << std::endl;
}

// return the trade area list of cards
std::list<Card*> TradeArea::getListOfCards(){
    return tradeAr;
}

TradeArea::TradeArea(std::istream& input, const CardFactory* cf) : MAX_CARDS(3) {
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
                std::cout << "(TradeArea Constructor) Vérifiez le nom de la carte dans le fichier. Valeur reçue : " << data << std::endl;
                exit(1);
        }
        if (card != nullptr) {
            tradeAr.push_back(card);
        }
    }
    std::cout << "TradeArea avec " << count << " cartes initialisées à partir du fichier correctement." << std::endl;
}