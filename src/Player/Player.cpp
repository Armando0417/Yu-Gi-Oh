#include "player.hpp"


    void Player::drawCard() {
        if (!deck.empty()) {
            hand.push_back( move(deck.back() ));
            deck.pop_back();
        }   
    }

    unique_ptr<Card> Player::requestPlayCard(unsigned int handIndex) {
            if (handIndex < hand.size()) {
                unique_ptr<Card> card = move(hand[handIndex]);
                hand.erase(hand.begin() + handIndex);
                return card;
            }
            return nullptr;
    }

    void Player::calculateLifePoints(int change) {
        lifePoints += change;
    }

    void Player::addToGraveyard(unique_ptr<Card> card) {
        if(card) graveyard.push_back(move(card));
               
    }
