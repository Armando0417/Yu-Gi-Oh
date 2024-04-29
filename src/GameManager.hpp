#include "ofMain.h"
#include "Card.hpp"
#include "GameBoard.hpp"
#include "Player.hpp"

class GameManager {

    public:

        GameBoardGui gameBoard;
        vector<unique_ptr<Player>> players;

        GameManager() {
            unique_ptr<Player> player1 = make_unique<Player>("Player 1", 1);
            unique_ptr<Player> player2 = make_unique<Player>("Player 2", 2);
            players.push_back(move(player1));
            players.push_back(move(player2));

            unique_ptr<GameBoardGui> gameBoard = make_unique<GameBoardGui>(PlayerID::TOP_PLAYER);
            
            gameBoard->setup();
        }
        void startGame() {
            // Initial game setup
        }
        
        void update() {
            for (auto& cardsOnField : gameBoard.zones) {
                if ( cardsOnField.second.card && cardsOnField.second.card->wasDestroyed() ) {
                //     sendCardToGraveyard()


                // }
                }
            

            }
        }

        void playerPlaysCard(int playerIndex, ZoneType zone, int handIndex) {
            if (playerIndex < players.size()) {
                unique_ptr<Card> card = players[playerIndex]->requestPlayCard(handIndex);
                
                if (card && gameBoard.isZoneAvailable(zone)) {
                    gameBoard.zones[zone].card = move(card); // Execute the card play
                }
            }
        }

        void sendCardToGraveyard(int playerIndex, unique_ptr<Card> card) {
            if(card) players[playerIndex]->addToGraveyard(move(card));
        }

};