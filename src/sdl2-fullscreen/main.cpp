#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>

#include <SDL.h>

//The DYNAMIC  initial size of the screen
unsigned int SCREEN_WIDTH;
unsigned int SCREEN_HEIGHT;


///this function produces a gradient on datsurface.
// the gradient will only be printed inside of the gradClip rectangle.
// at point 1 (x1,y1) there will be color1.
// at ponit 2 (x2,y2) there will be color2.
///horizontal gradients (y1=y2) and verticle gradients (x1=x2) are very fast compared to gradients at different slopes (where neither x1=x2 or y1=y2)
///if you are looking for speed, verticle/horizontal gradients are the way to go.
void gradient(SDL_Surface *datsurface, SDL_Rect *gradClip, int x1, int y1, int x2, int y2, Uint32 color1, Uint32 color2, unsigned int gradientType)
{
    // there is no point in printing a gradient with only a single point
    if (x1 == x2 && y1 == y2) {
        return;
    }

    // this is the integer used for the color of (i,j) pixel in the gradient
    long unsigned int color;
    // these are all one-time calculations. these values will be used in the loop.
    unsigned int alp1 = color1 / 0x1000000;
    unsigned int red1 = (color1 / 0x10000) % 0x100;
    unsigned int gre1 = (color1 / 0x100) % 0x100;
    unsigned int blu1 = color1 % 0x100;
    unsigned int alp2 = color2 / 0x1000000;
    unsigned int red2 = (color2 / 0x10000) % 0x100;
    unsigned int gre2 = (color2 / 0x100) % 0x100;
    unsigned int blu2 = color2 % 0x100;
    // this is for displaying the pixel at (i,j)
    SDL_Rect pixelRect;
    pixelRect.w = 1;
    pixelRect.h = 1;
    float m, b1, b2, diff, b, x, y;
    int i, j; // variables used to loop through the columns and row respectively.

    // if the gradient has no slope
    if (x1 == x2) {
        diff = (y2 - y1);
        pixelRect.x = gradClip->x;
        pixelRect.w = gradClip->w;

        // we will print rectangles that are 1-pixel tall horizontal line segments
        for (j = gradClip->y; j < gradClip->y + gradClip->h; j++) { // loop through the rows    of the gradient clip
            y = (float)j;   // calculate y-intercept for this point (i,j)

            if (y < y1)                 // the pixel is not between the two points
                color = color1;         // choose color1
            else if (y > y2)        // the pixel is not between the two points
                color = color2;         // choose color2
            else {
                color = (int)((alp1 * (y2 - y) + alp2 * (y - y1)) / diff) * 0x1000000; // calculate alpha color component
                color += (int)((red1 * (y2 - y) + red2 * (y - y1)) / diff) * 0x10000; // calculate red   color component
                color += (int)((gre1 * (y2 - y) + gre2 * (y - y1)) / diff) * 0x100; // calculate green color component
                color += (int)((blu1 * (y2 - y) + blu2 * (y - y1)) / diff); // calculate blue  color component
            }

            pixelRect.y = y;
            SDL_FillRect(datsurface, &pixelRect, color);
        }
    }
    // if the gradient has infinite(very large slope
    else if (y1 == y2) {
        // we will print rectangels that are 1-pixel wide verticle line segments
        diff = (x2 - x1);
        pixelRect.y = gradClip->y;
        pixelRect.h = gradClip->h;

        // we will print rectangles that are 1-pixel tall horizontal line segments
        for (i = gradClip->x; i < gradClip->x + gradClip->w; i++) { // loop through the rows    of the gradient clip
            x = (float)i;   // calculate y-intercept for this point (i,j)

            if (x < x1)                 // the pixel is not between the two points
                color = color1;         // choose color1
            else if (x > x2)        // the pixel is not between the two points
                color = color2;         // choose color2
            else {
                color = (int)((alp1 * (x2 - x) + alp2 * (x - x1)) / diff) * 0x1000000; // calculate alpha color component
                color += (int)((red1 * (x2 - x) + red2 * (x - x1)) / diff) * 0x10000; // calculate red   color component
                color += (int)((gre1 * (x2 - x) + gre2 * (x - x1)) / diff) * 0x100; // calculate green color component
                color += (int)((blu1 * (x2 - x) + blu2 * (x - x1)) / diff); // calculate blue  color component
            }

            pixelRect.x = x;
            SDL_FillRect(datsurface, &pixelRect, color);
        }
    }
    // if the slope is a non-zero finite value
    else {
        //this is for the lines perpendicular to the original line. it is -1/original_line_slope.
        //this is the slope that will be used when calculating the color of each pixel
        m = ((float)(x1 - x2)) / ((float)(y2 - y1)); // calculate slope of the line perpendicular to the gradient line
        b1 = y1 - m * x1;                       // rearranged form of  y = mx + b  to calculate the the y-intercept for b1
        b2 = y2 - m * x2;                       // similar shenanigans for b2
        diff = b2 - b1;                     // calculate the difference in the y-intercept terms

        for (i = gradClip->x; i < gradClip->x + gradClip->w; i++) { // loop through the columns of the gradient clip
            for (j = gradClip->y; j < gradClip->y + gradClip->h; j++) { // loop through the rows    of the gradient clip
                pixelRect.x = i;
                pixelRect.y = j;
                b = (float)j - m * (float)i; // calculate y-intercept for this point (i,j)

                if (b < b1)                 // the pixel is not between the two points
                    color = color1;         // choose color1
                else if (b > b2)        // the pixel is not between the two points
                    color = color2;         // choose color2
                else {
                    color = (int)((alp1 * (b2 - b) + alp2 * (b - b1)) / diff) * 0x1000000; // calculate alpha color component
                    color += (int)((red1 * (b2 - b) + red2 * (b - b1)) / diff) * 0x10000; // calculate red   color component
                    color += (int)((gre1 * (b2 - b) + gre2 * (b - b1)) / diff) * 0x100; // calculate green color component
                    color += (int)((blu1 * (b2 - b) + blu2 * (b - b1)) / diff); // calculate blue  color component
                }

                SDL_FillRect(datsurface, &pixelRect, color);
            }
        }
    }
}


