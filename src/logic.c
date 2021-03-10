//YA SAJJAD

#include <stdbool.h>
#include "struct.h"
#include <SDL.h>
#include <math.h>

void death(Tank *tank, bool yn) {
    if (yn == true) {
        for (int j = k; j < i; j++) {
            if (tank->bullets[j].life + LIFE < SDL_GetTicks())
                k++;
        }
    } else {
        for (int j = xz; j < zx; j++) {
            if (tank->bullets[j].life + LIFE < SDL_GetTicks())
                xz++;
        }
    }
}

bool movement_collids_walls(Map *map, short a) {
    bool f = false;
    switch (a) {
        case 1:
            for (int j = 0; j < map->n; j++) {
                double b = fabs(map->tank->x + step * cos(map->tank->angle) - map->wall[j].x1);
                double c = fabs(map->tank->y - step * sin(map->tank->angle) - map->wall[j].y1);
                if (((b < LENGTH) && (map->tank->y >= map->wall[j].y1 - LENGTH) &&
                     (map->tank->y <= map->wall[j].y2 + LENGTH)) ||
                    ((c < LENGTH) && (map->tank->x >= map->wall[j].x1 - LENGTH) &&
                     (map->tank->x <= map->wall[j].x2 + LENGTH))) {
                    f = true;
                    break;
                }
            }
            return f;
        case 2:
            for (int j = 0; j < map->n; j++) {
                double b = fabs(map->tank->x - step * cos(map->tank->angle) - map->wall[j].x1);
                double c = fabs(map->tank->y + step * sin(map->tank->angle) - map->wall[j].y1);
                if (((b < LENGTH) && (map->tank->y >= map->wall[j].y1 - LENGTH) &&
                     (map->tank->y <= map->wall[j].y2 + LENGTH)) ||
                    ((c < LENGTH) && (map->tank->x >= map->wall[j].x1 - LENGTH) &&
                     (map->tank->x <= map->wall[j].x2 + LENGTH))) {
                    f = true;
                    break;
                }
            }
            return f;
        case 5:
            for (int j = 0; j < map->n; j++) {
                double b = fabs(map->tanking->x + step * cos(map->tanking->angle) - map->wall[j].x1);
                double c = fabs(map->tanking->y - step * sin(map->tanking->angle) - map->wall[j].y1);
                if (((b < LENGTH) && (map->tanking->y >= map->wall[j].y1 - LENGTH) &&
                     (map->tanking->y <= map->wall[j].y2
                                         + LENGTH)) || ((c < LENGTH) && (map->tanking->x >= map->wall[j].x1 - LENGTH) &&
                                                        (map->tanking->x <= map->wall[j].x2
                                                                            + LENGTH))) {
                    f = true;
                    break;
                }
            }
            return f;
        case 6:
            for (int j = 0; j < map->n; j++) {
                double b = fabs(map->tanking->x - step * cos(map->tanking->angle) - map->wall[j].x1);
                double c = fabs(map->tanking->y + step * sin(map->tanking->angle) - map->wall[j].y1);
                if (((b < LENGTH) && (map->tanking->y + step * sin(map->tanking->angle) >= map->wall[j].y1 - LENGTH)
                     && (map->tanking->y + step * sin(map->tanking->angle) <= map->wall[j].y2 + LENGTH)) ||
                    ((c < LENGTH) && (map->tanking->x - step * cos(map->tanking->angle) >= map->wall[j].x1 - LENGTH)
                     && (map->tanking->x - step * cos(map->tanking->angle) <= map->wall[j].x2 + LENGTH))) {
                    f = true;
                    break;
                }
            }
            return f;
        default:
            return f;
    }
}

short isthere(Map *map) {
    for (int j = (int) fmin(k, xz); j < fmax(i, zx); j++) {
        double a = map->tank->bullets[j].x - map->tank->x;
        double b = map->tanking->bullets[j].x - map->tank->x;
        double c = map->tank->bullets[j].x - map->tanking->x;
        double d = map->tanking->bullets[j].x - map->tanking->x;
        double aa = map->tank->bullets[j].y - map->tank->y;
        double bb = map->tanking->bullets[j].y - map->tank->y;
        double cc = map->tank->bullets[j].y - map->tanking->y;
        double dd = map->tanking->bullets[j].y - map->tanking->y;
        if (sqrt(a * a + aa * aa) < RADIUS + 2) {
            map->tank->bullets[j].life -= LIFE;
            return 1;
        }
        if (sqrt(b * b + bb * bb) < RADIUS + 2) {
            map->tanking->bullets[j].life -= LIFE;
            return 1;
        }
        if (sqrt(c * c + cc * cc) < RADIUS + 2) {
            map->tank->bullets[j].life -= LIFE;
            return 2;
        }
        if (sqrt(d * d + dd * dd) < RADIUS + 2) {
            map->tanking->bullets[j].life -= LIFE;
            return 2;
        }
    }

    double g = map->laser->x + 2.5 - map->tank->x;
    double gg = map->laser->y + 2.5 - map->tank->y;
    double q = map->laser->x + 2.5 - map->tanking->x;
    double qq = map->laser->y + 2.5 - map->tanking->y;
    if (sqrt(g * g + gg * gg) < 2.5) {
        damedasti = LASERCODE1;
        return 1;
    }
    if (sqrt(q * q + qq * qq) < 2.5) {
        damedasti = LASERCODE2;
        return 2;
    }

    if (damedasti == LASERCODE1) {
        if (fabs((map->tanking->x - map->tank->x) * sin(map->laser->angle) - (map->tanking->y - map->tank->y) *
                                                                             cos(map->laser->angle)) < RADIUS)
            return 2;
    }
    if (damedasti == LASERCODE2) {
        if (fabs((map->tank->x - map->tanking->x) * sin(map->laser->angle) - (map->tank->y - map->tanking->y) *
                                                                             cos(map->laser->angle)) < RADIUS)
            return 1;
    }
    return 0;
}
