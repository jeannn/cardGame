#include "Card.h"
using namespace std;

// Card

// detruit Card:: Card object
Card::~Card() {}

//blue
// Constructeur Blue:: Blue object
Blue::Blue(std::string name){
    this->name = name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int Blue::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalide

    switch(coins) {
        case 1:
            numeroCarte = 4;
            break;
        case 2:
            numeroCarte = 6;
            break;
        case 3:
            numeroCarte = 8;
            break;
        case 4:
            numeroCarte = 10;
            break;
        default:
            cout << "(Blue) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}

//retourne le nom de la carte
string Blue::getName(){
    return this->name;
}

// afficher la première lettre du nom de la carte
void Blue::print(std::ostream& out){
    out << this->getName()[0];
}

//chili
//Constructeur Chili:: Chili object
Chili::Chili(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string Chili::getName(){
    return this->name;
}

//retourne le nombre de cartes qui correspond au nombre de piece
int Chili::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 3;
            break;
        case 2:
            numeroCarte = 6;
            break;
        case 3:
            numeroCarte = 8;
            break;
        case 4:
            numeroCarte = 9;
            break;
        default:
            cout << "(Chili) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}

// afficher la première lettre du nom de la carte
void Chili::print(std::ostream& out){
    out << this->getName()[0];
}

//stink
// Constructeur Stink:: Stink object
Stink::Stink(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string Stink::getName(){
    return this->name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int Stink::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 3;
            break;
        case 2:
            numeroCarte = 5;
            break;
        case 3:
            numeroCarte = 7;
            break;
        case 4:
            numeroCarte = 8;
            break;
        default:
            cout << "(Stink) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}

// afficher la première lettre du nom de la carte
void Stink::print(std::ostream& out){
    out << this->getName()[0];
}

// Green
// Constructeur Green:: Green object
Green::Green(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string Green::getName(){
    return this->name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int Green::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 3;
            break;
        case 2:
            numeroCarte = 5;
            break;
        case 3:
            numeroCarte = 6;
            break;
        case 4:
            numeroCarte = 7;
            break;
        default:
            cout << "(Green) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}
// afficher la première lettre du nom de la carte
void Green::print(std::ostream& out){
    out << this->getName()[0];
}

// soy
// Constructeur soy::soy object
soy::soy(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string soy::getName(){
    return this->name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int soy::getCardsPerCoin(int coins){
    int numeroCarte = -1;

    switch(coins) {
        case 1:
            numeroCarte = 2;
            break;
        case 2:
            numeroCarte = 4;
            break;
        case 3:
            numeroCarte = 6;
            break;
        case 4:
            numeroCarte = 7;
            break;
        default:
            cout << "(soy) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}

// afficher la première lettre du nom de la carte
void soy::print(std::ostream& out){
    out << this->getName()[0];
}

// black
// Construct a new black::black object
black::black(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string black::getName(){
    return this->name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int black::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 2;
            break;
        case 2:
            numeroCarte = 4;
            break;
        case 3:
            numeroCarte = 5;
            break;
        case 4:
            numeroCarte = 6;
            break;
        default:
            cout << "(black) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}

// afficher la première lettre du nom de la carte
void black::print(std::ostream& out){
    out << this->getName()[0];
}

// Red
// Constructeur Red:: Red object
Red::Red(std::string name){
    this->name = name;
}

// retourne le nom de la carte
string Red::getName(){
    return this->name;
}

// retourne le nombre de cartes qui correspond au nombre de piece
int Red::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 2;
            break;
        case 2:
            numeroCarte = 3;
            break;
        case 3:
            numeroCarte = 4;
            break;
        case 4:
            numeroCarte = 5;
            break;
        default:
            cout << "(Red) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }

    return numeroCarte;
}
// afficher la première lettre du nom de la carte
void Red::print(std::ostream& out){
    out << this->getName()[0];
}
//garden
// Constructeur garden::garden object
garden::garden(std::string name){
    this->name = name;
}
// retourne le nom de la carte
string garden::getName(){return this->name;}
// afficher la première lettre du nom de la carte
void garden::print(std::ostream& out){out << this->getName()[0] ;}
// affiche card object
std::ostream& operator<<(std::ostream& out, Card& card)
{
    card.print(out);
    return out;
}
// mettre la carte dans un fichier
void Card::saveCard(std::ofstream& filename){
    filename << *this;
}
// retourne le nombre de cartes qui correspond au nombre de piece
int garden::getCardsPerCoin(int coins){
    int numeroCarte = -1; // invalid

    switch(coins) {
        case 1:
            numeroCarte = 0;
            break;
        case 2:
            numeroCarte = 2;
            break;
        case 3:
            numeroCarte = 3;
            break;
        case 4:
            numeroCarte = 0;
            break;
        default:
            cout << "(garden) - Vérifiez la valeur des pièces passées getCardsPerCoin. Valeur reçue : " << coins << endl;
    }
    return numeroCarte;
}