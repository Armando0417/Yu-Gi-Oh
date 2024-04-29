#include "OfMain.h"

struct Zone {
    int xPos;
    int yPos;
    int cardWidth;
    int cardHeight;
    bool selected;

    // Constructor doesn't set positions and sizes anymore, just initializes them
    Zone() : xPos(0), yPos(0), cardWidth(0), cardHeight(0), selected(false) {}

    Zone(int x, int y, int w, int h) : xPos(x), yPos(y), cardWidth(w), cardHeight(h), selected(false) {}
    

    void setParameters(float x, float y, float w, float h) {
        xPos = x;
        yPos = y;
        cardWidth = w;
        cardHeight = h;
    }



    void draw() {
        if(selected) ofSetColor(255, 0, 0);
        
        ofDrawRectangle(xPos, yPos, cardWidth, cardHeight);

        ofSetColor(255,255,255);

    }


};


class GameBoard {

    public:
        vector<unique_ptr<Zone>> mainZones; 
        vector<unique_ptr<Zone>> spellTrapZones;
        unique_ptr<Zone> fieldZone;
        unique_ptr<Zone> extraDeckZone;
        unique_ptr<Zone> deckZone;
        unique_ptr<Zone> graveyardZone;

        GameBoard() {
            // Initialize zones without setting their parameters
            for (int i = 0; i < 5; ++i) {
                mainZones.push_back(std::make_unique<Zone>());
                spellTrapZones.push_back(std::make_unique<Zone>());
            }
            fieldZone = std::make_unique<Zone>();
            extraDeckZone = std::make_unique<Zone>();
            deckZone = std::make_unique<Zone>();
            graveyardZone = std::make_unique<Zone>();
        }


    void setup() {
        // Set up your board based on some fixed dimensions
        float cardWidth = 100;
        float cardHeight = 175;
        float xOffset = 50;
        float yOffset = 50;
        float padding = 10;

        // Assuming the window size is fixed or this is called every time the window is resized
        float windowWidth = ofGetWidth();
        float windowHeight = ofGetHeight();

        // Define yOffset for the first row of cards (Main Monster Zones)
        yOffset = windowHeight / 2 - (cardHeight + padding) - cardHeight / 2;

        // Set up main monster card zones
        for (int i = 0; i < 5; ++i) {
            mainZones[i]->setParameters(xOffset + i * (cardWidth + padding), yOffset, cardWidth, cardHeight);
        }

        // Define yOffset for the second row of cards (Spell & Trap Zones)
        yOffset = windowHeight / 2 + padding;

        // Set up spell and trap card zones
        for (int i = 0; i < 5; ++i) {
            spellTrapZones[i]->setParameters(xOffset + i * (cardWidth + padding), yOffset, cardWidth, cardHeight);
        }

        // Set up Field Zone, Extra Deck, Deck, and Graveyard (GY)
        // You'll need to adjust the xOffsets for each of these to align with your game's layout
        fieldZone->setParameters(xOffset, yOffset - 2 * (cardHeight + padding), cardWidth, cardHeight);
        extraDeckZone->setParameters(windowWidth - xOffset - cardWidth, yOffset - 2 * (cardHeight + padding), cardWidth, cardHeight);
        deckZone->setParameters(windowWidth - xOffset - cardWidth, windowHeight / 2 + (cardHeight + padding), cardWidth, cardHeight);
        graveyardZone->setParameters(windowWidth - xOffset - 2 * (cardWidth + padding), windowHeight / 2 + (cardHeight + padding), cardWidth, cardHeight);
    }


        void draw(){
            for(auto& zone : mainZones){
                zone->draw();
            }

            for(auto& zone : spellTrapZones){
                zone->draw();
            }
            // Draw the Field Zone, Extra Deck, Deck, and Graveyard
            fieldZone->draw();
            extraDeckZone->draw();
            deckZone->draw();
            graveyardZone->draw();
        }



        // GameBoard() {}
        // void setup(){
        //     float screenRatioWidth = ofGetWidth() / 800.0; // Assuming 800 is the base width you designed for
        //     float screenRatioHeight = ofGetHeight() / 600.0; // Assuming 600 is the base height
        //     float cardWidth = 100 * screenRatioWidth; // Scale card width
        //     float cardHeight = 140 * screenRatioHeight; // Scale card height
        //     float xOffset = 50 * screenRatioWidth; // Scale starting x position
        //     float yOffset = 50 * screenRatioHeight; // Scale starting y position
        //     float padding = 40 * screenRatioWidth; // Scale space between cards
        //     // Set up main monster card zones
        //     for (int i = 0; i < 5; ++i) {
        //         mainZones.push_back(make_unique<Zone>(xOffset + i * (cardWidth + padding), yOffset, cardWidth, cardHeight));
        //     }
        //     // Set up spell and trap card zones below the main monster card zones
        //     for (int i = 0; i < 5; ++i) {
        //         spellTrapZones.push_back(make_unique<Zone>(xOffset + i * (cardWidth + padding), yOffset + cardHeight + padding, cardWidth, cardHeight));
        //     }
        // };

        
        // vector<Zone>& getZones() {
        //     vector<Zone> zones = mainZones;
        //     zones.insert(zones.end(), spellTrapZones.begin(), spellTrapZones.end());
        //     return zones;
        // }


};