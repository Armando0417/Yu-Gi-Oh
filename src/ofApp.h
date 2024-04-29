#pragma once

#include "ofMain.h"

// #include "Board.hpp"
#include "Card.hpp"
#include "GameBoard.hpp"
#include "DeckMaker.hpp"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
		// unique_ptr<GameBoard> board;
		unique_ptr<GameBoardGui> TopBoard;
		unique_ptr<GameBoardGui> BottomBoard;
		unique_ptr<Card> card;
		unique_ptr<DeckMaker> deck;


	// std::unique_ptr<MonsterCard> card;
    int selectedZoneIndex = -1; // -1 means no zone is selected
    bool isMainZone = true;  // To determine if the selected zone is in mainZones or spellTrapZones

};
