#pragma once
#include "ofMain.h"
#include "Card.hpp"
#include "GameBoard.hpp"

class Player {
    
    public:
        string name;
        int lifePoints;
        int ID;
        vector<unique_ptr<Card>> hand;
        vector<unique_ptr<Card>> deck;
        vector<unique_ptr<Card>> graveyard;

        Player(string n, int id) : name(n), lifePoints(8000), ID(id)  {}

        void drawCardFromDeck();
        unique_ptr<Card> requestPlayCard(unsigned int handIndex);
        void calculateLifePoints(int change);  // Can be positive (healing) or negative (damage)
        void shuffleDeck();
        // Card* drawFromDeck();
        void addToGraveyard(unique_ptr<Card> card);
        

        int getDeckSize() const { return deck.size(); }
        int getLifePoints() const { return lifePoints; }

    



};