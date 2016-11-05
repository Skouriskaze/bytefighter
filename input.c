// Input controller
// Name: Jesse Huang

#include <stdlib.h>

#include "gamelogic.c"


void updatePlayerBulletCreation(Bullet *bullets[], Player player) {
    if (KEY_PRESSED(BUTTON_A)) {
        int index = 0;
        while (index < MAX_BULLETS && bullets[index]->exists == TRUE) {
            index++;
        }

        if (index != MAX_BULLETS) {
            Bullet *bullet = malloc(sizeof(Bullet));
            bullet->x = player.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
            bullet->y = player.y + BULLET_HEIGHT;
            bullet->speed = -2;
            bullet->exists = TRUE;
            bullets[index] = bullet;
        }

    } else if (KEY_PRESSED(BUTTON_B)) {
       int index = MAX_BULLETS;
       while (index < MAX_BULLETS + MAX_MISSILES && bullets[index]->exists == TRUE) {
            index++;
       }

       if (index != MAX_BULLETS + MAX_MISSILES) {
            Bullet *bullet = malloc(sizeof(Bullet));
            bullet->x = player.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
            bullet->y = player.y;
            bullet->speed = -4;
            bullet->exists = TRUE;
            bullets[index] = bullet; 
       }
    }
}

void updateComputerBulletCreation(Bullet *bullets[], Player player) {
    int r = rand() % 10;

    if (r == 1) {
        int index = 0;
        while (index < MAX_BULLETS && bullets[index]->exists == TRUE) {
            index++;
        }
        //create slow bullet 
        if (index != MAX_BULLETS) {
            Bullet *bullet = malloc(sizeof(Bullet));
            bullet->x = player.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
            bullet->y = player.y + PLAYER_HEIGHT;
            bullet->speed = 2;
            bullet->exists = TRUE;
            bullets[index] = bullet;
        } 
    } else if (r == 2) {
        int index = MAX_BULLETS;
        while (index < MAX_BULLETS + MAX_MISSILES && bullets[index]->exists == TRUE) {
            index++;
        }
        //create fast bullet
       if (index != MAX_BULLETS + MAX_MISSILES) {
            Bullet *bullet = malloc(sizeof(Bullet));
            bullet->x = player.x + PLAYER_WIDTH / 2 - BULLET_WIDTH / 2;
            bullet->y = player.y + PLAYER_HEIGHT;
            bullet->speed = 4;
            bullet->exists = TRUE;
            bullets[index] = bullet;
        } 
    }
}

void updatePlayerMovement(Player *player) {
    // Clearing delta
    player->deltaX = 0;
    player->deltaY = 0;

    //Check input
    if (KEY_DOWN(BUTTON_DOWN)) {
        player->deltaY = MOVESPEED_Y;
    }
    if (KEY_DOWN(BUTTON_UP)) {
        player->deltaY = -MOVESPEED_Y;
    }
    if (KEY_DOWN(BUTTON_LEFT)) {
        player->deltaX = -MOVESPEED_X;
    }
    if (KEY_DOWN(BUTTON_RIGHT)) {
        player->deltaX = MOVESPEED_X;
    }

    movePlayer(player, -1, (GAME_HEIGHT + BOUNDARY_HEIGHT) / 2, GAME_WIDTH, GAME_HEIGHT);

}
