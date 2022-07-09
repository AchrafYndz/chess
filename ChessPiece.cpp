#include "ChessPiece.h"
#include "game.h"

std::vector<std::pair<int, int>> Pawn::getValidMoves(Game &g) {
    std::vector<std::pair<int, int>> moves;
    if (getColor() == black) {
        std::pair<int, int> oneFront;
        oneFront.first = curRow + 1;
        oneFront.second = curCol;
        if (oneFront.first > 7);
        else if (g.getPiece(oneFront.first, oneFront.second) == nullptr) {
            moves.push_back(oneFront);
        }
        std::pair<int, int> twoFront;
        twoFront.first = curRow + 2;
        twoFront.second = curCol;
        if (twoFront.first > 7);
        else if (g.getPiece(twoFront.first, twoFront.second) == nullptr &&
                 g.getPiece(oneFront.first, oneFront.second) == nullptr && !moved) {
            moves.push_back(twoFront);
        }
        std::pair<int, int> oneLeftFront;
        oneLeftFront.first = curRow + 1;
        oneLeftFront.second = curCol - 1;
        if (oneLeftFront.second < 0 || oneLeftFront.first > 7);
        else if (g.getPiece(oneLeftFront.first, oneLeftFront.second) == nullptr) {
            if (Pawn *_ = dynamic_cast<Pawn *>(g.getPiece(oneLeftFront.first - 1, oneLeftFront.second))) {
                ChessPiece *pawn = g.getPiece(oneLeftFront.first - 1, oneLeftFront.second);
                if (pawn->isEnPassantable()) {
                    moves.push_back(oneLeftFront);
                }
            }
        } else if (g.getPiece(oneLeftFront.first, oneLeftFront.second) != nullptr &&
                   g.getPiece(oneLeftFront.first, oneLeftFront.second)->getColor() == white) {
            moves.push_back(oneLeftFront);
        }
        std::pair<int, int> oneRightFront;
        oneRightFront.first = curRow + 1;
        oneRightFront.second = curCol + 1;
        if (oneRightFront.second > 7 || oneRightFront.first > 7);
        else if (g.getPiece(oneRightFront.first, oneRightFront.second) == nullptr) {
            if (Pawn *_ = dynamic_cast<Pawn *>(g.getPiece(oneRightFront.first - 1, oneRightFront.second))) {
                ChessPiece *pawn = g.getPiece(oneRightFront.first - 1, oneRightFront.second);
                if (pawn->isEnPassantable()) {
                    moves.push_back(oneRightFront);
                }
            }
        } else if (g.getPiece(oneRightFront.first, oneRightFront.second) != nullptr &&
                   g.getPiece(oneRightFront.first, oneRightFront.second)->getColor() == white) {
            moves.push_back(oneRightFront);
        }
    } else if (getColor() == white) {
        std::pair<int, int> oneFront;
        oneFront.first = curRow - 1;
        oneFront.second = curCol;
        if (oneFront.first < 0);
        else if (g.getPiece(oneFront.first, oneFront.second) == nullptr && oneFront.first >= 0) {
            moves.push_back(oneFront);
        }
        std::pair<int, int> twoFront;
        twoFront.first = curRow - 2;
        twoFront.second = curCol;
        if (twoFront.first < 0);
        else if (g.getPiece(twoFront.first, twoFront.second) == nullptr &&
                 g.getPiece(oneFront.first, oneFront.second) == nullptr && !moved) {
            moves.push_back(twoFront);
        }
        std::pair<int, int> oneLeftFront;
        oneLeftFront.first = curRow - 1;
        oneLeftFront.second = curCol - 1;
        if (oneLeftFront.second < 0 || oneLeftFront.first < 0);
        else if (g.getPiece(oneLeftFront.first, oneLeftFront.second) == nullptr) {
            if (Pawn *_ = dynamic_cast<Pawn *>(g.getPiece(oneLeftFront.first + 1, oneLeftFront.second))) {
                ChessPiece *pawn = g.getPiece(oneLeftFront.first + 1, oneLeftFront.second);
                if (pawn->isEnPassantable()) {
                    moves.push_back(oneLeftFront);
                }
            }
        } else if (g.getPiece(oneLeftFront.first, oneLeftFront.second) != nullptr &&
                   g.getPiece(oneLeftFront.first, oneLeftFront.second)->getColor() == black) {
            moves.push_back(oneLeftFront);
        }
        std::pair<int, int> oneRightFront;
        oneRightFront.first = curRow - 1;
        oneRightFront.second = curCol + 1;
        if (oneRightFront.second > 7 || oneRightFront.first < 0);
        else if (g.getPiece(oneRightFront.first, oneRightFront.second) == nullptr) {
            if (Pawn *_ = dynamic_cast<Pawn *>(g.getPiece(oneRightFront.first + 1, oneRightFront.second))) {
                ChessPiece *pawn = g.getPiece(oneRightFront.first + 1, oneRightFront.second);
                if (pawn->isEnPassantable()) {
                    moves.push_back(oneRightFront);
                }
            }
        } else if (g.getPiece(oneRightFront.first, oneRightFront.second) != nullptr &&
                   g.getPiece(oneRightFront.first, oneRightFront.second)->getColor() == black) {
            moves.push_back(oneRightFront);
        }
    }
    return moves;
}