//this draws a line on the screen from point (x1,y1) to point (x2,y2)
// this draws the line (mathematically) from the centers of the two pixels.
void draw_line(SDL_Surface *theSurface, int x1, int y1, int x2, int y2, int thickness, int lineColor)
{
    //this is the rectangle describing the pixel to color in.
    SDL_Rect myPixel;
    myPixel.w = 1;
    myPixel.h = 1;

    //handle lines with no x-difference
    if (x1 == x2) {
        // this handles the special case that the line is a point
        if (y1 == y2) {
            // draw a point
            myPixel.x = x1;
            myPixel.y = y1;
            SDL_FillRect(theSurface, &myPixel, lineColor);
            // done drawing a point. that's all folks!
            return;
        }

        //this handles the special case the the line is a verticle line (slope infinity)
        // this swaps the x and y values so that the function draws a line with a finite slope (zero)
        // the myPixel rectangle is no longer a pixel. it is now being used as a vertical line
        myPixel.w = 1;
        myPixel.x = x1;

        if (y2 - y1 >= 0) {
            myPixel.h = y2 - y1;
            myPixel.y = y1;
        } else {
            myPixel.h = y1 - y2;
            myPixel.y = y2;
        }

        SDL_FillRect(theSurface, &myPixel, lineColor);
        return;
    }

    float slope = (float)(y2 - y1) / (float)(x2 - x1);
    //generate an absolute value of the slope
    float absval_slope = slope;

    if (slope < 1) absval_slope *= -1;

    float x, y;
    //this is used to mathematically determine where the line should be.
    float line_value;

    // if the absolute value of the slope is less than 1, index through the x values
    if (absval_slope < 1) {
        //all of this assumes that x1 <= x2
        float pixel_offset = 0.5;
        //x2 is greater than x1
        int low_x = x1;
        int high_x = x2;
        int ref_y = y1;     // this is the reference y. this is where we start

        // this takes care of the special case of x1 being bigger than x2.
        if (x1 > x2) {
            pixel_offset *= -1;
            //x2 is less than x1
            low_x = x2;
            high_x = x1;
            ref_y = y2;
        }

        for (x = low_x + pixel_offset, myPixel.x = low_x; x < high_x; x += 1, myPixel.x++) {
            line_value = (x - low_x) * slope + ref_y;
            myPixel.y = line_value; // integer assignment. truncate decimal places

            // if the line_value has decimal place value greater than or equal to 0.5, then round up.
            if (line_value - (int)line_value > 0.5) myPixel.y++;

            // only print the pixel if it is within the screen bounds
            if (myPixel.x >= 0 && myPixel.x < SCREEN_WIDTH && myPixel.y >= 0 && myPixel.y < SCREEN_HEIGHT)
                SDL_FillRect(theSurface, &myPixel, lineColor);
        }
    }
    // otherwise, the absolute value of the slope is greater to or equal to one, so index through the y values
    else {
        //all of this assumes that y1 <= y2
        float pixel_offset = 0.5;
        //y2 is greater than y1
        int low_y = y1;
        int high_y = y2;
        int ref_x = x1;     // this is the reference x. this is where we start

        // this takes care of the special case of y1 being bigger than y2.
        if (y1 > y2) {
            pixel_offset *= -1;
            //y2 is less than y1
            low_y = y2;
            high_y = y1;
            ref_x = x2;
        }

        for (y = low_y + pixel_offset, myPixel.y = low_y; y < high_y; y += 1, myPixel.y++) {
            line_value = (y - low_y) / slope + ref_x;
            myPixel.x = line_value; // integer assignment. truncate decimal places

            // if the line_value has decimal place value greater than or equal to 0.5, then round up.
            if (line_value - (int)line_value > 0.5) myPixel.x++;

            // only print the pixel if it is within the screen bounds
            if (myPixel.x >= 0 && myPixel.x < SCREEN_WIDTH && myPixel.y >= 0 && myPixel.y < SCREEN_HEIGHT)
                SDL_FillRect(theSurface, &myPixel, lineColor);
        }
    }
}

