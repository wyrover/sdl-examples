#include "SDL_circle.h"

void SDL_RenderFillCircle(SDL_Renderer *r, int x, int y, int radius)
{
    // lets draw a circle!
    // http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    // algorithm slightly adapted to pair the points for line drawing
    int cx = radius / 2;
    int cy = 0;
    int radiusError = 1 - cx;
    // buffer up enough to fit the circle points
    SDL_Point points[(radius / 2) * 6];
    unsigned int pointCount = 0;
    int xDiff = x + radius;
    int yDiff = y + radius;

    while (cx >= cy) {
        // top cover (round part. on top)
        points[pointCount++] = SDL_Point{ cy + xDiff, -cx + yDiff};
        points[pointCount++] = SDL_Point{ -cy + xDiff, -cx + yDiff};
        // top half cover
        points[pointCount++] = SDL_Point{ cx + xDiff, -cy + yDiff};
        points[pointCount++] = SDL_Point{ -cx + xDiff, -cy + yDiff};
        // bottom half
        points[pointCount++] = SDL_Point{ cx + xDiff,  cy + yDiff};
        points[pointCount++] = SDL_Point{ -cx + xDiff,  cy + yDiff};
        // bottom cover (round part. on bottom)
        points[pointCount++] = SDL_Point{ cy + xDiff,  cx + yDiff};
        points[pointCount++] = SDL_Point{ -cy + xDiff,  cx + yDiff};
        //
        cy++;

        if (radiusError < 0)  {
            radiusError += 2 * cy + 1;
        }  else  {
            cx--;
            radiusError += 2 * (cy - cx + 1);
        }
    }

    SDL_RenderDrawLines(r, points, pointCount);
}