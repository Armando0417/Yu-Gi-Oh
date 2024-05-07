#include "ofMain.h"
#include "Card.hpp"


class DeckMaker {

    public:
         vector<Card> deck;


        DeckMaker() {}


         bool loadDeck(const string& fileName) {
            ifstream file(fileName);
            if (!file.is_open()) {
                cerr << "Failed to open file: " << fileName << endl;
                return false;
            }

            string line;
            getline(file, line); // Skip the first line
            getline(file, line); // Skip the empty second line 

            while (getline(file, line)) {
                istringstream ss(line);
                
                string name, token, cardType, MonsterType, effect;
                int attack, defense;

                getline(ss, name, ',');  // Get the first element as the name
                getline(ss, cardType, ','); // Then cardType

                if(cardType == "MONSTER"){
                    getline(ss, MonsterType, ','); // Monster Type
                    getline(ss, token, ','); // Stars
                    int stars = stoi(token); 
                    getline(ss, token, ','); // Attack
                    attack = stoi(token);
                    getline(ss, token, ','); // Defense
                    defense = stoi(token);
                    MonsterCard tempCard(name, stars, attack, defense, "");
                    deck.push_back(move(tempCard));
                }
                else if (cardType == "SPELL") {
                    SpellCard tempCard(name, "", "");
                    deck.push_back(move(tempCard));
                }

                // // CardType cardType = static_cast<CardType>(type);
                // unique_ptr<CardEffect> effect = make_unique<CardEffect>(DECREASE_ATK, 100, 2); // Example effect

                // Assuming you have a suitable constructor that can handle these parameters
                // MonsterCard tempCard(name, 10, attack, defense, ofImage());
                // deck.push_back(move(tempCard)); // Use move to transfer ownership
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