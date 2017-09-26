/*****************************************************************************************
 * Board.cpp - Board of the game. A matrix of n x m holes.
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
 *
/*****************************************************************************************/

// ------includes-------

#include "Board.h"


Board::Board(Piece *pPiece, int pScreenHeight)
{
    // Get the screen height
    mScreenHeight = 480;
    // Get the pointer to the Piece class
    piece = pPiece;
    //Init the board blocks with free positions
    initBoard();
}

/*
======================================
Returns the horizontal position (in pixels) of the block given like parameter

Parameters:

>> pPos:  Horizontal position of the block in the board
======================================
*/
int Board::getXPosInPixels(int pPos)
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

/*
======================================
Returns the vertical position (in pixels) of the block given like parameter

Parameters:

>> pPos:  Horizontal position of the block in the board
======================================
*/
int Board::getYPosInPixels(int pPos)
{
    return (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT) + (pPos * BLOCK_SIZE));
}

/*
======================================
Returns 1 (true) if the this block of the board is empty, 0 if it is filled

Parameters:

>> pX:        Horizontal position in blocks
>> pY:        Vertical position in blocks
======================================
*/
bool Board::isFreeBlock(int pX, int pY)
{
    return (mBoard[pX][pY] == POS_FREE);
}

/*
======================================
Check if the piece can be stored at this position without any collision
Returns true if the movement is  possible, false if it not possible

Parameters:

>> pX:        Horizontal position in blocks
>> pY:        Vertical position in blocks
======================================
*/
bool Board::isPossibleMovement(int pX, int pY)
{
    int boardX, boardY;
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board

//----------------------------------------------------------------------------------------
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        boardX = pX + i;

        for (int j = 0; j < PIECE_BLOCKS; j++) {
            boardY = pY + j;

            // Check if the piece is outside the limits of the board
            if (boardX < 0 || boardX > BOARD_WIDTH - 1 || boardY > BOARD_HEIGHT - 1) {
                if (piece->mPiece[i][j] != 0)
                    return 0;
            }

            // Check if the piece have collisioned with a block already stored in the map
            if (boardY >= 0) {
                if (piece->mPiece[i][j] != 0 && !isFreeBlock(boardX, boardY))
                    return false;
            }
        }
    }

//---------------------------------------------------------------------------------------------
    return true;
}

/*
======================================
Store a piece in the board by filling the blocks

Parameters:

>> pX:        Horizontal position in blocks
>> pY:        Vertical position in blocks
>> pPiece:    Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================
*/
void Board::storePiece(int pX, int pY)
{
    int boardX, boardY;

    // Store each block of the piece into the board
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        boardX = pX + i;

        for (int j = 0; j < PIECE_BLOCKS; j++) {
            boardY = pY + j;

            // Store only the blocks of the piece that are not holes
            if (piece->mPiece[i][j] != 0)
                mBoard[boardX][boardY] = piece->pieceType;
        }
    }
}

/*
======================================
Delete all the lines that should be removed
======================================
*/
void Board::deletePossibleLines()
{
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        int col = 0;

        while (col < BOARD_WIDTH) {
            if (mBoard[col][i] == POS_FREE) break;

            col++;
        }

        if (col == BOARD_WIDTH) deleteLine(i);
    }
}

/*
======================================
Check if the game is over becase a piece have achived the upper position

Returns true or false
======================================
*/
bool Board::isGameOver()
{
    //If the first line has blocks, then, game over
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] != POS_FREE) return true;
    }

    return false;
}

/*
======================================
Delete a line of the board by moving all above lines down

Parameters:

>> pY:        Vertical position in blocks of the line to delete
======================================
*/
void Board::deleteLine(int pY)
{
    // Moves all the upper lines one row down
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mBoard[i][j] = mBoard[i][j - 1];
        }
    }
}

/*
======================================
Init the board blocks with free positions
======================================
*/
void Board::initBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = 0;
        }
}

/*
============================================
next piece
=============================================
*/
void Board::updateCurrentPiece(Piece *piece)
{
    this->piece = piece;
}

void Board::clearBoard()
{
    initBoard();
}

int Board::storedPieceType(int x, int y)
{
    return mBoard[x][y];
}
