// HW09 Gameboy Game
// Name: Jesse Huang
#include "myLib.h"
#include "consts.h"
#include "draw.c"
#include "input.c"
#include <stdlib.h>

//Image files
#include "resources/start.h"
#include "resources/pause.h"
#include "resources/victory.h"
#include "resources/defeat.h" 


#define ANIMATION_SPEED     2


void startScreen();
void endStartScreen();

int startAnimation(int counter);
void exitStartAnimation();

void pauseScreen();
void endPauseScreen();

void playScreen(Player *player, Player *computer, Bullet *playerBullets[], Bullet *computerBullets[]);
void updateBulletMovement(Bullet *bullets[]);
void endPlayScreen();

void defeatScreen();
void endDefeatScreen();

void victoryScreen();
void endVictoryScreen();

void waitForVBlank();


unsigned short inputOld;
unsigned short inputNew;

enum GameState state;

int computerDestination;

int main() {

    REG_DISPCTRL = MODE3 | BG2_ENABLE;

    state = START_SCREEN;

    //Taking in input
    inputOld = 0;
    inputNew = BUTTONS;
    

    //Player bullets
    Bullet *playerBullets[MAX_BULLETS + MAX_MISSILES];

    //Computer bullets
    Bullet *computerBullets[MAX_BULLETS + MAX_MISSILES];

    //Game loop
    //Creating player
    Player player = {GAME_WIDTH / 2 - PLAYER_WIDTH, GB_HEIGHT - PLAYER_HEIGHT, 0, 0, PLAYER_LIVES, MAX_SHIELD, FALSE, HUMAN};

    //Creating Computer
    Player computer = {GAME_WIDTH / 2 - PLAYER_WIDTH, 0, 0, 0, PLAYER_LIVES, MAX_SHIELD, FALSE, COMPUTER};

    int seed = 0;
    int counter = 1;


    while(1) {
        waitForVBlank();
    
        //Checks state, then goes to the appropriate method
        switch(state) {
        case START_SCREEN:
            startScreen();
            seed++;
            
            if (KEY_PRESSED(BUTTON_START)) {
                state = START_ANIMATION;
                endStartScreen();
                resetPlayer(&player);
                resetPlayer(&computer);
                resetBullets(playerBullets);
                resetBullets(computerBullets);

                srand(seed);
                computerDestination = GAME_WIDTH / 2;
            }

            break;

        case START_ANIMATION:
            if(startAnimation(counter)) {
                counter = 1;
                state = PLAY;
                exitStartAnimation();
            }
            counter += ANIMATION_SPEED;
            break;
        
        case PLAY:
            playScreen(&player, &computer, playerBullets, computerBullets);

            if (KEY_PRESSED(BUTTON_START)) {
                state = PAUSE;
            }

            if (KEY_PRESSED(BUTTON_SELECT)) {
                state = START_SCREEN;
            }
            break;

        case PAUSE:
    
            pauseScreen();

            if (KEY_PRESSED(BUTTON_START)) {
                state = PLAY;
                endPauseScreen();
            }
            if (KEY_PRESSED(BUTTON_SELECT)) {
                state = START_SCREEN;
            }
            break;

        case VICTORY:
            victoryScreen();
            if (KEY_PRESSED(BUTTON_START)) {
                state = START_SCREEN;
                endVictoryScreen();
            }
            if (KEY_PRESSED(BUTTON_SELECT)) {
                state = START_SCREEN;
            }
            break;
        case DEFEAT:
            defeatScreen();
            if (KEY_PRESSED(BUTTON_START)) {
                state = START_SCREEN;
                endDefeatScreen();
            }
            if (KEY_PRESSED(BUTTON_SELECT)) {
                state = START_SCREEN;
            }
            break;
        } // END SWITCH

        inputOld = inputNew;
        inputNew = BUTTONS;

    }
    return 0;
}


void startScreen() {
    drawImage(0, 0, START_WIDTH, START_HEIGHT, start);
    drawString(150, 100, "Press", BLACK);
    drawString(175, 110, "Start", BLACK);
}

void endStartScreen() {
    drawRect(0, 0, GB_WIDTH, GB_HEIGHT, BLACK);
}

int startAnimation(int counter) {
    return animateToImage(counter, victory, start);
    //return animateToBlack(counter, start);
}

void exitStartAnimation() {
    eraseImage(0, 0, START_WIDTH, START_HEIGHT);
}

void playScreen(Player *player, Player *computer, Bullet *playerBullets[], Bullet *computerBullets[]) {
    //Player input control
    updatePlayerMovement(player);   
    updateComputerMovement(computer, 2);

    //Player bullet control
    updateBulletMovement(playerBullets);
    updatePlayerBulletCreation(playerBullets, *player);

    //Computer bullet control
    updateBulletMovement(computerBullets);
    updateComputerBulletCreation(computerBullets, *computer);

    //Update shield info
    updateHumanShield(player);

    //Check collisions and lives
    checkCollisionEvent(player, computerBullets);
    checkCollisionEvent(computer, playerBullets);

    //Draw bullets
    eraseBullets(playerBullets);
    eraseBullets(computerBullets);
    drawBullets(playerBullets);
    drawBullets(computerBullets);
    drawMissiles(playerBullets);
    drawMissiles(computerBullets);

    //Draw player
    erasePlayer(*player);
    drawPlayer(*player);

    //Draw Computer
    erasePlayer(*computer);
    drawPlayer(*computer);

    //Draw HUD
    drawHUD(player->lives, computer->lives);

    //Draw boundary
    drawBoundary();
}


void pauseScreen() {
    videoBuffer[0] = WHITE;
    drawImageCentered(PAUSE_WIDTH, PAUSE_HEIGHT, pause);
}

void endPauseScreen() {
    eraseImageCentered(PAUSE_WIDTH, PAUSE_HEIGHT);
}

void victoryScreen() {
    drawImageCentered(VICTORY_WIDTH, VICTORY_HEIGHT, victory);
    drawString(150, 100, "Press", BLACK);
    drawString(175, 110, "Start", BLACK);
}

void endVictoryScreen() {
    eraseImageCentered(VICTORY_WIDTH, VICTORY_HEIGHT);
}

void defeatScreen() {
    drawImageCentered(DEFEAT_WIDTH, DEFEAT_HEIGHT, defeat);
    drawString(150, 110, "Game", RED);
    drawString(175, 120, "Over", RED);
}

void endDefeatScreen() {
    eraseImageCentered(DEFEAT_WIDTH, DEFEAT_HEIGHT);
}


void waitForVBlank() {
    while (SCANLINECOUNTER >= 160);
    while (SCANLINECOUNTER < 160);
}
