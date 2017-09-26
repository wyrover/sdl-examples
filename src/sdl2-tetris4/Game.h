/*****************************************************************************************
 * Game.h - maintains all game objects
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
 *
/*****************************************************************************************/


#ifndef _GAME_
#define _GAME_

// ------ Includes -----

#include "Board.h"
#include "View.h"
#include "Commands.h"
#include <time.h>

// ------ Defines -----

#define WAIT_TIME 700           // Number of milliseconds that the piece remains before going 1 block down */


// --------------------------------------------------------------------------------
//                                   Game
// --------------------------------------------------------------------------------

class Game
{
public:
    Game(View *pView,
         Commands *pCommands,
         int pScreenHeight);

    void drawScene();
    void createNewPiece();
    bool restart();

    int posX, posY;
    int pieceType, rotation;

    Board *board;
    Piece *piece;
private:
    int mScreenHeight;
    int nextPosX, nextPosY;
    int nextPieceType, nextRotation;

    Piece *nextPiece;
    View *view;
    Commands *commands;

    int getRand(int pA, int pB);      //
    void initGame();    //
    void drawPiece(int pX, int pY/*, color pColor*/, Piece* piece);   //
    void drawBoard();   //
};

#endif // _GAME_