void Pawn::setMoved(bool b) {
    moved = b;
}

bool Pawn::getMoved() {
    return moved;
}

void Pawn::setEnPassantable(bool b) {
    enPassantable = b;
}

bool Pawn::isEnPassantable() {
    return enPassantable;
}

std::vector<std::pair<int, int>> Rook::getValidMoves(Game &g) {
    std::vector<std::pair<int, int>> moves;
    bw color = getColor();
    for (int i = curRow; i <= 7; i++) {
        if (i == curRow) continue;
        std::pair<int, int> colAbove;
        colAbove.first = i;
        colAbove.second = curCol;
        if (g.getPiece(colAbove.first, colAbove.second) != nullptr) {
            if (g.getPiece(colAbove.first, colAbove.second)->getColor() != color) {
                moves.push_back(colAbove);
            }
            break;
        }
        moves.push_back(colAbove);
    }
    for (int i = curRow; i >= 0; i--) {
        if (i == curRow) continue;
        std::pair<int, int> colBelow;
        colBelow.first = i;
        colBelow.second = curCol;
        if (g.getPiece(colBelow.first, colBelow.second) != nullptr) {
            if (g.getPiece(colBelow.first, colBelow.second)->getColor() != color) {
                moves.push_back(colBelow);
            }
            break;
        }
        moves.push_back(colBelow);
    }

    for (int i = curCol; i <= 7; i++) {
        if (i == curCol) continue;
        std::pair<int, int> rowRight;
        rowRight.first = curRow;
        rowRight.second = i;
        if (g.getPiece(rowRight.first, rowRight.second) != nullptr) {
            if (g.getPiece(rowRight.first, rowRight.second)->getColor() != color) {
                moves.push_back(rowRight);
            }
            break;
        }
        moves.push_back(rowRight);
    }
    for (int i = curCol; i >= 0; i--) { // naar links loopen
        if (i == curCol) continue;
        std::pair<int, int> rowLeft;
        rowLeft.first = curRow;
        rowLeft.second = i;
        if (g.getPiece(rowLeft.first, rowLeft.second) != nullptr) {
            if (g.getPiece(rowLeft.first, rowLeft.second)->getColor() != color) {
                moves.push_back(rowLeft);
            }
            break;
        }
        moves.push_back(rowLeft);
    }
    return moves;
}

void Rook::setMoved(bool m) {
    moved = m;
}

bool Rook::getMoved() {
    return moved;
}

