// Renderer draws images
// Name: Jesse Huang

#include "resources/life.h"
#include "resources/dead.h"
#include "resources/human.h"
#include "resources/computer.h"

void drawProjectile(Bullet bullet, unsigned short color);
void eraseProjectile(Bullet bullet);

void drawBullets(Bullet *bullets[]) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet bullet;
        bullet = *bullets[i];
        drawProjectile(bullet, WHITE);
    }
    
}

void drawMissiles(Bullet *bullets[]) {
    for (int i = MAX_BULLETS; i < MAX_BULLETS + MAX_MISSILES; i++) {
        Bullet bullet;
        bullet = *bullets[i];
        drawProjectile(bullet, GREEN);

    }
}

void eraseBullets(Bullet *bullets[]) {
    for (int i = 0; i < MAX_BULLETS+ MAX_MISSILES; i++) {
        Bullet bullet;
        bullet = *bullets[i];
        eraseProjectile(bullet);
    }
}

void drawProjectile(Bullet bullet, unsigned short color) {
    if (bullet.exists == TRUE) {
        drawRect(bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT, color);
    }
}

void eraseProjectile(Bullet bullet) {
    if (bullet.exists == TRUE) {
        drawRect(bullet.x, bullet.y - bullet.speed, BULLET_WIDTH, BULLET_HEIGHT, BLACK);
    }
}

void erasePlayer(Player player) {
    drawRect(player.x - player.deltaX, player.y - player.deltaY, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK); 

    drawRect(player.x - 4 - player.deltaX, player.y - player.deltaY, 2, PLAYER_HEIGHT, BLACK); 

}
void drawPlayer(Player player) {
    if (player.type == HUMAN) {
        //Draw current player
        drawImage(player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT, human);

    } else if (player.type == COMPUTER) {
        drawImage(player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT, computer);
    }

    int shieldLength = PLAYER_HEIGHT * player.shield / MAX_SHIELD;
    drawRect(player.x - 4, player.y, 2, shieldLength, CYAN); 

}

void drawComputerHearts(int lives) {
    for (int i = 0; i < lives; i++) {
        drawImage(GAME_WIDTH, LIFE_HEIGHT * i, LIFE_WIDTH, LIFE_HEIGHT, life);
    }
    for (int i = lives; i < PLAYER_LIVES; i++) {
        drawImage(GAME_WIDTH, LIFE_HEIGHT * i, DEAD_WIDTH, DEAD_HEIGHT, dead);
    }
}

void drawPlayerHearts(int lives) {
    for (int i = 0; i < lives; i++) {
        drawImage(GAME_WIDTH, GAME_HEIGHT - LIFE_HEIGHT * (i + 1), LIFE_WIDTH, LIFE_HEIGHT, life);
    }
    for (int i = lives; i < PLAYER_LIVES; i++) {
        drawImage(GAME_WIDTH, GAME_HEIGHT - LIFE_HEIGHT * (i + 1), DEAD_WIDTH, DEAD_HEIGHT, dead);
    }
}

void drawHUD(int humanLives, int computerLives) {
    drawRect(GAME_WIDTH, 0, 16, GB_HEIGHT, MAROON);

    drawComputerHearts(computerLives);
    drawPlayerHearts(humanLives);
    
}

void drawBoundary() {
    drawRect(0, (GAME_HEIGHT - BOUNDARY_HEIGHT) / 2, GB_WIDTH, BOUNDARY_HEIGHT, GREY);
}

int animateToBlack(int counter, const u16 *image) {
    if (counter >= 1 && counter < 240) {
        drawRect(0, 0, counter, GB_HEIGHT, BLACK);
        drawPartialImage(counter, 0, GB_WIDTH, GB_HEIGHT, 0, GB_WIDTH - counter, image);
        return 0;
    }
    return 1;
}

int animateToImage(int counter, const u16 *firstImage, const u16 *secondImage) {
    if (counter >= 1 && counter < 240) {
        drawPartialImage(0, 0, GB_WIDTH, GB_HEIGHT, counter, counter, secondImage);
        drawPartialImage(counter, 0, GB_WIDTH, GB_HEIGHT, 0, GB_WIDTH - counter, firstImage);
        return 0;
    }
    return 1;
    
}
