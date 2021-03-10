//YA BAGHER

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "struct.h"
#include "view.h"
#include "physics.h"
#include "logic.h"

Wall saved_walls1[22] = {
        {10,  5,   10,  691},
        {152, 103, 152, 201},
        {152, 299, 152, 397},
        {294, 201, 294, 299},
        {294, 397, 294, 593},
        {436, 201, 436, 299},
        {578, 201, 578, 299},
        {578, 495, 578, 593},
        {720, 397, 720, 593},
        {10,  5,   862, 5},
        {436, 103, 862, 103},
        {10,  201, 152, 201},
        {578, 201, 720, 201},
        {152, 299, 578, 299},
        {720, 299, 862, 299},
        {294, 397, 436, 397},
        {578, 397, 720, 397},
        {152, 495, 294, 495},
        {436, 495, 578, 495},
        {10,  593, 152, 593},
        {862, 5,   862, 691},
        {10,  691, 862, 691}
};

Wall saved_walls2[36] = {
        {10,  6,   10,  690},
        {106, 386, 106, 538},
        {202, 82,  202, 234},
        {202, 310, 202, 386},
        {298, 6,   298, 158},
        {298, 310, 298, 386},
        {298, 462, 298, 538},
        {394, 234, 394, 310},
        {394, 538, 394, 614},
        {490, 82,  490, 158},
        {490, 462, 490, 614},
        {586, 158, 586, 310},
        {586, 462, 586, 538},
        {586, 614, 586, 690},
        {682, 234, 682, 462},
        {682, 614, 682, 690},
        {778, 158, 778, 386},
        {778, 462, 778, 614},
        {10,  6,   874, 6},
        {394, 82,  778, 82},
        {10,  158, 106, 158},
        {298, 158, 394, 158},
        {586, 158, 874, 158},
        {106, 234, 490, 234},
        {10,  310, 298, 310},
        {490, 310, 586, 310},
        {298, 386, 394, 386},
        {490, 386, 586, 386},
        {106, 462, 202, 462},
        {394, 462, 490, 462},
        {586, 462, 778, 462},
        {202, 538, 394, 538},
        {682, 538, 778, 538},
        {106, 614, 394, 614},
        {874, 6,   874, 690},
        {10,  690, 874, 690}
};

Wall saved_walls3[31] = {
        {8,   6,   8,   692},
        {202, 496, 202, 594},
        {299, 6,   299, 104},
        {299, 300, 299, 398},
        {396, 104, 396, 300},
        {396, 398, 396, 496},
        {493, 300, 493, 398},
        {590, 6,   590, 104},
        {590, 202, 590, 300},
        {590, 398, 590, 496},
        {687, 104, 687, 202},
        {687, 300, 687, 398},
        {784, 202, 784, 300},
        {784, 398, 784, 496},
        {8,   6,   881, 6},
        {105, 104, 299, 104},
        {493, 104, 590, 104},
        {784, 104, 881, 104},
        {105, 202, 784, 202},
        {8,   300, 202, 300},
        {299, 300, 396, 300},
        {8,   398, 299, 398},
        {396, 398, 493, 398},
        {590, 398, 784, 398},
        {105, 496, 202, 496},
        {299, 496, 590, 496},
        {784, 496, 881, 496},
        {8,   594, 105, 594},
        {202, 594, 784, 594},
        {881, 6,   881, 692},
        {8,   692, 881, 692}
};

#ifdef main
#undef main
#endif /*main*/

