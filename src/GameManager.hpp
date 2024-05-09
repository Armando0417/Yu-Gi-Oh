#include "ofMain.h"
#include "Card.hpp"
#include "GameBoard.hpp"
#include "Player.hpp"

#include "GameStateManager.hpp"

#include "Button.hpp"

class GameManager {

    public:
        vector<unique_ptr<GameBoardGui>> gameboards;
        vector<unique_ptr<Player>> players;
        unique_ptr<GameStateManager> stateManager;
        unique_ptr<Button> stateButton;

        GameManager() {
            unique_ptr<Player> player1 = make_unique<Player>("Player 1", 1);
            unique_ptr<Player> player2 = make_unique<Player>("Player 2", 2);
            players.push_back(move(player1));
            players.push_back(move(player2));

            gameboards.push_back( make_unique<GameBoardGui>(PlayerID::BOTTOM_PLAYER) );
            gameboards.push_back( make_unique<GameBoardGui>(PlayerID::TOP_PLAYER) );

            for (auto& board : gameboards) {
                board->setup();
            }

            stateManager = make_unique<GameStateManager>();
            stateButton = make_unique<Button> (ofGetWidth()/2 - 300, 10, 500, 100, "", "Next Phase");

        }
        void startGame() {
            // Initial game setup
        }
        
        void update() { 

            WhichPhase();
            if(stateButton->wasPressed()){
                stateManager->nextPhase();
            }
            stateButton->update();
            
            for(auto& board : gameboards) {
                board->update();
            }
        }

        void renderGame() { 
            for(auto& board : gameboards) {
                board->renderBoard();
            }

            if (players.size() >= 2){
                gameboards[0]->drawPlayerHand(*players[0]);  // Assuming players[0] is the bottom player
                gameboards[1]->drawPlayerHand(*players[1]);  // Assuming players[1] is the top player
            }
            stateButton->draw();
        }


        void WhichPhase(){
            switch (stateManager->getCurrentState()){
                case GameStateManager::DRAW_PHASE_TOP_PLAYER : stateButton->setString("Draw Phase Top Player"); break;
                case GameStateManager::MAIN_PHASE_1_TOP_PLAYER : stateButton->setString("Main Phase 1 Top Player"); break;
                case GameStateManager::BATTLE_PHASE_TOP_PLAYER : stateButton->setString("Battle Phase Top Player"); break;
                case GameStateManager::MAIN_PHASE_2_TOP_PLAYER : stateButton->setString("Main Phase 2 Top Player"); break;
                case GameStateManager::END_PHASE_TOP_PLAYER : stateButton->setString("End Phase Top Player"); break;

                case GameStateManager::DRAW_PHASE_BOT_PLAYER : stateButton->setString("Draw Phase Bot Player"); break;
                case GameStateManager::MAIN_PHASE_1_BOT_PLAYER : stateButton->setString("Main Phase 1 Bot Player"); break;
                case GameStateManager::BATTLE_PHASE_BOT_PLAYER : stateButton->setString("Battle Phase Bot Player"); break;
                case GameStateManager::MAIN_PHASE_2_BOT_PLAYER : stateButton->setString("Main Phase 2 Bot Player"); break;
                case GameStateManager::END_PHASE_BOT_PLAYER : stateButton->setString("End Phase Bot Player"); break;
            }
        }




        void playerPlaysCard(unsigned int playerIndex, ZoneType zone, int handIndex) {
            if (playerIndex < players.size()) {
                unique_ptr<Card> card = players[playerIndex]->requestPlayCard(handIndex);
                
                if (card && gameboards[0]->isZoneAvailable(zone)) {
                    gameboards[0]->zones[zone].card = move(card); // Execute the card play
                }
            }
        }

        void sendCardToGraveyard(int playerIndex, unique_ptr<Card> card) {
            if(card) players[playerIndex]->addToGraveyard(move(card));
        }

        void mouseMoved(int mouseX, int mouseY) {
            for(auto & board : gameboards) {
                for(auto & zone : board->zones) {
                    zone.second.checkZone(mouseX, mouseY);
                }
            }
        }
        void mousePressed(int mouseX, int mouseY) {
            stateButton->setPressed(mouseX, mouseY);

            for(auto & board : gameboards) {
                for(auto & zone : board->zones) {
                    if(zone.second.selected) {
                        unique_ptr<Card> c = make_unique<MonsterCard>("Blue Eyes White Dragon", 8, 3000, 2500, "bin\\data\\CardImages\\BEWD.jpg");
                        zone.second.setCard(move(c));
                    }
                }
            }
        }

};