/*****************************************************************************************
 * Piece.cpp - creates a piece array given a type and rotation
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
/*****************************************************************************************/

#include "Piece.h"

// I
int I [5][5] =      {
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};
// L
int L [5][5] =      {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
};
// L mirrored
int Lm [5][5] =     {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
};
//N
int N [5][5]  =     {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};
//N mirrored
int Nm [5][5]  =    {
    {0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0 , 1, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};
//Square
int S [5][5]  =     {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0}
};
//T
int T [5][5]  =     {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};



/*
==================================================
Piece Constructor

Parameters:
>> pieceType:     one of the seven different pieces
>> pieceRotation: one of the four different orientations a piece can exist in
==================================================
*/
Piece::Piece(int pieceType, int pieceRotation)
{
    // assigns mPiece one of the piece types and rotates it
    this->pieceType = pieceType;
    getPiece(pieceType);
    rotatePiece(pieceRotation);
}

/*
==================================================
getPiece - Assigns one of the Piece arrays to member variable mPiece

>> pieceType: random number 0 - 6, which piece to assign
==================================================
*/
void Piece::getPiece(int pieceType)
{
    switch (pieceType) {
    // I
    case _I:
        std::copy(&I[0][0], &I[0][0] + 25, &mPiece[0][0]);
        break;

    // L
    case _L:
        std::copy(&L[0][0], &L[0][0] + 25, &mPiece[0][0]);
        break;

    // L mirrored
    case _Lm:
        std::copy(&Lm[0][0], &Lm[0][0] + 25, &mPiece[0][0]);
        break;

    //N
    case _N:
        std::copy(&N[0][0], &N[0][0] + 25, &mPiece[0][0]);
        break;

    //N mirrored
    case _Nm:
        std::copy(&Nm[0][0], &Nm[0][0] + 25, &mPiece[0][0]);
        break;

    //Square
    case _S:
        std::copy(&S[0][0], &S[0][0] + 25, &mPiece[0][0]);
        break;

    //T
    case _T:
        std::copy(&T[0][0], &T[0][0] + 25, &mPiece[0][0]);
        break;
    }
}

/*
=======================================
Rotate Piece - Rotates Piece by 90 degrees Clockwise

>> pieceRotation: how many times to rotate
===========================================
*/
void Piece::rotatePiece(int pieceRotation)
{
    int count = 0;

    while (count < pieceRotation) {
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                int temp                           = mPiece[i][j];
                mPiece[i][j]                       = mPiece[SIZE - j - 1][i];
                mPiece[SIZE - j - 1][i]            = mPiece[SIZE - i - 1][SIZE - j - 1];
                mPiece[SIZE - i - 1][SIZE - j - 1] = mPiece[j][SIZE - i - 1];
                mPiece[j][SIZE - i - 1]            = temp;
            }
        }

        count++;
    }
}

/*
===========================================================
Get initial position functions
- sets the pivot of the piece to the center part of the board
============================================================
*/
int Piece::getXInitialPosition()
{
    return -2;
}
int Piece::getYInitialPosition()
{
    //check bottom half of the Piece array
    for (int i = 0; i < SIZE; i++) {
        if (mPiece[3][i] == 1) return -3;

        if (mPiece[4][i] == 1) return -4;
    }

    return -2;
}
