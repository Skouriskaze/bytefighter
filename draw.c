#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "resources/fonts/standard.h"

#define OFFSET(x, y)    (x) + (y) * GB_WIDTH

#define NUM_CHARS       59

#define DMA_ON                  (1 << 31)
#define DMA_SOURCE_INCREMENT    (0 << 23)
#define DMA_SOURCE_DECREMENT    (1 << 23)
#define DMA_SOURCE_FIXED        (2 << 23)

#define DMA     ((volatile DMA_REC *)0X40000B0)

typedef struct {
    const volatile void* src;
    volatile void* dest;
    u32 cnt;
} DMA_REC;


void drawRect(int x, int y, int width, int height, const u16 color) {
    volatile u16 fixedColor = color;
   for (int i = 0; i < height; i++) {
       DMA[3].cnt = 0;
       DMA[3].src = &fixedColor;
       DMA[3].dest = videoBuffer + OFFSET(x, i + y);
       DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | width;
   }
}

void drawImage(int x, int y, int width, int height, const u16 *image) {
    for (int i = 0; i < height; i++) {
        DMA[3].cnt = 0;
        DMA[3].src = image + i * width;
        DMA[3].dest = videoBuffer + OFFSET(x, i + y);
        DMA[3].cnt = DMA_ON | width;
    }
}

void drawPartialImage(int x, int y, int width, int height, int startX, int desWidth, const u16 *image) {
    for (int i = 0; i < height; i++) {
        DMA[3].cnt = 0;
        DMA[3].src = image + i * width + startX;
        DMA[3].dest = videoBuffer + OFFSET(x, i + y);
        DMA[3].cnt = DMA_ON | desWidth;
    }
}

void eraseImage(int x, int y, int width, int height) {
    volatile u16 color = BLACK;
    for (int i = 0; i < height; i++) {
        DMA[3].cnt = 0;
        DMA[3].src = &color;
        DMA[3].dest = videoBuffer + OFFSET(x, y + i);
        DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | width;
    }
}

void drawImageCentered(int width, int height, const u16* image) {
    drawImage((GB_WIDTH  - width) / 2, (GB_HEIGHT - height) / 2, width, height, image);
}

void eraseImageCentered(int width, int height) {
    eraseImage((GB_WIDTH  - width) / 2, (GB_HEIGHT - height) / 2, width, height);
}

void clearScreen() {
    eraseImage(0, 0, GB_WIDTH, GB_HEIGHT);
}

void drawChar(int x, int y, char letter, u16 color) {
    int index = letter - 32;
    for (int j = 0; j < STANDARD_HEIGHT; j++) {
        for (int i = 0; i < STANDARD_WIDTH / NUM_CHARS; i++) {
            u16 source = *(standard + (index * 8) + i + (j * STANDARD_WIDTH));
            if (source == 0x0000) {
                videoBuffer[OFFSET(x + i, y + j)] = color;
            }
        }
    }
}

void drawString(int x, int y, char message[], u16 color) {
    for (unsigned int i = 0; i < strlen(message); i++) { 
        message[i] = toupper(message[i]);
        drawChar(x + 8 * i, y, message[i], color);
    }
}

