// Game logic
// Name: Jesse Huang

#include "renderer.c"

enum GameState state;
int computerDestination;

void movePlayer(Player *player, int minX, int minY, int maxX, int maxY) {
    int x = player->x;
    int y = player->y;
    int dx = player->deltaX;
    int dy = player->deltaY;

    if (x + dx + PLAYER_WIDTH < maxX && x + dx > minX) {
        player->x += dx;
    } else {
        player->deltaX = 0;
    }

    if (y + dy + PLAYER_HEIGHT < maxY && y + dy > minY) {
        player->y += dy;
    } else {
        player->deltaY = 0;
    }
}

void updateHumanShield(Player *player) {
   if ((KEY_DOWN(BUTTON_R) || KEY_DOWN(BUTTON_L)) && player->shield > 0) {
        player->shield -= 2;
        player->shieldOn = TRUE;
   } else {
       if (player->shield < MAX_SHIELD) {
           player->shieldOn = FALSE;
           player->shield++;
       }
   }
}

void checkCollisionEvent(Player *player, Bullet *bullets[]) {
    for (int i = 0; i < MAX_BULLETS + MAX_MISSILES; i++) {
        Bullet *bullet = bullets[i];
        if (bullet->exists == TRUE) {
            //Check collision
           
            if (bullet->x < player->x + PLAYER_WIDTH &&
                    bullet->y < player->y + PLAYER_HEIGHT &&
                    bullet->x + BULLET_WIDTH > player->x &&
                    bullet->y + BULLET_HEIGHT > player->y) {
                //Collision Detected
                if (player->shieldOn == FALSE) {
                    player->lives--;
                }
                //erase bullet
                eraseProjectile(*bullet);
                bullet->exists = FALSE;
            }
        }
    }

    if (player->lives < 1) {
        if (player->type == HUMAN) {
            //GAME OVER
            state = DEFEAT;
        } else {
            //YOU WIN
            state = VICTORY;
        }
    }
}

void updateComputerMovement(Player *computer, int level) {
    switch (level) {
        default:
        case 1:
            if (computer->x <= 20) {    
                computer->deltaX = 1;
            } else if (computer->x >= GAME_WIDTH - 20) {
                computer->deltaX = -1;
            }

            if (computer->deltaX == 0) {
                computer->deltaX = 1;
            }


        
            movePlayer(computer, -1, -1, GAME_WIDTH, (GAME_HEIGHT - BOUNDARY_HEIGHT) / 2);
            break;
        case 2:
            if (abs(computerDestination - computer->x) < MOVESPEED_X) {
                computerDestination = rand() % (GAME_WIDTH - PLAYER_WIDTH);
            } else if (computerDestination > computer->x) {
                computer->deltaX = MOVESPEED_X;
            } else if (computerDestination < computer->x) {
                computer->deltaX = -MOVESPEED_X;
            }
            movePlayer(computer, -1, -1, GAME_WIDTH, (GAME_HEIGHT - BOUNDARY_HEIGHT) / 2);

            break;
    }
}

void updateBulletMovement(Bullet *bullets[]) {
    for (int i = 0; i < MAX_BULLETS + MAX_MISSILES; i++) {
        Bullet *bullet;
        bullet = bullets[i];
        if (bullet->exists == TRUE) {
             bullet->y += bullet->speed;
     
             //Check if off screen
             if (bullet->y + BULLET_HEIGHT < -1 || bullet->y > GB_HEIGHT) {
                eraseProjectile(*bullet);
                bullet->exists = FALSE;
             }
        }
    }
}

void resetPlayer(Player *player) {
    erasePlayer(*player);
    player->lives = 5;
    player->x = GAME_WIDTH / 2 - PLAYER_WIDTH;
    player->shield = MAX_SHIELD;
    player->deltaY = 0;

    if (player->type == HUMAN) {
        player->y = GAME_HEIGHT - PLAYER_HEIGHT;
        player->deltaX = 0;
    } else {
        player->y = 0;
        player->deltaX = 1;
    }
}

void resetBullets(Bullet *bullets[]) {
    for (int i = 0; i < MAX_BULLETS + MAX_MISSILES; i++) {
        eraseProjectile(*bullets[i]);
        bullets[i]->exists = FALSE;
    }
}
