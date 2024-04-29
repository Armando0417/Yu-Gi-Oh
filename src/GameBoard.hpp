#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPanel.h"
#include "ofParameter.h"

enum ZoneType {
    MONSTER_ZONE_1,
    MONSTER_ZONE_2,
    MONSTER_ZONE_3,
    MONSTER_ZONE_4,
    MONSTER_ZONE_5,
    SPELL_TRAP_ZONE_1,
    SPELL_TRAP_ZONE_2,
    SPELL_TRAP_ZONE_3,
    SPELL_TRAP_ZONE_4,
    SPELL_TRAP_ZONE_5,
    FIELD_ZONE,
    GRAVEYARD,
    DECK,
    EXTRA_DECK
};
struct Zone {
    int xPos;
    int yPos;
    int cardWidth;
    int cardHeight;
    bool selected;
    bool taken;
    // Constructor doesn't set positions and sizes anymore, just initializes them
    Zone() : xPos(0), yPos(0), cardWidth(0), cardHeight(0), selected(false), taken(false) {}

    Zone(int x, int y, int w, int h) : xPos(x), yPos(y), cardWidth(w), cardHeight(h), selected(false), taken(false) {}
    

    void setParameters(float x, float y, float w, float h) {
        xPos = x;
        yPos = y;
        cardWidth = w;
        cardHeight = h;
    }

    void draw() {
        if (taken) {
            ofFill();
            ofSetColor(255, 255, 0);  // Yellow fill if taken
        }
        if (selected) {
            ofNoFill();
            ofSetLineWidth(2);       // Thicker line for visibility
            ofSetColor(255, 0, 0);   // Red border if selected
        } else {
            ofFill();
            ofSetColor(255, 255, 255); // Default fill color
        }
        ofDrawRectangle(xPos, yPos, cardWidth, cardHeight);
        ofSetLineWidth(1);           // Reset line width
    }
};

class GameBoardGui {

    public:
        // GUI Panel
        ofxPanel gui;
        //   vector<Zone> zones;
        map<ZoneType, Zone> zones;
        /*
            Values found:
                - cardWidth: 100
                - cardHeight: 175
                - xOffset: 540
                - yOffset: 775
                - padding: 99.525
        */


        // Parameters for board layout
        ofParameter<float> cardWidth;
        ofParameter<float> cardHeight;
        ofParameter<float> xOffset;
        ofParameter<float> yOffset;
        ofParameter<float> padding;

      
        GameBoardGui() {}

        void setup() {
            gui.setup("Game Board Control Panel");
            gui.add(cardWidth.set("Card Width", 110, 50, 150));
            gui.add(cardHeight.set("Card Height", 175, 100, 200));
            gui.add(xOffset.set("X Offset", 320, 0, 1000));
            gui.add(yOffset.set("Y Offset", 730, 0, 1000));
            gui.add(padding.set("Padding", 99.525, 5, 200));

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

    void update() {
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

        void draw() {
            ofBackground(30);
            gui.draw();
            for (auto& zone : zones) {
                zone.second.draw();
            }
        }


//     void drawGameBoard(){
//         // Draw Monster Zones
//         for(int i = 0; i < 5; ++i) {
//             ofDrawRectangle(xOffset + i * (cardWidth + padding), yOffset, cardWidth, cardHeight);
//         }

//         // Draw Spell and Trap Zones
//         for(int i = 0; i < 5; ++i) {
//             ofDrawRectangle(xOffset + i * (cardWidth + padding), yOffset + cardHeight + padding, cardWidth, cardHeight);
//         }

//         // Draw other specific zones like Deck and Graveyard
//         ofDrawRectangle(xOffset, yOffset + 2 * (cardHeight + padding), cardWidth, cardHeight); // Example for Deck Zone
//         ofDrawRectangle(xOffset + cardWidth + padding, yOffset + 2 * (cardHeight + padding), cardWidth, cardHeight); // Example for Graveyard
// }


};