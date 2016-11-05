// Constants
#define PLAYER_WIDTH    8
#define PLAYER_HEIGHT   8
#define MOVESPEED_X     2
#define MOVESPEED_Y     1
#define MAX_SHIELD      100
#define PLAYER_LIVES    5

#define MAX_BULLETS     4
#define MAX_MISSILES    1
#define BULLET_WIDTH    2
#define BULLET_HEIGHT   2

#define BOUNDARY_HEIGHT  2

#define GAME_WIDTH      224
#define GAME_HEIGHT     160

//macros
#define KEY_PRESSED(key)  (~(~(inputOld) & (key)) & (~(inputNew) & (key)))

extern unsigned short inputOld;
extern unsigned short inputNew;
extern int computerDestination;

typedef enum Boolean {
    FALSE,
    TRUE
} Boolean;

typedef enum PlayerType {
    HUMAN,
    COMPUTER
} PlayerType;


typedef struct Bullet {
    int x;
    int y;
    int speed;
    Boolean exists;
} Bullet;

typedef struct Player {
    int x;
    int y;
    int deltaX;
    int deltaY;
    int lives;
    int shield;
    Boolean shieldOn;
    PlayerType type;
} Player;

enum GameState {
    START_SCREEN,
    START_ANIMATION,
    PLAY,
    PAUSE,
    VICTORY,
    DEFEAT
};

extern enum GameState state;
