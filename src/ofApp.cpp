#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // board = make_unique<GameBoard>();
    // board->setup();
    // card = make_unique<MonsterCard>("test", 10, 1000, 1000, ofImage());
    // BottomBoard = make_unique<GameBoardGui>(PlayerID::BOTTOM_PLAYER);
    // TopBoard = make_unique<GameBoardGui>(PlayerID::TOP_PLAYER);
    // BottomBoard->setup();
    // TopBoard->setup(); 

    // if(BottomBoard->owner == PlayerID::BOTTOM_PLAYER) {
    //     std::cout << "Bottom player was set up correctly" << std::endl;
    // } 
    // if (TopBoard->owner == PlayerID::TOP_PLAYER) {
    //     std::cout << "Top player was set up correctly" << std::endl;
    // }

    gameManager = make_unique<GameManager>();


    deck = make_unique<DeckMaker>();
    deck->loadDeck("cards.csv");
    if(deck->deck.size() > 0) {
        std::cout << "Deck was loaded correctly" << std::endl;
    }
    deck->printDeck();
}

//--------------------------------------------------------------
void ofApp::update(){
    gameManager->update();

    // TopBoard->update();
    // BottomBoard->update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    // board->draw();

    // TopBoard->renderBoard();
    // BottomBoard->renderBoard();
    gameManager->renderGame();
    // for(auto & zone : guiBoard->zones) {

    // }


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    gameManager->mouseMoved(x, y);

    
    // for(auto & zone : TopBoard->zones) {
    //     zone.second.selected = (x >= zone.second.xPos 
    //                             && x < zone.second.xPos + zone.second.cardWidth 
    //                             && y >= zone.second.yPos 
    //                             && y < zone.second.yPos + zone.second.cardHeight);
    // }
    // for(auto & zone : BottomBoard->zones) {
    //     zone.second.selected = (x >= zone.second.xPos 
    //                             && x < zone.second.xPos + zone.second.cardWidth 
    //                             && y >= zone.second.yPos 
    //                             && y < zone.second.yPos + zone.second.cardHeight);
    // }


    
    
    // for (auto& zone : board->mainZones) {
    //     zone->selected = (x >= zone->xPos && x < zone->xPos + zone->cardWidth &&
    //                       y >= zone->yPos && y < zone->yPos + zone->cardHeight);
    // }

    // for (auto& zone : board->spellTrapZones) {
    //     zone->selected = (x >= zone->xPos && x < zone->xPos + zone->cardWidth &&
    //                       y >= zone->yPos && y < zone->yPos + zone->cardHeight);
    // }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == OF_MOUSE_BUTTON_LEFT) {
        gameManager->mousePressed(x, y);
    }

    // if (button == OF_MOUSE_BUTTON_LEFT) {
    //     for(auto & zoneEntry : guiBoard->zones) {
    //         Zone &zone = zoneEntry.second;
    //         std::cout << "Zone dimensions: " << zone.cardWidth << "x" << zone.cardHeight << std::endl;
    //         std::cout << "Zone position: " << zone.xPos << ", " << zone.yPos << std::endl;
    //         if (x >= zone.xPos && x < zone.xPos + zone.cardWidth &&
    //             y >= zone.yPos && y < zone.yPos + zone.cardHeight) {
    //             zone.taken = true;  // Force set to true
    //             std::cout << "Zone taken status changed to: " << zone.taken << std::endl;
    //             break;
    //         }
    //     }
    // }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