void saveToBitmap(char *filename, SDL_Surface *toSave, int x, int y)
{
    if (!toSave) {
        fprintf(stderr, "NON FATAL ERROR : SDL_RenderReadPixels() has failed  : %s\n", SDL_GetError());
        return;
    }

    if (SDL_SaveBMP(toSave, filename) != 0) {
        fprintf(stderr, "NON FATAL ERROR : SDL_SaveBMP() has failed  : %s\n", SDL_GetError());
    }
}

void Gradient(SDL_Surface *Screen, SDL_Color Color,
              int StartX, int StartY, int EndX, int EndY)
{
    Uint8 R, G, B;
    int X;

    for (X = StartX; X < (StartX + EndX); X++) {
        int Y;

        for (Y = StartY; Y < (StartY + EndY); Y++) {
            R = (Color.r * ((StartX + EndX + StartY + EndY) - (Y + X)) /
                 (StartX + EndX + StartY + EndY));
            G = (Color.g * ((StartX + EndX + StartY + EndY) - (Y + X)) /
                 (StartX + EndX + StartY + EndY));
            B = (Color.b * ((StartX + EndX + StartY + EndY) - (Y + X)) /
                 (StartX + EndX + StartY + EndY));
            Uint32 PixelColor = SDL_MapRGB(Screen->format, R, G, B);
            Uint32 *Bufp;
            Bufp = (Uint32 *)Screen->pixels + Y * Screen->pitch / 4 + X;
            *Bufp = PixelColor;
        }
    }
}




int _tmain(int argc, _TCHAR* argv[])
{
    SDL_Window* mainWindow = NULL;
    SDL_Surface* screen = NULL;
    SDL_Event event;
    bool done = false;
    int flag = 0;
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    SCREEN_WIDTH = desktop.right;
    SCREEN_HEIGHT = desktop.bottom;
    std::cout << "width:" << SCREEN_WIDTH << " height:" << SCREEN_HEIGHT;
    mainWindow = SDL_CreateWindow("SDL basic test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    screen = SDL_GetWindowSurface(mainWindow);
    std::cout << "Hello World SDL!!!!!" << std::endl;

    while (!done) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    done = true;
                    break;

                case SDLK_1:
                    flag = 1;
                    break;

                case SDLK_2:
                    flag = 2;
                    break;

                case SDLK_3:
                    flag = 3;
                    break;

                case SDLK_4:
                    flag = 4;
                    break;

                case SDLK_5:
                    flag = 5;
                    break;

                case SDLK_6:
                    flag = 6;
                    break;

                case SDLK_7:
                    flag = 7;
                    break;

                case SDLK_8:
                    flag = 8;
                    break;

                case SDLK_9:
                    flag = 9;
                    break;

                case SDLK_0:
                    flag = 10;
                    break;

                case SDLK_F7:
                    flag = 11;
                    break;

                case SDLK_F8:
                    flag = 12;
                    break;

                case SDLK_F2:
                    flag = 13;
                    break;

                case SDLK_F3:
                    flag = 14;
                    break;

                case SDLK_F4:
                    flag = 15;
                    break;

                case SDLK_F5:
                    flag = 16;
                    break;

                default:
                    flag++;
                    break;
                }
            }
        }

        switch (flag) {
        case 1:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));     // 白
            break;

        case 2:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));     // 黑
            break;

        case 3:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xF0, 0x00, 0x00));     // 红
            break;

        case 4:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xF0, 0x00));     // 绿
            break;

        case 5:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0xF0));     // 蓝
            break;

        case 6:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xFF, 0xFF));     // 青
            break;

        case 7:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0x00, 0xFF));     // 洋红
            break;

        case 8:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00));     // 黄
            break;

        case 9:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xF0, 0x00));     // 水平渐变
            break;

        case 10:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xF0, 0x00));     // 垂直渐变
            break;

        case 11:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xF0, 0x00));     // 垂直线
            break;

        case 12:
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xF0, 0x00));     // 水平线
            break;

        default:
            //draw_line(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0x00 ));
            SDL_Color mycolor;
            mycolor.r = 0x00;
            mycolor.g = 0xFF;
            mycolor.b = 0x00;
            mycolor.a = 0xFF;
            Gradient(screen,  mycolor, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
        }

        SDL_UpdateWindowSurface(mainWindow);
    }

    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}