#include <iostream>
#include <utility>
#include "game.h"
#include "ChessPiece.h"

Game::Game() {
    std::vector<ChessPiece *> row(8, nullptr);
    board[0] = row;
    for (int r = 0; r < 7; r++) {
        board.push_back(row);
    }
    setStartingBoard();
}

Game::~Game() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            delete getPiece(r, c);
        }
    }
}

void Game::setStartingBoard() {
    ChessPiece *whitePawn1 = new Pawn(white);
    ChessPiece *whitePawn2 = new Pawn(white);
    ChessPiece *whitePawn3 = new Pawn(white);
    ChessPiece *whitePawn4 = new Pawn(white);
    ChessPiece *whitePawn5 = new Pawn(white);
    ChessPiece *whitePawn6 = new Pawn(white);
    ChessPiece *whitePawn7 = new Pawn(white);
    ChessPiece *whitePawn8 = new Pawn(white);

    ChessPiece *blackPawn1 = new Pawn(black);
    ChessPiece *blackPawn2 = new Pawn(black);
    ChessPiece *blackPawn3 = new Pawn(black);
    ChessPiece *blackPawn4 = new Pawn(black);
    ChessPiece *blackPawn5 = new Pawn(black);
    ChessPiece *blackPawn6 = new Pawn(black);
    ChessPiece *blackPawn7 = new Pawn(black);
    ChessPiece *blackPawn8 = new Pawn(black);

    ChessPiece *whiteRook1 = new Rook(white);
    ChessPiece *whiteRook2 = new Rook(white);

    ChessPiece *blackRook1 = new Rook(black);
    ChessPiece *blackRook2 = new Rook(black);

    ChessPiece *whiteKnight1 = new Knight(white);
    ChessPiece *whiteKnight2 = new Knight(white);

    ChessPiece *blackKnight1 = new Knight(black);
    ChessPiece *blackKnight2 = new Knight(black);

    ChessPiece *whiteBishop1 = new Bishop(white);
    ChessPiece *whiteBishop2 = new Bishop(white);

    ChessPiece *blackBishop1 = new Bishop(black);
    ChessPiece *blackBishop2 = new Bishop(black);

    ChessPiece *whiteQueen = new Queen(white);

    ChessPiece *blackQueen = new Queen(black);

    ChessPiece *whiteKing = new King(white);

    ChessPiece *blackKing = new King(black);

    setPiece(0, 0, blackRook1);
    setPiece(0, 7, blackRook2);
    setPiece(0, 1, blackKnight1);
    setPiece(0, 6, blackKnight2);
    setPiece(0, 2, blackBishop1);
    setPiece(0, 5, blackBishop2);
    setPiece(0, 3, blackQueen);
    setPiece(0, 4, blackKing);
    setPiece(1, 0, blackPawn1);
    setPiece(1, 1, blackPawn2);
    setPiece(1, 2, blackPawn3);
    setPiece(1, 3, blackPawn4);
    setPiece(1, 4, blackPawn5);
    setPiece(1, 5, blackPawn6);
    setPiece(1, 6, blackPawn7);
    setPiece(1, 7, blackPawn8);
    for (int r = 2; r < 7; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
    setPiece(7, 0, whiteRook1);
    setPiece(7, 7, whiteRook2);
    setPiece(7, 1, whiteKnight1);
    setPiece(7, 6, whiteKnight2);
    setPiece(7, 2, whiteBishop1);
    setPiece(7, 5, whiteBishop2);
    setPiece(7, 3, whiteQueen);
    setPiece(7, 4, whiteKing);
    setPiece(6, 0, whitePawn1);
    setPiece(6, 1, whitePawn2);
    setPiece(6, 2, whitePawn3);
    setPiece(6, 3, whitePawn4);
    setPiece(6, 4, whitePawn5);
    setPiece(6, 5, whitePawn6);
    setPiece(6, 6, whitePawn7);
    setPiece(6, 7, whitePawn8);
}


bool Game::move(ChessPiece *p, int r, int c) {
    std::vector<std::pair<int, int>> valid = p->getValidMoves(*this);
    std::pair<int, int> newPos;
    newPos.first = r;
    newPos.second = c;
    std::vector<std::vector<ChessPiece *>> prev_bord = this->board;
    if (find(valid.begin(), valid.end(), newPos) !=
        valid.end()) {
        int prevRow = p->curRow;
        int prevCol = p->curCol;

        if (King *_ = dynamic_cast<King *>(p)) {
            if (abs(p->curCol - c) > 1) {
                if (p->curCol > c) {
                    for (int i = 1; i <= p->curCol; i++) {
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }

                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
                                    std::vector<std::pair<int, int>> localValid = p->getValidMoves(*this);
                                    for (auto g: localValid) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    setPiece(r, c, p);
                    ChessPiece *rook = getPiece(r, 0);
                    setPiece(r, c + 1, rook);
                    setPiece(r, 0, nullptr);
                    setPiece(prevRow, prevCol, nullptr);
                    return true;
                } else {
                    for (int i = p->curCol; i < 7; i++) {
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
                                    std::vector<std::pair<int, int>> validMoves = p->getValidMoves(*this);
                                    for (auto g: validMoves) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    setPiece(r, c, p);
                    ChessPiece *rook = getPiece(r, 7);
                    setPiece(r, c - 1, rook);
                    setPiece(r, 7, nullptr);
                    setPiece(prevRow, prevCol, nullptr);
                    return true;
                }
            }
        }

        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            if (abs(c - p->curCol) == 1) {
                if (getPiece(r, c) == nullptr) {
                    setPiece(r, c, p);
                    if (p->getColor() == black) {
                        delete getPiece(r - 1, c);
                        setPiece(r - 1, c, nullptr);
                    } else {
                        delete getPiece(r + 1, c);
                        setPiece(r + 1, c, nullptr);
                    }
                    setPiece(prevRow, prevCol, nullptr);
                    return true;
                }
            }
        }

        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            if (r == 0 || r == 7) {
                delete getPiece(r, c);
                setPiece(r, c, new Queen{p->getColor()});
                setPiece(prevRow, prevCol, nullptr);
                return true;
            }
        }

        setPiece(p->curRow, p->curCol, nullptr);
        ChessPiece *prevPiece = getPiece(r, c);
        setPiece(r, c, p);

        if (check(p->getColor())) {
            setPiece(prevRow, prevCol, p);
            setPiece(r, c, prevPiece);
            return false;
        }

        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            p->setMoved(true);
            if (abs(r - prevRow) == 2) {
                p->setEnPassantable(true);
            }
        }

        if (Rook *_ = dynamic_cast<Rook *>(p)) {
            p->setMoved(true);
        }
        if (King *_ = dynamic_cast<King *>(p)) {
            p->setMoved(true);
        }

        return true;
    };
    return false;
}

