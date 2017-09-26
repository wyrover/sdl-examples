/*****************************************************************************************
 * Piece.h - Maintains the piece array
 *
 * @author - Abesari Woldeyesus (abesary@bu.edu)
/*****************************************************************************************/

#ifndef _PIECE_
#define _PIECE_
#define SIZE 5
#include <iostream>

// --------------------------------------------------------------------------------
//                                   piece
// --------------------------------------------------------------------------------

class Piece
{
public:
    Piece(int pieceType, int pieceRotation);                    // Constructor

    void rotatePiece(int pieceRotation = 1);         // Rotates Piece array
    int getXInitialPosition();
    int getYInitialPosition();

    int mPiece [5][5];    // Piece array
    int pieceType;        // Piece indicator (0 - 6)

private:
    void getPiece(int pieceType);         // assigns mPiece one of the 7 piece arrays
    enum {ZERO, _I, _L, _Lm, _N, _Nm, _S, _T};
};

#endif // _piece_
