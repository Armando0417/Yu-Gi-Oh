#include "ofMain.h"
#include "Card.hpp"


class DeckMaker {

    public:
         vector<Card> deck;


        DeckMaker() {}


         bool loadDeck(const std::string& fileName) {
            std::ifstream file(fileName);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << fileName << std::endl;
                return false;
            }

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                
                std::string name, token;
                int attack, defense;

                std::getline(ss, name, ',');  // Get the first element as the name
                std::getline(ss, token, ','); // Then attack
                attack = std::stoi(token);
                std::getline(ss, token, ','); // Then defense
                defense = std::stoi(token);


                // // CardType cardType = static_cast<CardType>(type);
                // std::unique_ptr<CardEffect> effect = std::make_unique<CardEffect>(DECREASE_ATK, 100, 2); // Example effect

                // Assuming you have a suitable constructor that can handle these parameters
                MonsterCard tempCard(name, 10, attack, defense, ofImage());
                deck.push_back(std::move(tempCard)); // Use std::move to transfer ownership
            }

            file.close();
            return true;
        }
         void printDeck() {
            for (auto& card : deck) {
                card.print();
            }
        }


};