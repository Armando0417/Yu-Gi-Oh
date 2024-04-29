#include "GameBoard.hpp"


void GameBoardGui::setup() {
        gui.setup("Game Board Control Panel");
            gui.add(cardWidth.set("Card Width", 86.5, 50, 150));
            gui.add(cardHeight.set("Card Height", 137.5, 100, 200));
            // Need to check where to start drawing the board depending which player it belongs to
                gui.add(xOffset.set("X Offset", owner == TOP_PLAYER ? 390 : 390, 0, 1000)); 
                gui.add(yOffset.set("Y Offset", owner == TOP_PLAYER ? 110 : 570, 0, 1000));
            gui.add(padding.set("Padding", 87.875, 5, 200));

        if (owner == TOP_PLAYER) gui.setPosition(ofGetWidth() - gui.getWidth() - 10, 10);
        else gui.setPosition(10, 10);

        std::cout << "GUI position for " << (owner == TOP_PLAYER ? "Top" : "Bottom") << " player: " << gui.getPosition() << std::endl;

        float startingX = xOffset;
        float startingY = yOffset;

        // Setting up the Field Zone at the start of the top row
        zones[FIELD_ZONE].setParameters(startingX, startingY, cardWidth, cardHeight);

        // Setting up the Extra Deck at the start of the bottom row
        zones[EXTRA_DECK].setParameters(startingX, startingY + cardHeight + padding, cardWidth, cardHeight);

        float currentX = startingX + cardWidth + padding; // Increment x position after the Field Zone

        // Setting up Monster Zones and Spell & Trap Zones
        for (int i = 0; i < 5; ++i) {
            zones[static_cast<ZoneType>(MONSTER_ZONE_1 + i)].setParameters(currentX, startingY, cardWidth, cardHeight);
            zones[static_cast<ZoneType>(SPELL_TRAP_ZONE_1 + i)].setParameters(currentX, startingY + cardHeight + padding, cardWidth, cardHeight);
            currentX += cardWidth + padding;
        }

        // Setting up the Graveyard at the end of the top row
        zones[GRAVEYARD].setParameters(currentX, startingY, cardWidth, cardHeight);

        // Setting up the Deck at the end of the bottom row
        zones[DECK].setParameters(currentX, startingY + cardHeight + padding, cardWidth, cardHeight);


    }
    


   
void GameBoardGui::update() {
     // Constants for the layout
            float startingX = xOffset;
            float startingY = yOffset;

            // Update positions and sizes for each zone
            zones[FIELD_ZONE].setParameters(startingX, startingY, cardWidth, cardHeight);
            zones[EXTRA_DECK].setParameters(startingX, startingY + cardHeight + padding, cardWidth, cardHeight);

            float currentX = startingX + cardWidth + padding; // Start after the field/extra deck zone

            for (int i = 0; i < 5; i++) {
                zones[static_cast<ZoneType>(MONSTER_ZONE_1 + i)].setParameters(currentX, startingY, cardWidth, cardHeight);
                zones[static_cast<ZoneType>(SPELL_TRAP_ZONE_1 + i)].setParameters(currentX, startingY + cardHeight + padding, cardWidth, cardHeight);
                currentX += cardWidth + padding;
            }

            zones[GRAVEYARD].setParameters(currentX, startingY, cardWidth, cardHeight);
            zones[DECK].setParameters(currentX, startingY + cardHeight + padding, cardWidth, cardHeight);
}

void GameBoardGui::drawBoard() {
    //  ofBackground(30);
    if (owner == TOP_PLAYER) {
        ofSetColor(100, 100, 250);  // Light blue background for top player
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()/2);  // Half-height background
    } 
    else {
        ofSetColor(250, 100, 100);  // Light red background for bottom player
        ofDrawRectangle(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2);  // Half-height background
    }


    gui.draw();
    for (auto& zone : zones) {
        zone.second.draw();
    }
}

void GameBoardGui::battleBetweenZones(ZoneType attacker, ZoneType defender){
     if(zones[attacker].isTaken() && zones[defender].isTaken()) {
                Card* atkCard = zones[attacker].card.get();
                Card* defCard = zones[defender].card.get();

                MonsterCard* monsterAtk = dynamic_cast<MonsterCard*>(atkCard);
                MonsterCard* monsterDef = dynamic_cast<MonsterCard*>(defCard);

                if (monsterAtk && monsterDef) {
                    if (monsterAtk->getATK() > monsterDef->getDEF()) {
                        zones[defender].card->destroy();
                        // zones[defender].card.reset();
                    }

                    else if (monsterAtk->getATK() < monsterDef->getDEF()) {
                        zones[attacker].card->destroy();
                        // zones[attacker].card.reset();   
                    }

                    else return;
                }
            }
}