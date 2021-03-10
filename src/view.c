#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "struct.h"
#include "physics.h"
#include "logic.h"
#include <SDL2_gfxPrimitives.h>

void harekat(Map *map) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (damedasti != MENUCODE) {
        if ((state[SDL_SCANCODE_UP]) && (movement_collids_walls(map, 1) == false))
            move_tanks(map->tank, true);
        if ((state[SDL_SCANCODE_DOWN]) && (movement_collids_walls(map, 2) == false))
            move_tanks(map->tank, false);
        if (state[SDL_SCANCODE_RIGHT])
            turn_tanks(map->tank, true);
        if (state[SDL_SCANCODE_LEFT])
            turn_tanks(map->tank, false);
        if (state[SDL_SCANCODE_M]) {
            if (i < AMMO) {
                if (damedasti != LASERCODE1) {
                    fire(map->tank, true);
                    i++;
                } else
                    damedasti = LASERCODE11;
            }
        }
        if ((state[SDL_SCANCODE_W]) && (movement_collids_walls(map, 5) == false))
            move_tanks(map->tanking, true);
        if ((state[SDL_SCANCODE_S]) && (movement_collids_walls(map, 6) == false))
            move_tanks(map->tanking, false);
        if (state[SDL_SCANCODE_D])
            turn_tanks(map->tanking, true);
        if (state[SDL_SCANCODE_A])
            turn_tanks(map->tanking, false);
        if (state[SDL_SCANCODE_SPACE]) {
            if (zx < AMMO) {
                if (damedasti != LASERCODE2) {
                    fire(map->tanking, false);
                    zx++;
                } else
                    damedasti = LASERCODE22;
            }
        }
        if (state[SDL_SCANCODE_ESCAPE])
            damedasti = MENUCODE;
    } else {
        if (state[SDL_SCANCODE_ESCAPE])
            damedasti = 0;
        if (state[SDL_SCANCODE_G])
            damedasti = NEWGAME;
        if (state[SDL_SCANCODE_Q])
            damedasti = EXITCODE;
        if (state[SDL_SCANCODE_E])
            save_game(map, true);
        if (state[SDL_SCANCODE_L])
            save_game(map, false);
    }
}

int handleEvents(Map *map) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXITCODE;
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            harekat(map);
    }
}

void menu() {
    SDL_Window *menu = SDL_CreateWindow("MENU", 200, 50, MAP_WIDTH, MAP_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderers = SDL_CreateRenderer(menu, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderers, 120, 220, 60, 255);
    SDL_RenderClear(renderers);
    SDL_RenderSetScale(renderers, 2, 2);
    stringRGBA(renderers, 60, 10, "PRESS 'L' FOR LOAD GAME FROM LAST SAVE", 10, 10, 250, 255);
    stringRGBA(renderers, 90, 65, "PRESS 'G' TO START A NEW GAME", 20, 20, 250, 255);                //SPEAKING...
    stringRGBA(renderers, 100, 130, "PRESS 'E' TO SAVE YOUR GAME", 25, 25, 250, 255);
    stringRGBA(renderers, 105, 190, "PRESS 'Q' TO EXIT THE GAME", 30, 30, 250, 255);
    stringRGBA(renderers, 90, 245, "PRESS 'esc' TO RESUME THE GAME", 40, 40, 250, 255);
    stringRGBA(renderers, 2, 260, "NOTE THAT YOU CAN ALWAYS PRESS 'esc' TO ENTER THIS MENU", 50, 50, 250, 255);
    stringRGBA(renderers, 135, 275, "AND PAUSE THE GAME.", 50, 50, 250, 255);
    SDL_RenderSetScale(renderers, 1, 1);
    SDL_RenderPresent(renderers);
    SDL_Event event;
    bool flg = true;
    while (flg) {
        while (SDL_PollEvent(&event)) {
            if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_q)) {
                SDL_DestroyRenderer(renderers);  //void
                SDL_DestroyWindow(menu);         //quit
                SDL_Quit();                      //window
                damedasti = EXITCODE;
                return;
            }
            if (event.key.keysym.sym == SDLK_g) {
                flg = false;
                break;
            }
            if (event.key.keysym.sym == SDLK_l) {
                damedasti = SAVECODE;
                flg = false;
                break;
            }
        }
    }
    SDL_DestroyRenderer(renderers);
    SDL_DestroyWindow(menu);
}
