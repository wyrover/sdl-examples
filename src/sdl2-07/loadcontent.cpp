#include"game.h"

bool game::LoadContent()
{
    int w = 0, h = 0;
    /*************************************************************
    Create Surface
    *************************************************************/
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(0, 2048, 2048, 32, rmask, gmask, bmask, amask);
    std::cout << "W " << surface->w << " H " << surface->h << "\n";
    /****************************************************************************
    Create Map
    ****************************************************************************/
    //Allocate map space (2048+1)x(2048+1)=4198401
    float *mmap;
    mmap = new float [4198401];

    //set all to zero
    for (int x = 0; x < 4198401; x++) {
        mmap[x] = 0;
    }

    mmap[0 + (0 * 2048)] = 0;
    mmap[2048 + (0 * 2049)] = 10;
    mmap[0 + (2048 * 2049)] = 5;
    mmap[2048 + (2048 * 2049)] = -5;
    /***********************************************************/
    srand(time(NULL));
    /***********************************************************/
    struct pp {
        int x, y;
        float e;
    };
    pp A, B, C, D, E, TL, TR, BL, BR;
    float change = 10.0;
    int step = 2048;

    while (step > 1) {
        for (int y = 0; y < 2048; y += step) {
            for (int x = 0; x < 2048; x += step) {
                TL.x = x;
                TL.y = y;
                TR.x = x + step;
                TR.y = y;
                BL.x = x;
                BL.y = y + step;
                BR.x = x + step;
                BR.y = y + step;
                TL.e = mmap[TL.x + (TL.y * 2049)];
                TR.e = mmap[TR.x + (TR.y * 2049)];
                BL.e = mmap[BL.x + (BL.y * 2049)];
                BR.e = mmap[BR.x + (BR.y * 2049)];
                A.x = x + (step / 2);
                A.y = y + (step / 2);
                A.e = ((TL.e+TR.e+BL.e+BR.e) / 4);

                if (rand() % 2) {
                    A.e += change;
                } else {
                    A.e -= change;
                }

                B.x = x + (step / 2);
                B.y = y;
                B.e = ((TL.e+TR.e) / 2);

                if (rand() % 2) {
                    B.e += change;
                } else {
                    B.e -= change;
                }

                C.x = x + step;
                C.y = y + (step / 2);
                C.e = ((TR.e+BR.e) / 2);

                if (rand() % 2) {
                    C.e += change;
                } else {
                    C.e -= change;
                }

                D.x = x + (step / 2);
                D.y = y + step;
                D.e = ((BL.e+BR.e) / 2);

                if (rand() % 2) {
                    D.e += change;
                } else {
                    D.e -= change;
                }

                E.x = x;
                E.y = y + (step / 2);
                E.e = ((TL.e+BL.e) / 2);

                if (rand() % 2) {
                    E.e += change;
                } else {
                    E.e -= change;
                }

                mmap[A.x + (A.y * 2049)] = A.e;
                mmap[B.x + (B.y * 2049)] = B.e;
                mmap[C.x + (C.y * 2049)] = C.e;
                mmap[D.x + (D.y * 2049)] = D.e;
                mmap[E.x + (E.y * 2049)] = E.e;
            }
        }

        step /= 2;
        change /= 2;
    }

    /***********************************************************/
    int low = 9999, high = 0;

    for (int x = 0; x < 4198401; x++) {
        if (mmap[x] > high) {
            high = mmap[x];
        }

        if (mmap[x] < low) {
            low = mmap[x];
        }
    }

    std::cout << low << " " << high << "\n";
    int elevation = ((high - low) / 2) + low;
    std::cout << elevation << "\n";
    /****************************************************************************
    Fill surface
    see mask above for color
    ****************************************************************************/
    unsigned int *pixels = (unsigned int *)surface->pixels;
    unsigned int color = 0xff000000;

    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }

    for (int y = 0; y < 2047; y++) {
        for (int x = 0; x < 2047; x++) {
            color = 0;
            float a = (mmap[x + (y * 2049)] + mmap[x + 1 + (y * 2049)] + mmap[x + 1 + ((y + 1) * 2049)] + mmap[x + ((y + 1) * 2049)]) / 4;

            if ((int)a <= elevation) {
                color = 0xffff0000;
            }

            if ((int)a >= elevation + 1) {
                color = 0xff577ab9;
            }

            if ((int)a >= elevation + 2) {
                color = 0xff00ff00;
            }

            if ((int)a >= high - 4) {
                color = 0xff888888;
            }

            if ((int)a >= high - 2) {
                color = 0xffffffff;
            }

            //Color AABBGGRR
            //color = 0xff0000ff;
            pixels[x + (y * 2048)] = color;
        }
    }

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }

    Map = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(Map, NULL, NULL, &w, &h);
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    rectMap.x = 0;
    rectMap.y = 0;
    rectMap.w = ww;
    rectMap.h = wh;
    //saving to png
    SDL_SaveBMP(surface, "res/sdl2-07/Map01.png");
    SDL_FreeSurface(surface);
    delete[] mmap;
    return 1;
}
