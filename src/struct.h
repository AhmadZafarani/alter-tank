//YA RABB

#ifndef BP_PROJECT_STRUCT_H
#define BP_PROJECT_STRUCT_H


#define FPS 50
#define MAP_WIDTH 890
#define MAP_HEIGHT 700
#define step 5
#define EXITCODE 15
#define DELTA (M_PI / 10)
#define LENGTH 32
#define AMMO 20
#define LIFE 1000
#define RADIUS 30
#define MENUCODE 10
#define NEWGAME 122
#define TIMES 5
#define SAVECODE 110
#define LASERCODE1 119
#define LASERCODE2 120
#define LASERCODE11 118
#define LASERCODE22 117


typedef struct {
    double x, y;
    double angle;
    unsigned long int life;
} Bullet;

typedef struct {
    double x;
    double y;
    double angle;
    double XNoghtedovvom;
    double YNoghtedovvom;
    Bullet *bullets;
    unsigned short score;
} Tank;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
} Wall;

typedef struct {
    double x, y, angle;
    long int life;
} Laser;

typedef struct {
    Tank *tank, *tanking;
    Wall *wall;
    short n;
    Laser *laser;
} Map;


unsigned short i, k, xz, zx, damedasti;


#endif //BP_PROJECT_STRUCT_H
