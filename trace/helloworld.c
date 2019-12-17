/* hello.c
 * This is a straightforward RGB gradient generator
 * that outputs in ppm format.
 */

#define IMAGE_WIDTH 1000
#define IMAGE_HEIGHT 1000

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main() {
    /* output magic number */
    printf("P3\n");

    /* output dimensions */
    printf("%d %d\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    /* output colors */
    printf("%d\n", 255);

    /* seed RNG */
    time_t t;
    srand((unsigned) time(&t));

    for (int xi = 0; xi < (IMAGE_WIDTH - 1); xi++) {
        for (int yi = 0; yi < (IMAGE_HEIGHT - 1); yi++) {
            float r = 255 * ((float)xi / (float)IMAGE_WIDTH);
            float g = 255 * ((float)yi / (float)IMAGE_HEIGHT);
            float b = xi > yi ? r : g * (rand() % 2);
            printf("%d %d %d\n", (int)r, (int)g, (int)b);
        }
    }

    return 0;
}