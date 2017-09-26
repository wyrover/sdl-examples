/*****************************************************************************************
 * Game.cpp - Logic of the game
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
 *
/*****************************************************************************************/

#ifndef LINUX
    #include <windows.h>
#endif
#include "Game.h"

/*
======================================
Init
======================================
*/
Game::Game(View *pView, Commands *pCommands, int pScreenHeight)
{
    mScreenHeight = 480;
    view = pView;
    commands = pCommands;
    // Game initialization
    initGame();
}

/*
======================================
Get a random int between two integers

>> pA: First number
>> pB: Second number
======================================
*/
int Game::getRand(int pA, int pB)
{
    return rand() % (pB - pA + 1) + pA;
}

/*
======================================
Create a random piece
- updates current piece to nextPiece
- creates new piece for nextPiece
======================================
*/
void Game::createNewPiece()
{
    // New piece
    piece = nextPiece;
    board->updateCurrentPiece(piece);
    posX          = (BOARD_WIDTH / 2) + piece->getXInitialPosition();
    posY          = piece->getYInitialPosition();
    nextPiece     = new Piece(nextPieceType, nextRotation);
    nextPieceType = getRand(1, 7);
    nextRotation  = getRand(0, 3);
}

/*
 ======================================
 Game initializer
 ======================================
*/
void Game::initGame()
{
    // init random numbers
    srand((unsigned int) time(NULL));
    pieceType     = getRand(1, 7);
    rotation      = getRand(0, 3);
    nextPieceType = getRand(1, 7);
    nextRotation  = getRand(0, 3);
    // initialize first piece, next piece and board
    piece     = new Piece(pieceType, rotation);
    nextPiece = new Piece(nextPieceType, nextRotation);
    board     = new Board(piece, mScreenHeight);
    posX          = (BOARD_WIDTH / 2) + piece->getXInitialPosition();
    posY          = piece->getYInitialPosition();
    nextPosX = 10;
    nextPosY = 0;
}

/*
=============================================
Draw piece
>> pX:      Horizontal position in blocks
>> pY:      Vertical position in blocks
=============================================
*/
void Game::drawPiece(int pX, int pY, Piece* pPiece)
{
    //Piece color
    Piece* pieceToDraw = pPiece;
    color mColor = static_cast<color>(pieceToDraw->pieceType);
    // Obtain the position in pixel in the screen of the block we want to draw
    int xPosInPixels = board->getXPosInPixels(pX);
    int yPosInPixels = board->getYPosInPixels(pY);

    //Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            if (pieceToDraw->mPiece[i][j] != 0)
                view->drawBlock(xPosInPixels + i * BLOCK_SIZE,
                                yPosInPixels + j * BLOCK_SIZE,
                                BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                                mColor);
        }
    }
}

/*
======================================
Draw board

Draw the two lines that delimit the board
======================================
*/
void Game::drawBoard()
{
    // Calculate the limits of the board in pixels
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);
    // Rectangles that delimits the board
    view->drawBlock(mX1 - BOARD_LINE_WIDTH, mY, BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);
    view->drawBlock(mX2, mY, BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);
    view->drawBlock(mX1, mScreenHeight, BLOCK_SIZE * BOARD_WIDTH, BOARD_LINE_WIDTH, BLUE);
    mX1++;
    color mColor;

    // Rectangles that represent the stored pieces on the board
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mColor = static_cast<color>(board->storedPieceType(i, j));

            //Draw the blocks that have been filled
            if (!board->isFreeBlock(i, j)) {
                view->drawBlock(mX1 + i * BLOCK_SIZE,
                                mY + j * BLOCK_SIZE,
                                BLOCK_SIZE - 1, BLOCK_SIZE - 1,
                                mColor);
            }
        }
    }
}

/*
======================================
draw scene

Draw all the objects of the scene
======================================
*/
void Game::drawScene()
{
    view->clearScreen();                        // Clear Screen for rendering
    view->loadBackGround();                     // Load background image
    drawBoard();                                // Draw the delimitation lines and blocks stored in the board
    drawPiece(posX, posY, piece);               // Draw the playing piece
    drawPiece(nextPosX, nextPosY, nextPiece);   // Draw the next piece
    view->updateScreen();
}

/*
====================================================
restart

Prompts user if they want to play again and clears the board
====================================================
*/
bool Game::restart()
{
    int response = view->messageBox();

    if (response) {
        board->clearBoard();
        return true;
    } else return false;
}
