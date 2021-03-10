//YA AMIR-ALMOMENIN
#include <stdbool.h>
#include "struct.h"
#include <math.h>
#include <SDL.h>
#include <stdio.h>

void turn_tanks(Tank *tank, bool yn) {
    if (yn == true) {
        tank->angle -= DELTA;
        tank->XNoghtedovvom = tank->x + LENGTH * cos(tank->angle);
        tank->YNoghtedovvom = tank->y - LENGTH * sin(tank->angle);
    } else {
        tank->angle += DELTA;
        tank->XNoghtedovvom = tank->x + LENGTH * cos(tank->angle);
        tank->YNoghtedovvom = tank->y - LENGTH * sin(tank->angle);
    }
}

void move_tanks(Tank *tank, bool yn) {
    if (yn == true) {
        tank->y -= step * sin(tank->angle);
        tank->YNoghtedovvom -= step * sin(tank->angle);
        tank->x += step * cos(tank->angle);
        tank->XNoghtedovvom += step * cos(tank->angle);
    } else {
        tank->y += step * sin(tank->angle);
        tank->YNoghtedovvom += step * sin(tank->angle);
        tank->x -= step * cos(tank->angle);
        tank->XNoghtedovvom -= step * cos(tank->angle);
    }
}

void fire(Tank *tank, bool yn) {
    if (yn == true) {
        tank->bullets[i].angle = tank->angle;
        tank->bullets[i].x = tank->XNoghtedovvom;
        tank->bullets[i].y = tank->YNoghtedovvom;
        tank->bullets[i].life = SDL_GetTicks();
    } else {
        tank->bullets[zx].angle = tank->angle;
        tank->bullets[zx].x = tank->XNoghtedovvom;
        tank->bullets[zx].y = tank->YNoghtedovvom;
        tank->bullets[zx].life = SDL_GetTicks();
    }
}

short pingpong(Map *map, bool yn) {
    if (yn == true) {
        for (int j = 0; j < map->n; j++) {
            for (int a = k; a < i; a++) {
                double b = fabs(map->tank->bullets[a].x + step * cos(map->tank->bullets[a].angle) - map->wall[j].x1);
                double c = fabs(map->tank->bullets[a].y - step * sin(map->tank->bullets[a].angle) - map->wall[j].y1);
                if (((b < 6) &&
                     (map->tank->bullets[a].y + step * sin(map->tank->bullets[a].angle) >= map->wall[j].y1 - 6)
                     && (map->tank->bullets[a].y + step * sin(map->tank->bullets[a].angle + 6) <= map->wall[j].y2)) ||
                    ((c < 6) &&
                     (map->tank->bullets[a].x - step * cos(map->tank->bullets[a].angle) >= map->wall[j].x1 - 6)
                     && (map->tank->bullets[a].x - step * cos(map->tank->bullets[a].angle) <= map->wall[j].x2 + 6))) {
                    if (map->wall[j].x1 == map->wall[j].x2)
                        return 2;
                    if (map->wall[j].y1 == map->wall[j].y2)
                        return 1;
                }
            }
        }
        return 0;
    } else {
        for (int j = 0; j < map->n; j++) {
            for (int a = k; a < i; a++) {
                double b = fabs(
                        map->tanking->bullets[a].x + step * cos(map->tanking->bullets[a].angle) - map->wall[j].x1);
                double c = fabs(
                        map->tanking->bullets[a].y - step * sin(map->tanking->bullets[a].angle) - map->wall[j].y1);
                if (((b < 6) &&
                     (map->tanking->bullets[a].y + step * sin(map->tanking->bullets[a].angle) >= map->wall[j].y1 - 6)
                     && (map->tanking->bullets[a].y + step * sin(map->tanking->bullets[a].angle + 6) <=
                         map->wall[j].y2)) ||
                    ((c < 6) &&
                     (map->tanking->bullets[a].x - step * cos(map->tanking->bullets[a].angle) >= map->wall[j].x1 - 6)
                     && (map->tanking->bullets[a].x - step * cos(map->tanking->bullets[a].angle) <=
                         map->wall[j].x2 + 6))) {
                    if (map->wall[j].x1 == map->wall[j].x2)
                        return 2;
                    if (map->wall[j].y1 == map->wall[j].y2)
                        return 1;
                }
            }
        }
        return 0;
    }
}

void save_game(Map *map, bool yn) {
    FILE *file;
    if (yn == true) {
        file = fopen("C:\\Users\\Asus\\Desktop\\project\\src\\load.txt", "w");
        if (file == NULL) {
            printf("error");
            return;
        }
        fwrite(map->tank, sizeof(Tank), 1, file);
        fwrite(map->tank->bullets, sizeof(Bullet), AMMO, file);
        fwrite(map->tanking, sizeof(Tank), 1, file);
        fwrite(map->tanking->bullets, sizeof(Bullet), AMMO, file);
        fwrite(&(map->n), sizeof(unsigned short), 1, file);
        fwrite(map->laser, sizeof(Laser), 1, file);
        fwrite(&i, sizeof(unsigned short), 1, file);
        fwrite(&k, sizeof(unsigned short), 1, file);
        fwrite(&zx, sizeof(unsigned short), 1, file);
        fwrite(&xz, sizeof(unsigned short), 1, file);
        fclose(file);
    } else {
        file = fopen("C:\\Users\\Asus\\Desktop\\project\\src\\load.txt", "r");
        if (file == NULL) {
            printf("error");
            return;
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
    }
}
