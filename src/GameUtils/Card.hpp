#pragma once
#include "ofMain.h"


enum CardType {
    MONSTER,
    SPELL,
    TRAP,
};

enum MonsterType {
    NORMAL, 
    FUSION, 
    SYNCHRO, 
};

    /*
        Effects:
            - Destroy a card on the field
            - Add a card from deck to hand / graveyard to hand
            - Increase atk
            - Decrease atk 
    */


   enum EffectType {
        INCREASE_ATK,
        DECREASE_ATK,
        INCREASE_DEF,
        DECREASE_DEF,
        DESTROY_TARGET,
        ADD_CARD
   };

    struct CardEffect {
        EffectType type;
        int magnitude;
        int duration;

        CardEffect() = default;
        CardEffect(EffectType t, int mag, int dur) : type(t), magnitude(mag), duration(dur) {}
    };


class Card {
    protected:
        string name;
        CardType type;
        string effectDescription;
        bool isDestroyed;
        ofImage cardImage;
        unique_ptr<CardEffect> effect;



    public:
        Card(string n, CardType t, string e, ofImage img, unique_ptr<CardEffect> eff = nullptr) 
            : name(n), type(t), effectDescription(e), isDestroyed(false), cardImage(img), effect(move(eff)) {}
        // Move Constructor
        
        Card(Card&& other) noexcept
            : name(std::move(other.name)), effect(std::move(other.effect)) {}


        void drawCard(int x, int y, int cardWidth, int cardHeight) {
            if (cardImage.isAllocated()) {
                cardImage.draw(x, y, cardWidth, cardHeight);
            }
            // Reset color after drawing
            ofSetColor(255, 255, 255);
        }
        // Move Assignment Operator
        Card& operator=(Card&& other) noexcept {
            if (this != &other) {
                name = std::move(other.name);
                effect = std::move(other.effect);
            }
            return *this;
        }
        // Delete the copy constructor and copy assignment operator to prevent copying
        Card(const Card&) = delete;
        Card& operator=(const Card&) = delete;

        // Example method
        void print() const {
            std::cout << "Card Name: " << name << std::endl;
        }





        virtual int getATK() { return 0; }
        virtual int getDEF() { return 0; }
        virtual ~Card() = default;
        virtual void activate() {} 

        void destroy() { isDestroyed = true; }
        bool wasDestroyed() { return isDestroyed; }

        string printCard() {
            if (type == MONSTER) {
                return "This card is: " + name + " and is a " + "MONSTER";
            }
            if (type == SPELL) {
                return "This card is: " + name + " and is a " + "SPELL";
            }
            else 
                return "This card is: " + name + " and is a " + "TRAP";
        }
};

/*
    Note from Author:
        - By default when making a monster, the "tuner" flag will be false by default. This is by design to not make the constructors too flooded with params.
            after making a monster card, just use the makeTuner() method right after to turn the monster into a tuner.
*/

class MonsterCard: public Card{
    protected: 
        int starLevel; 
        int attack; 
        int defense; 
        MonsterType monsterType; 
        bool tuner;

    public: 
        // Default non-effect monster constructor. Use this constructor if you want to make a regular non-effect monster card
            MonsterCard(string n, int stars, int atk, int def, ofImage img)
                : Card(n, MONSTER, "", img), 
                starLevel(stars), 
                attack(atk), 
                defense(def), 
                monsterType(NORMAL), 
                tuner(false) {}

            MonsterCard(string n, int stars, int atk, int def, MonsterType mType, string effect, ofImage img, unique_ptr<CardEffect> eff = nullptr)
                : Card(n, MONSTER, effect, img, move(eff)),
                starLevel(stars), 
                attack(atk), 
                defense(def), 
                monsterType(mType), 
                tuner(false) {}
                
        CardType getCardType() { return type; } 
        MonsterType getMonsterType() { return monsterType; }

        void makeTuner() {tuner = true;}

        int getATK() override { return attack; }
        int getDEF() override { return defense; }



        void activate() override {
        
            return; 
        }
};

class TrapCard : public Card {
    public: 
        TrapCard(string n, string e, ofImage img, unique_ptr<CardEffect> eff = nullptr)
                : Card(n, TRAP, e, img, move(eff)) {}
        
        void activate() override {
            // Activation logic here
        }
};

class SpellCard : public Card {
    public: 
        SpellCard(string n, string e, ofImage img, unique_ptr<CardEffect> eff = nullptr)
            : Card(n, SPELL, e, img, move(eff)) {}
    
        void activate() override {
            // Basic Spell activation logic
            // For example, "Increase player's life points by 500"
        }
};

class FusionMonsterCard : public MonsterCard {
    public:
        FusionMonsterCard(string name, int stars, int atk, int def, string effect, ofImage img, unique_ptr<CardEffect> eff = nullptr)
            : MonsterCard(name, stars, atk, def, FUSION, effect, img, move(eff)) {}

        void activate() override {
            // Fusion monster-specific activation logic
            // For example, "Can only be summoned by fusing two specific monsters"
        }
};

class SynchroMonsterCard : public MonsterCard {
    public:
        SynchroMonsterCard(string name, int stars, int atk, int def, string effect, ofImage img, unique_ptr<CardEffect> eff = nullptr)
            : MonsterCard(name, stars, atk, def, SYNCHRO, effect, img, move(eff)) {}

        void activate() override {
            // Synchro monster-specific activation logic
            // For example, "Can be summoned using one Tuner and one or more non-Tuner monsters"
        }
};