int main(int argc, char *argv[]) {

    short n;
    Tank *tank_1 = (Tank *) malloc(sizeof(Tank) * 1);    //maghadir
    Tank *tank_2 = (Tank *) malloc(sizeof(Tank) * 1);
    Map *map = malloc(sizeof(Map) * 1);
    map->tank = tank_1;
    tank_1->bullets = (Bullet *) malloc(AMMO * sizeof(Bullet));
    map->tanking = tank_2;
    tank_2->bullets = (Bullet *) malloc(AMMO * sizeof(Bullet));
    char *tank1 = (char *) malloc(sizeof(char) * 20);
    char *tank2 = (char *) malloc(sizeof(char) * 20);
    Laser *laser = (Laser *) malloc(sizeof(Laser) * 1);
    map->laser = laser;
    laser->life = SDL_GetTicks();
    laser->x = rand() % MAP_WIDTH - 10;
    laser->y = rand() % MAP_WIDTH;
//----------------------------------------------------------------------    load a game
    if (damedasti == SAVECODE) {
        FILE *file;
        file = fopen("C:\\Users\\Asus\\Desktop\\project\\src\\load.txt", "r");
        if (file == NULL) {
            printf("error");
            return 0;
        }
        fread(map->tank, sizeof(Tank), 1, file);
        fread(map->tank->bullets, sizeof(Bullet), AMMO, file);
        fread(map->tanking, sizeof(Tank), 1, file);
        fread(map->tanking->bullets, sizeof(Bullet), AMMO, file);
        fread(&(map->n), sizeof(unsigned short), 1, file);
        fread(map->laser, sizeof(Laser), 1, file);
        fread(&i, sizeof(unsigned short), 1, file);
        fread(&k, sizeof(unsigned short), 1, file);
        fread(&zx, sizeof(unsigned short), 1, file);
        fread(&xz, sizeof(unsigned short), 1, file);
        fclose(file);

        switch (map->n % 3) {
            case 0:
                map->wall = saved_walls3;
                break;
            case 1:
                map->wall = saved_walls1;
                break;
            case 2:
                map->wall = saved_walls2;
        }
    }
//---------------------------------------------------------------------------   starting a new game
    if (damedasti != SAVECODE) {
        n = rand() % 3;
        switch (n) {
            case 0:
                map->wall = saved_walls3;
                map->n = 31;
                break;
            case 1:
                map->wall = saved_walls1;
                map->n = 22;
                break;
            case 2:
                map->wall = saved_walls2;
                map->n = 36;
        }
        tank_1->x = rand() % MAP_WIDTH + 35;
        tank_1->y = rand() % MAP_HEIGHT;
        tank_1->XNoghtedovvom = tank_1->x;
        tank_1->YNoghtedovvom = tank_1->y - LENGTH;
        tank_1->angle = M_PI / 2;
        tank_1->score = 0;
        tank_2->x = rand() % MAP_WIDTH - 100;
        tank_2->y = rand() % MAP_HEIGHT;
        tank_2->XNoghtedovvom = tank_2->x;
        tank_2->YNoghtedovvom = tank_2->y + LENGTH;
        tank_2->angle = 3 * M_PI / 2;
        tank_2->score = 0;
    }
//------------------------------------------------------------//avvaliyeh
    //  FIRST THINGS, FIRST!

    SDL_Init(SDL_INIT_VIDEO);
    menu();                                                   //first menu
    gfxPrimitivesSetFont(NULL, 0, 0);
    if (damedasti == EXITCODE)
        return 0;
    SDL_Window *window = SDL_CreateWindow("GAME", 100, 50, MAP_WIDTH, MAP_HEIGHT, SDL_WINDOW_OPENGL);   //CREATE A
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);                  //WINDOW TO PLAY

