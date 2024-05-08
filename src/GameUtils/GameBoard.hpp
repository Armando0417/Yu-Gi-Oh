#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPanel.h"
#include "ofParameter.h"
#include "Card.hpp"
#include "Player.hpp"


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

enum PlayerID {
    TOP_PLAYER,
    BOTTOM_PLAYER
};

struct Zone {
    int xPos;
    int yPos;
    int cardWidth;
    int cardHeight;
    bool selected;
    unique_ptr<Card> card;
    PlayerID playerID; // Added to indicate which player owns the card in this zone

    // Constructor doesn't set positions and sizes anymore, just initializes them
    Zone() : xPos(0), yPos(0), cardWidth(0), cardHeight(0), selected(false), card(nullptr), playerID(BOTTOM_PLAYER) {}

    Zone(int x, int y, int w, int h, PlayerID player) : xPos(x), yPos(y), cardWidth(w), cardHeight(h), selected(false), card(nullptr), playerID(player) {}
    

    void setParameters(float x, float y, float w, float h) {
        xPos = x;
        yPos = y;
        cardWidth = w;
        cardHeight = h;
    }

    bool isTaken() const {
        return card != nullptr;
    }

    void checkZone(int x, int y) {
        if( x >= xPos && x <= xPos + cardWidth && y >= yPos && y <= yPos + cardHeight) {
            selected = true;
        }
        else{
            selected = false;
        }
    }

 


    void draw() {
        if (isTaken()) {
            ofFill();
            ofSetColor(255, 255, 0);  // Yellow fill if taken
        }
        if (selected) {
            ofNoFill();
            ofSetLineWidth(2);       // Thicker line for visibility
            ofSetColor(255, 0, 0);   // Red border if selected
        } 
        else {
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
        PlayerID owner;
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

        GameBoardGui() : owner(BOTTOM_PLAYER) {}
        GameBoardGui(PlayerID player) : owner(player) {}

        void setup();

        void update();

        void renderBoard();

        bool isZoneAvailable(ZoneType z) { return !zones[z].isTaken(); }

    
        void battleBetweenZones (ZoneType attacker, ZoneType defender);

        void drawPlayerHand(const Player& player);

};
