#define REG_DISPCTRL *(unsigned short*) 0X4000000

//General
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char s8;
typedef short s16;
typedef int s32;

//Color
#define COLOR(r, g, b) (((r) & 0x1F) | (((g) & 0x1F) << 5) | (((b) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0)
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)


#define BG2_ENABLE (1 << 10)
#define MODE3 3

//Input
#define BUTTONS         *(volatile unsigned short*) 0x4000130
#define BUTTON_A        (1 << 0)
#define BUTTON_B        (1 << 1)
#define BUTTON_SELECT   (1 << 2)
#define BUTTON_START    (1 << 3)
#define BUTTON_RIGHT    (1 << 4)
#define BUTTON_LEFT     (1 << 5)
#define BUTTON_UP       (1 << 6)
#define BUTTON_DOWN     (1 << 7)
#define BUTTON_R        (1 << 8)
#define BUTTON_L        (1 << 9)
#define KEY_DOWN(key)   (~(BUTTONS) & key)

//Interrupts?
#define REG_DISPCNT     *(unsigned short*) 0x4000000
#define SCANLINECOUNTER  *(unsigned short*) 0x4000006

//consts
#define GB_WIDTH    240
#define GB_HEIGHT   160

unsigned short *videoBuffer = (unsigned short*) 0x6000000;
