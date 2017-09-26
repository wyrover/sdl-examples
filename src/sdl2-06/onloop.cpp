#include"game.h"
void game::OnLoop()
{
    if (scrollRight) {
        position++;
    }

    if (scrollLeft) {
        position--;
    }

    if (position > 49280) {
        position -= 49280;
    }

    if (position < 0) {
        position += 49280;
    }
}
