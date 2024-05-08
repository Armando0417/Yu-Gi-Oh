class GameStateManager {
    public:
        /*
            Note from author: 
                The progression of phases are as follows:
                    DRAW_PHASE -> MAIN_PHASE_1 -> BATTLE_PHASE -> MAIN_PHASE_2 -> END_PHASE -> DRAW_PHASE
        */
        enum GameState {
            DRAW_PHASE_TOP_PLAYER,
            MAIN_PHASE_1_TOP_PLAYER,
            BATTLE_PHASE_TOP_PLAYER,
            MAIN_PHASE_2_TOP_PLAYER,
            END_PHASE_TOP_PLAYER,


            DRAW_PHASE_BOT_PLAYER,
            MAIN_PHASE_1_BOT_PLAYER,
            BATTLE_PHASE_BOT_PLAYER,
            MAIN_PHASE_2_BOT_PLAYER,
            END_PHASE_BOT_PLAYER
        };

    private:
        GameState currentState;

    public:
        GameStateManager() : currentState(DRAW_PHASE_TOP_PLAYER) {}

        void nextPhase() {
            switch (currentState) {
                //Phases for the top PLAYER                
                case DRAW_PHASE_TOP_PLAYER : currentState = MAIN_PHASE_1_TOP_PLAYER; break;
                case MAIN_PHASE_1_TOP_PLAYER : currentState = BATTLE_PHASE_TOP_PLAYER; break;
                case BATTLE_PHASE_TOP_PLAYER : currentState = MAIN_PHASE_2_TOP_PLAYER; break;
                case MAIN_PHASE_2_TOP_PLAYER : currentState = END_PHASE_TOP_PLAYER; break;
                case END_PHASE_TOP_PLAYER : currentState = DRAW_PHASE_BOT_PLAYER; break; //Start the other player's turn 

                //Phases for the bot PLAYER
                case DRAW_PHASE_BOT_PLAYER : currentState = MAIN_PHASE_1_BOT_PLAYER; break;
                case MAIN_PHASE_1_BOT_PLAYER : currentState = BATTLE_PHASE_BOT_PLAYER; break;
                case BATTLE_PHASE_BOT_PLAYER : currentState = MAIN_PHASE_2_BOT_PLAYER; break;
                case MAIN_PHASE_2_BOT_PLAYER : currentState = END_PHASE_BOT_PLAYER; break;

            // This is going to keep the loop going
                case END_PHASE_BOT_PLAYER : currentState = DRAW_PHASE_TOP_PLAYER; break; 
                
            }
        }

        GameState getCurrentState() const { return currentState; }
};