bool Game::move_wo_delete(ChessPiece *p, int r, int c) {
    std::vector<std::pair<int, int>> validMoves = p->getValidMoves(*this);
    std::pair<int, int> nieuwe_pos;
    nieuwe_pos.first = r;
    nieuwe_pos.second = c;
    std::vector<std::vector<ChessPiece *>> prev_bord = this->board;
    if (find(validMoves.begin(), validMoves.end(), nieuwe_pos) !=
        validMoves.end()) {
        int old_row = p->curRow;
        int old_col = p->curCol;

        if (King *_ = dynamic_cast<King *>(p)) {
            if (abs(p->curCol - c) > 1) {
                if (p->curCol > c) {
                    for (int i = 1; i <= p->curCol; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
//                                    std::vector<std::pair<int, int>> localValidMoves = p->getValidMoves(*this);
                                    for (auto g: validMoves) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move validMoves
                    setPiece(r, c, p); // zet de koning alvast daar
                    ChessPiece *toren = getPiece(r, 0); // get de linkse toren
                    setPiece(r, c + 1, toren); // zet die 1 rechts van de koning
                    setPiece(r, 0, nullptr); // verwijder de toren van zijn vorige positie
                    setPiece(old_row, old_col, nullptr); // verwijder de koning van zijn vorige positie
                    return true;
                } else { // als we naar rechts bewegen
                    // analoog als hierboven
                    for (int i = p->curCol; i < 7; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
                                    std::vector<std::pair<int, int>> geldig = p->getValidMoves(*this);
                                    for (auto g: geldig) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move validMoves
                    setPiece(r, c, p);
                    ChessPiece *toren = getPiece(r, 7);
                    setPiece(r, c - 1, toren);
                    setPiece(r, 7, nullptr);
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // voer en en passant move uit
        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            if (abs(c - p->curCol) == 1) {
                if (getPiece(r, c) == nullptr) {
                    setPiece(r, c, p);
                    if (p->getColor() == black) {
                        setPiece(r - 1, c, nullptr);
                    } else {
                        setPiece(r + 1, c, nullptr);
                    }
                    setPiece(old_row, old_col, nullptr);
                    return true;
                }
            }
        }

        // promotie
        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            if (r == 0 || r == 7) {
                setPiece(r, c, new Queen{p->getColor()});
                setPiece(old_row, old_col, nullptr);
                return true;
            }
        }

        setPiece(p->curRow, p->curCol, nullptr);
        ChessPiece *prev_piece = getPiece(r, c);
        setPiece(r, c, p);
        if (p->getColor() == black && check(black)) {
            setPiece(old_row, old_col, p);
            setPiece(r, c, prev_piece);
            return false;
        }
        if (p->getColor() == white && check(white)) {
            setPiece(old_row, old_col, p);
            setPiece(r, c, prev_piece);
            return false;
        }
        // maak een pion 'en passantable'
        if (Pawn *_ = dynamic_cast<Pawn *>(p)) {
            p->setMoved(true);
            if (abs(r - old_row) == 2) {
                p->setEnPassantable(true);
            }
        }

        if (Rook *_ = dynamic_cast<Rook *>(p)) {
            p->setMoved(true);
        }
        if (King *_ = dynamic_cast<King *>(p)) {
            p->setMoved(true);
        }

        return true;
    };
    return false;
}

bool Game::validateMove(ChessPiece *p, int r, int c) {
    std::vector<std::pair<int, int>> geldig = p->getValidMoves(*this);
    std::pair<int, int> nieuwe_pos;
    nieuwe_pos.first = r;
    nieuwe_pos.second = c;
    int old_row = p->curRow;
    int old_col = p->curCol;
    std::vector<std::vector<ChessPiece *>> origineel_bord = this->board;
    if (find(geldig.begin(), geldig.end(), nieuwe_pos) !=
        geldig.end()) {// als de nieuwe positie in de geldige zetten zit
        // rokeren
        if (King *_ = dynamic_cast<King *>(p)) { // als een koning gaat bewegen...
            if (abs(p->curCol - c) > 1) { // en die gaat meer dan 1 vakje naar rechts of links
                if (p->curCol > c) { // als we naar links rokeren
                    for (int i = 1; i <= p->curCol; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
                                    std::vector<std::pair<int, int>> geldig = p->getValidMoves(*this);
                                    for (auto g: geldig) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    return true;
                } else { // als we naar rechts bewegen
                    // analoog als hierboven
                    for (int i = p->curCol; i < 7; i++) {
                        // dan checken we eerst dat er geen pieces tussen staan
                        if (i != p->curCol && getPiece(p->curRow, i) != nullptr) {
                            return false;
                        }
                        // en vervolgens checken we dat er geen stukken van de tegenstander deze vakjes 'coveren'
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                ChessPiece *enemy = getPiece(a, b);
                                if (enemy != nullptr && enemy->getColor() != p->getColor()) {
                                    std::vector<std::pair<int, int>> geldig = p->getValidMoves(*this);
                                    for (auto g: geldig) {
                                        if (validateMove(enemy, p->curRow, i)) {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // als die al dit heeft overleeft, is de move geldig
                    return true;
                }
            }
        }


        setPiece(p->curRow, p->curCol, nullptr);
        setPiece(r, c, p);
        if (p->getColor() == black && check(black)) {
            p->curCol = old_col;
            p->curRow = old_row;
            this->board = origineel_bord;
            return false;
        }
        if (p->getColor() == white && check(white)) {
            p->curCol = old_col;
            p->curRow = old_row;
            this->board = origineel_bord;
            return false;
        }
        p->curCol = old_col;
        p->curRow = old_row;
        this->board = origineel_bord;
        return true;
    };
    p->curCol = old_col;
    p->curRow = old_row;
    this->board = origineel_bord;
    return false;
}

bool Game::check(bw color) {
    for (const std::vector<ChessPiece *> &row: this->board) {
        for (ChessPiece *p: row) {
            if (p != nullptr && p->getColor() != color) {
                std::vector<std::pair<int, int>> validMoves = p->getValidMoves(*this);
                for (auto move: validMoves) {
                    ChessPiece *piece = getPiece(move.first, move.second);
                    if (piece != nullptr) {
                        if (King *_ = dynamic_cast<King *>(piece)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::checkmate(bw color) {
    for (const std::vector<ChessPiece *> &row: this->board) {
        for (ChessPiece *p: row) {
            if (p != nullptr && p->getColor() == color) {
                std::vector<std::pair<int, int>> validMoves = p->getValidMoves(*this);
                for (std::pair<int, int> m: validMoves) {
                    if (validateMove(p, m.first, m.second)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Game::stalemate(bw color) {
    for (const std::vector<ChessPiece *> &row: this->board) {
        for (ChessPiece *p: row) {
            if (p != nullptr && p->getColor() == color) {
                std::vector<std::pair<int, int>> validMoves = p->getValidMoves(*this);
                for (std::pair<int, int> m: validMoves) {
                    if (validateMove(p, m.first, m.second)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

ChessPiece *Game::getPiece(int r, int c) {
    ChessPiece *piece = board.at(r).at(c);
    return piece;
}

void Game::setPiece(int r, int c, ChessPiece *p) {
    board[r][c] = p;
    if (p != nullptr) {
        p->curRow = r;
        p->curCol = c;
    }
}

void Game::setBoard(std::vector<std::vector<ChessPiece *>> p) {
    board = std::move(p);
}

std::vector<std::vector<ChessPiece *>> Game::getBoard() {
    return board;
}