//-------------------------------------------------------------
    while (1) {

        death(tank_1, true);  //check bullets life duration
        death(tank_2, false);

        if ((handleEvents(map) == EXITCODE) || (damedasti == EXITCODE))   //check ending
            break;                                                        //handling events

        sprintf(tank1, "GREEN SCORE : %d", tank_1->score);
        sprintf(tank2, "RED SCORE : %d", tank_2->score);
        if ((tank_1->score > TIMES) || (tank_2->score > TIMES))       //check if there is a LOOSER or not
            break;

//------------------------------------------------------------- drawing the map and the tanks, or in-game menu
        SDL_SetRenderDrawColor(renderer, 250, 200, 60, 255);
        SDL_RenderClear(renderer);

        switch (n) {    //draw the walls according to n
            case 0:
                for (int j = 0; j < 31; j++)
                    thickLineRGBA(renderer, saved_walls3[j].x1, saved_walls3[j].y1, saved_walls3[j].x2,
                                  saved_walls3[j].y2, 5, 0, 0, 255, 255);
                break;
            case 1:
                for (int j = 0; j < 22; j++)
                    thickLineRGBA(renderer, saved_walls1[j].x1, saved_walls1[j].y1, saved_walls1[j].x2,
                                  saved_walls1[j].y2, 5, 0, 0, 255, 255);
                break;
            case 2:
                for (int j = 0; j < 36; j++)
                    thickLineRGBA(renderer, saved_walls2[j].x1, saved_walls2[j].y1, saved_walls2[j].x2,
                                  saved_walls2[j].y2, 5, 0, 0, 255, 255);
                break;
        }

        //tanking!
        filledCircleRGBA(renderer, tank_1->x, tank_1->y, RADIUS, 0, 100, 100, 255);
        thickLineRGBA(renderer, tank_1->x, tank_1->y, tank_1->XNoghtedovvom, tank_1->YNoghtedovvom, 5, 0, 255, 0, 255);
        filledCircleRGBA(renderer, tank_2->x, tank_2->y, RADIUS, 250, 10, 10, 255);
        thickLineRGBA(renderer, tank_2->x, tank_2->y, tank_2->XNoghtedovvom, tank_2->YNoghtedovvom, 5, 2, 2, 2, 255);

        if (damedasti == MENUCODE) {        //a menu in game
            boxRGBA(renderer, 0, 0, 900, 700, 220, 220, 220, 250);
            SDL_RenderSetScale(renderer, 2, 2);
            stringRGBA(renderer, 60, 20, "PRESS 'L' FOR LOAD GAME FROM LAST SAVE", 10, 10, 10, 255);
            stringRGBA(renderer, 90, 75, "PRESS 'G' TO START A NEW GAME", 10, 10, 10,
                       255);              //SPEAKING AGAIN?
            stringRGBA(renderer, 50, 130, "YOU CAN ALWAYS PRESS 'E' TO SAVE YOUR GAME", 10, 10, 10, 255);
            stringRGBA(renderer, 105, 190, "PRESS 'Q' TO EXIT THE GAME", 10, 10, 10, 255);
            stringRGBA(renderer, 90, 245, "PRESS 'esc' TO RESUME THE GAME", 10, 40, 40, 255);           //SO FORGETFUL!
            stringRGBA(renderer, 2, 260, "NOTE THAT YOU CAN ALWAYS PRESS 'esc' TO ENTER THIS MENU", 10, 10, 10, 255);
            stringRGBA(renderer, 135, 275, "AND PAUSE THE GAME.", 10, 10, 10, 255);
            SDL_RenderSetScale(renderer, 1, 1);
        }
        if (damedasti == NEWGAME) {      //ARE YOU KIDDING?
            i = 0;
            damedasti = 0;
            k = 0;
            xz = 0;
            zx = 0;
            tank_1->x = rand() % MAP_WIDTH + 35;
            tank_1->y = rand() % MAP_HEIGHT;
            tank_1->XNoghtedovvom = tank_1->x;
            tank_1->YNoghtedovvom = tank_1->y - LENGTH;     //AGAIN... ))))))):
            tank_1->angle = M_PI / 2;
            tank_1->score = 0;
            tank_2->x = rand() % MAP_WIDTH - 100;
            tank_2->y = rand() % MAP_HEIGHT;
            tank_2->XNoghtedovvom = tank_2->x;
            tank_2->YNoghtedovvom = tank_2->y + LENGTH;
            tank_2->angle = 3 * M_PI / 2;
            tank_2->score = 0;
        }

//----------------------------------------------------------------      draw bullets, check if a bullet hit a wall
        if (damedasti != LASERCODE1 || damedasti != LASERCODE11) {
            for (int j = k; j < i; j++) {
                if (pingpong(map, true) == 1)
                    tank_1->bullets[j].angle = (2 * M_PI - tank_1->bullets[j].angle);
                if (pingpong(map, true) == 2)
                    tank_1->bullets[j].angle = M_PI - tank_1->bullets[j].angle;
                tank_1->bullets[j].x += (step * cos(tank_1->bullets[j].angle));
                tank_1->bullets[j].y -= (step * sin(tank_1->bullets[j].angle));
                filledCircleRGBA(renderer, tank_1->bullets[j].x, tank_1->bullets[j].y, 5, 100, 100, 100, 255);
            }
        }
        if (damedasti != LASERCODE2 || damedasti != LASERCODE22) {
            for (int j = xz; j < zx; j++) {
                if (pingpong(map, false) == 1)
                    tank_2->bullets[j].angle *= (-1);
                if (pingpong(map, false) == 2)
                    tank_2->bullets[j].angle = M_PI - tank_2->bullets[j].angle;
                tank_2->bullets[j].x += (step * cos(tank_2->bullets[j].angle));
                tank_2->bullets[j].y -= (step * sin(tank_2->bullets[j].angle));
                filledCircleRGBA(renderer, tank_2->bullets[j].x, tank_2->bullets[j].y, 5, 100, 100, 100, 255);
            }
        }

        if (damedasti == LASERCODE11) {
            laser->angle = tank_1->angle;
            thickLineRGBA(renderer, tank_1->YNoghtedovvom, tank_1->YNoghtedovvom, MAP_WIDTH * cos(tank_1->angle),
                          MAP_HEIGHT * sin(tank_1->angle), 2, 250, 10, 10, 255);
            damedasti = LASERCODE1;
        }                                                                       //draw laser
        if (damedasti == LASERCODE22) {
            laser->angle = tank_2->angle;
            thickLineRGBA(renderer, tank_2->YNoghtedovvom, tank_2->YNoghtedovvom, MAP_WIDTH * cos(tank_2->angle),
                          MAP_HEIGHT * sin(tank_2->angle), 2, 250, 10, 10, 255);
            damedasti = LASERCODE2;
        }

        stringRGBA(renderer, 15, 15, tank2, 250, 0, 0, 255);              //scoreboard
        stringRGBA(renderer, 750, 15, tank1, 0, 100, 100, 255);

//----------------------------------------------------------    DON'T HURT ME...NO MORE...
        if (isthere(map) == 1) {
            tank_1->x = rand() % MAP_WIDTH + 35;
            tank_1->y = rand() % MAP_HEIGHT;
            tank_1->XNoghtedovvom = tank_1->x;
            tank_1->YNoghtedovvom = tank_1->y - LENGTH;
            tank_1->angle = M_PI / 2;
            tank_2->score++;
        }
        if (isthere(map) == 2) {
            tank_2->x = rand() % MAP_WIDTH - 100;           //IF A BULLET HITS A TANK
            tank_2->y = rand() % MAP_HEIGHT;
            tank_2->XNoghtedovvom = tank_2->x;
            tank_2->YNoghtedovvom = tank_2->y + LENGTH;
            tank_2->angle = 3 * M_PI / 2;
            tank_1->score++;
        }
        if (SDL_TICKS_PASSED(SDL_GetTicks(), laser->life + 15000) == true) {
            boxRGBA(renderer, laser->x, laser->y, laser->x + 5, laser->y + 5, 250, 10, 10, 255);
            if (SDL_TICKS_PASSED(SDL_GetTicks(), laser->life + 20000) == true || isthere(map) == 1 || isthere(map) == 2)
                laser->life += 20000;
        }
        SDL_RenderPresent(renderer);

//---------------------------------------------------------
        SDL_Delay(1000 / FPS);  //delay
    }
    tank_1->x = SDL_GetTicks();
//----------------------------------------------------------
    SDL_DestroyRenderer(renderer);  //void
    SDL_DestroyWindow(window);      //quit
    SDL_Quit();                     //window
    printf("green score was : %d\nred score was : %d\ntime elapsed is : %ld ms", tank_1->score, tank_2->score,
           (long) tank_1->x);
    return 0;
}