std::vector<std::pair<int, int>> Knight::getValidMoves(Game &g) {
    std::vector<std::pair<int, int>> moves;
    int X[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    bw color = getColor();
    for (int i = 0; i < 8; i++) {
        std::pair<int, int> LShape;
        LShape.first = curRow + X[i];
        LShape.second = curCol + Y[i];
        if (LShape.first < 0 || LShape.first > 7 || LShape.second < 0 || LShape.second > 7) {
            continue;
        }
        if (g.getPiece(LShape.first, LShape.second) == nullptr ||
            g.getPiece(LShape.first, LShape.second)->getColor() != color) {
            moves.push_back(LShape);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> Bishop::getValidMoves(Game &g) {
    bw color = getColor();
    std::vector<std::pair<int, int>> moves;
    int leftAbove = std::min(curRow, curCol);
    for (int i = 1; i <= leftAbove; i++) {
        std::pair<int, int> diagonalLeftAbove;
        diagonalLeftAbove.first = curRow - i;
        diagonalLeftAbove.second = curCol - i;
        if (g.getPiece(diagonalLeftAbove.first, diagonalLeftAbove.second) != nullptr) {
            if (g.getPiece(diagonalLeftAbove.first, diagonalLeftAbove.second)->getColor() != color) {
                moves.push_back(diagonalLeftAbove);
            }
            break;
        }
        moves.push_back(diagonalLeftAbove);
    }
    int rightAbove = std::min(curRow, 7 - curCol);
    for (int i = 1; i <= rightAbove; i++) {
        std::pair<int, int> diagonalRightAbove;
        diagonalRightAbove.first = curRow - i;
        diagonalRightAbove.second = curCol + i;
        if (g.getPiece(diagonalRightAbove.first, diagonalRightAbove.second) != nullptr) {
            if (g.getPiece(diagonalRightAbove.first, diagonalRightAbove.second)->getColor() != color) {
                moves.push_back(diagonalRightAbove);
            }
            break;
        }
        moves.push_back(diagonalRightAbove);
    }
    int leftBelow = 7 - std::max(curRow, 7 - curCol);
    for (int i = 1; i <= leftBelow; i++) {
        std::pair<int, int> diagonalLeftBelow;
        diagonalLeftBelow.first = curRow + i;
        diagonalLeftBelow.second = curCol - i;
        if (g.getPiece(diagonalLeftBelow.first, diagonalLeftBelow.second) != nullptr) {
            if (g.getPiece(diagonalLeftBelow.first, diagonalLeftBelow.second)->getColor() != color) {
                moves.push_back(diagonalLeftBelow);
            }
            break;
        }
        moves.push_back(diagonalLeftBelow);
    }
    int rightBelow = 7 - std::max(curRow, curCol);
    for (int i = 1; i <= rightBelow; i++) {
        std::pair<int, int> diagonalRightBelow;
        diagonalRightBelow.first = curRow + i;
        diagonalRightBelow.second = curCol + i;
        if (g.getPiece(diagonalRightBelow.first, diagonalRightBelow.second) != nullptr) {
            if (g.getPiece(diagonalRightBelow.first, diagonalRightBelow.second)->getColor() != color) {
                moves.push_back(diagonalRightBelow);
            }
            break;
        }
        moves.push_back(diagonalRightBelow);
    }
    return moves;
}

std::vector<std::pair<int, int>> King::getValidMoves(Game &g) {
    std::vector<std::pair<int, int>> moves;
    bw color = getColor();
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r == 0 && c == 0) {
                continue;
            }
            std::pair<int, int> move;
            move.first = curRow + r;
            move.second = curCol + c;
            if (move.first < 0 || move.first > 7 || move.second < 0 || move.second > 7) {
                continue;
            }
            if (g.getPiece(move.first, move.second) == nullptr ||
                g.getPiece(move.first, move.second)->getColor() != color) {
                moves.push_back(move);
            }
        }
    }
    if (!moved && curCol == 4) {
        ChessPiece *rechtertoren = g.getPiece(curRow, curCol + 3);
        if (Rook *_ = dynamic_cast<Rook *>(rechtertoren)) {
            if (!rechtertoren->getMoved()) {
                std::pair<int, int> move;
                move.first = curRow;
                move.second = curCol + 2;
                moves.push_back(move);
            }
        }
        ChessPiece *linkertoren = g.getPiece(curRow, curCol - 4);
        if (Rook *_ = dynamic_cast<Rook *>(linkertoren)) {
            if (!linkertoren->getMoved()) {
                std::pair<int, int> move;
                move.first = curRow;
                move.second = curCol - 2;
                moves.push_back(move);
            }
        }
    }
    return moves;
}

void King::setMoved(bool m) {
    moved = m;
}

bool King::getMoved() {
    return moved;
}

std::vector<std::pair<int, int>> Queen::getValidMoves(Game &g) {
    bw color = getColor();
    std::vector<std::pair<int, int>> moves;

    int leftAbove = std::min(curRow, curCol);
    for (int i = 1; i <= leftAbove; i++) {
        std::pair<int, int> diagonalLeftAbove;
        diagonalLeftAbove.first = curRow - i;
        diagonalLeftAbove.second = curCol - i;
        if (g.getPiece(diagonalLeftAbove.first, diagonalLeftAbove.second) != nullptr) {
            if (g.getPiece(diagonalLeftAbove.first, diagonalLeftAbove.second)->getColor() != color) {
                moves.push_back(diagonalLeftAbove);
            }
            break;
        }
        moves.push_back(diagonalLeftAbove);
    }

    int rightAbove = std::min(curRow, 7 - curCol);
    for (int i = 1; i <= rightAbove; i++) {
        std::pair<int, int> diagonalRightAbove;
        diagonalRightAbove.first = curRow - i;
        diagonalRightAbove.second = curCol + i;
        if (g.getPiece(diagonalRightAbove.first, diagonalRightAbove.second) != nullptr) {
            if (g.getPiece(diagonalRightAbove.first, diagonalRightAbove.second)->getColor() != color) {
                moves.push_back(diagonalRightAbove);
            }
            break;
        }
        moves.push_back(diagonalRightAbove);
    }

    int leftBelow = 7 - std::max(curRow, 7 - curCol);
    for (int i = 1; i <= leftBelow; i++) {
        std::pair<int, int> diagonalLeftBelow;
        diagonalLeftBelow.first = curRow + i;
        diagonalLeftBelow.second = curCol - i;
        if (g.getPiece(diagonalLeftBelow.first, diagonalLeftBelow.second) != nullptr) {
            if (g.getPiece(diagonalLeftBelow.first, diagonalLeftBelow.second)->getColor() != color) {
                moves.push_back(diagonalLeftBelow);
            }
            break;
        }
        moves.push_back(diagonalLeftBelow);
    }
    int rightBelow = 7 - std::max(curRow, curCol);
    for (int i = 1; i <= rightBelow; i++) {
        std::pair<int, int> diagonalRightBelow;
        diagonalRightBelow.first = curRow + i;
        diagonalRightBelow.second = curCol + i;
        if (g.getPiece(diagonalRightBelow.first, diagonalRightBelow.second) != nullptr) {
            if (g.getPiece(diagonalRightBelow.first, diagonalRightBelow.second)->getColor() != color) {
                moves.push_back(diagonalRightBelow);
            }
            break;
        }
        moves.push_back(diagonalRightBelow);
    }

    for (int i = curRow; i <= 7; i++) {
        if (i == curRow) continue;
        std::pair<int, int> colAbove;
        colAbove.first = i;
        colAbove.second = curCol;
        if (g.getPiece(colAbove.first, colAbove.second) != nullptr) {
            if (g.getPiece(colAbove.first, colAbove.second)->getColor() != color) {
                moves.push_back(colAbove);
            }
            break;
        }
        moves.push_back(colAbove);
    }
    for (int i = curRow; i >= 0; i--) {
        if (i == curRow) continue;
        std::pair<int, int> colBelow;
        colBelow.first = i;
        colBelow.second = curCol;
        if (g.getPiece(colBelow.first, colBelow.second) != nullptr) {
            if (g.getPiece(colBelow.first, colBelow.second)->getColor() != color) {
                moves.push_back(colBelow);
            }
            break;
        }
        moves.push_back(colBelow);
    }

    for (int i = curCol; i <= 7; i++) {
        if (i == curCol) continue;
        std::pair<int, int> rowRight;
        rowRight.first = curRow;
        rowRight.second = i;
        if (g.getPiece(rowRight.first, rowRight.second) != nullptr) {
            if (g.getPiece(rowRight.first, rowRight.second)->getColor() != color) {
                moves.push_back(rowRight);
            }
            break;
        }
        moves.push_back(rowRight);
    }

    for (int i = curCol; i >= 0; i--) {
        if (i == curCol) continue;
        std::pair<int, int> rowLeft;
        rowLeft.first = curRow;
        rowLeft.second = i;
        if (g.getPiece(rowLeft.first, rowLeft.second) != nullptr) {
            if (g.getPiece(rowLeft.first, rowLeft.second)->getColor() != color) {
                moves.push_back(rowLeft);
            }
            break;
        }
        moves.push_back(rowLeft);
    }
    return moves;
}
