/*****************************************************************************************
 * Board.h - Maintains the board array
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
 *
/*****************************************************************************************/

#ifndef _BOARD_
#define _BOARD_

// ------ Includes -----

#include "Piece.h"

// ------ Defines -----

#define BOARD_LINE_WIDTH 6          // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 20               // Width and Height of each block of a piece
#define BOARD_POSITION 512          // Center position of the board from the left of the screen
#define BOARD_WIDTH 10              // Board width in blocks
#define BOARD_HEIGHT 20             // Board height in blocks
#define MIN_VERTICAL_MARGIN 20      // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20    // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5              // Number of horizontal and vertical blocks of a matrix piece


// --------------------------------------------------------------------------------
//                                   Board
// --------------------------------------------------------------------------------

class Board
{
public:

    Board(Piece *pPiece, int pScreenHeight);

    int getXPosInPixels(int pPos);
    int getYPosInPixels(int pPos);
    bool isFreeBlock(int pX, int pY);             //a block in the board

    bool isPossibleMovement(int pX, int pY);      // checks collisions
    void storePiece(int pX, int pY);              // fills an unfilled block in board
    void deletePossibleLines();
    bool isGameOver();
    void updateCurrentPiece(Piece * piece);      // updates current piece
    void clearBoard();
    int storedPieceType(int x, int y);           //used to differenciate while coloring

private:

    enum { POS_FREE, POS_FILLED };          // POS_FREE = free position of the board; POS_FILLED = filled position of the board
    int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the Piece
    Piece* piece;
    int mScreenHeight;

    void initBoard();
    void deleteLine(int pY);
};

#endif // _BOARD_
