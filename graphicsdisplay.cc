#include "graphicsdisplay.h"
#include "board.h"
#include "piece.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow &window, int gridSize) : window(window), gridSize(gridSize) {}

void GraphicsDisplay::notify(const Board &board, int srcRow, int srcCol, int destRow, int destCol) {
    int boardSize = 440;  // Size of the chessboard area
    int padding = 30;     // Padding around the board for indices
    int totalSize = boardSize + padding * 2;  // Total window size including padding
    int pixels = boardSize / gridSize;  // Size of each square in the grid

    auto state = board.getState();  // Get the current state of the board

    // Offset for drawing the board inside the padding
    int offsetX = padding;
    int offsetY = padding;

    // Calculate the positions of the affected squares
    int srcX = offsetX + srcCol * pixels;
    int srcY = offsetY + (gridSize - 1 - srcRow) * pixels;
    int destX = offsetX + destCol * pixels;
    int destY = offsetY + (gridSize - 1 - destRow) * pixels;

    // Determine the color of the squares
    int srcColor = (srcRow + srcCol) % 2 == 0 ? Xwindow::White : Xwindow::Black;
    int destColor = (destRow + destCol) % 2 == 0 ? Xwindow::White : Xwindow::Black;

    // Clear the source and destination squares
    window.fillRectangle(srcX, srcY, pixels, pixels, srcColor);
    window.fillRectangle(destX, destY, pixels, pixels, destColor);

    Piece *srcPiece = state[srcRow][srcCol];
    Piece *destPiece = state[destRow][destCol];

    if (srcRow == 0 && srcCol == 0 && destRow == 0 && destCol == 0) {
        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridSize; ++col) {
                Piece *piece = state[row][col];

                // Determine the color of the square (checker pattern)
                int color = (row + col) % 2 == 0 ? Xwindow::White : Xwindow::Black;

                // Calculate the y position from the bottom of the board
                int yPos = offsetY + (gridSize - 1 - row) * pixels;

                // Draw the square with offset
                window.fillRectangle(offsetX + col * pixels, yPos, pixels, pixels, color);

                // If there's a piece on this square, draw it
                if (piece != nullptr) {
                    char pieceChar = piece->displayChar();  // Assuming Piece has a method to return a char representing it
                    string pieceStr(1, pieceChar);

                    unsigned long colour = (piece->getColour() == "white") ? 0xFF0000 : 0x0000FF;

                    // Draw the piece on the board
                    window.drawString(offsetX + col * pixels + pixels / 2, yPos + pixels / 2, pieceStr, colour);
                }
            }

        // Draw row numbers on the left side of the board, original positions
        window.drawString(5, offsetY + row * pixels + pixels / 2, std::to_string(8 - row), 0x000000);
        }
    } else {
        // Draw the source piece, if it exists
        if (srcPiece != nullptr) {
            char srcPieceChar = srcPiece->displayChar();  // Assuming Piece has a method to return a char representing it
            string srcPieceStr(1, srcPieceChar);
            unsigned long srcColour = (srcPiece->getColour() == "white") ? 0xFF0000 : 0x0000FF;
            window.drawString(srcX + pixels / 2, srcY + pixels / 2, srcPieceStr, srcColour);
        }

        // Draw the destination piece, if it exists
        if (destPiece != nullptr) {
            char destPieceChar = destPiece->displayChar();  // Assuming Piece has a method to return a char representing it
            string destPieceStr(1, destPieceChar);
            unsigned long destColour = (destPiece->getColour() == "white") ? 0xFF0000 : 0x0000FF;
            window.drawString(destX + pixels / 2, destY + pixels / 2, destPieceStr, destColour);
        }
    }

    // Draw column letters on the bottom of the board
    for (int col = 0; col < gridSize; ++col) {
        window.drawString(offsetY + col * pixels + pixels / 2, 50 + boardSize + 5, std::string(1, 'a' + col), 0x000000);
    }
}

GraphicsDisplay::~GraphicsDisplay() {}
