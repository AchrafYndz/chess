#include <iostream>
#include "ChessGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

ChessGUI::ChessGUI() : ChessWindow(nullptr) {
    update();
}


bool alreadyClicked = false;
int prevRow;
int prevCol;
std::vector<std::pair<int, int>> prevValid;
bw colorToMove = white;
ChessPiece *clickedPiece;
void ChessGUI::clicked(int r, int c) {
    if (not alreadyClicked) {
        prevRow = r;
        prevCol = c;
        clickedPiece = this->g.getPiece(r, c);
        if (clickedPiece == nullptr) {
            return;
        } else if (colorToMove == white && clickedPiece->getColor() != white) {
            message("White to move!");
            return;
        } else if (colorToMove == black && clickedPiece->getColor() != black) {
            message("Black to move!");
            return;
        }

        setTileSelect(r, c, true);

        if (displayMoves()) {
            ChessPiece *p = g.getPiece(r, c);
            bw color = p->getColor();

            std::vector<std::pair<int, int>> validMoves = p->getValidMoves(g);
            prevValid = validMoves;

            std::vector<std::vector<ChessPiece *>> prev_bord = g.getBoard();
            int prevRow = p->curRow;
            int prevCol = p->curCol;
            bool prevMoved = p->getMoved();


            for (std::pair<int, int> m: validMoves) {
                if (King *_ = dynamic_cast<King *>(p)) {
                    if (g.validateMove(p, m.first, m.second)) {
                        setTileFocus(m.first, m.second, true);
                        continue;
                    }
                }
                if (g.move(p, m.first, m.second, false)) {
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            ChessPiece *piece = g.getPiece(i, j);
                            if (piece != nullptr && piece->getColor() != color) {
                                std::vector<std::pair<int, int>> allowed = piece->getValidMoves(g);
                                if (Pawn *_ = dynamic_cast<Pawn *>(piece)) {
                                    if (piece->getColor() == white) {
                                        std::pair<int, int> oneLeftAbove;
                                        oneLeftAbove.first = piece->curRow - 1;
                                        oneLeftAbove.second = piece->curCol - 1;
                                        if (oneLeftAbove.first == m.first && oneLeftAbove.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                        std::pair<int, int> oneRightAbove;
                                        oneRightAbove.first = piece->curRow - 1;
                                        oneRightAbove.second = piece->curCol + 1;
                                        if (oneRightAbove.first == m.first && oneRightAbove.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                    } else {
                                        std::pair<int, int> oneLeftAbove;
                                        oneLeftAbove.first = piece->curRow + 1;
                                        oneLeftAbove.second = piece->curCol - 1;
                                        if (oneLeftAbove.first == m.first && oneLeftAbove.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                        std::pair<int, int> oneRightAbove;
                                        oneRightAbove.first = piece->curRow + 1;
                                        oneRightAbove.second = piece->curCol + 1;
                                        if (oneRightAbove.first == m.first && oneRightAbove.second == m.second) {
                                            setTileThreat(m.first, m.second, true);
                                        }
                                    }
                                    continue;
                                }
                                for (std::pair<int, int> a: allowed) {
                                    if (g.validateMove(piece, a.first, a.second)) {
                                        if (a.first == m.first && a.second == m.second) {
                                            setTileThreat(a.first, a.second, true);
                                            continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    setTileFocus(m.first, m.second, true);

                    g.setBoard(prev_bord);
                    p->curCol = prevCol;
                    p->curRow = prevRow;
                    p->setMoved(prevMoved);

                    continue;
                }
            }
        }
        alreadyClicked = true;
        return;
    } else {
        if (r == clickedPiece->curRow &&
            c == clickedPiece->curCol) {
            alreadyClicked = false;
            setTileSelect(prevRow, prevCol, false);
            for (std::pair<int, int> g: prevValid) {
                setTileFocus(g.first, g.second, false);
                alreadyClicked = false;
            }
            return;
        }
        bool success = this->g.move(clickedPiece, r, c);
        if (not success) {
            message("Invalid move");

            setTileSelect(prevRow, prevCol, false);

            for (std::pair<int, int> g: prevValid) {
                setTileFocus(g.first, g.second, false);
            }

            alreadyClicked = false;
            return;
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ChessPiece *p = g.getPiece(i, j);
                if (p != nullptr && p->getColor() != colorToMove) {
                    if (p->isEnPassantable()) {
                        p->setEnPassantable(false);
                    }
                }
            }
        }

        colorToMove == white ? colorToMove = black : colorToMove = white;

        clearBoard();

        setTileSelect(prevRow, prevCol, false);
        for (std::pair<int, int> v: prevValid) {
            setTileFocus(v.first, v.second, false);
            alreadyClicked = false;
        }

        update();


        if (g.check(white)) {
            if (g.checkmate(white)) {
                message("Checkmate, black wins!");
            } else {
                message("White is in check!");
            }
        } else if (g.stalemate(white)) {
            message("Stalemate!");
        }

        if (g.check(black)) {
            if (g.checkmate(black)) {
                message("Checkmate, white wins!");
            } else {
                message("Black is in check!");
            }
        } else if (g.stalemate(black)) {
            message("Stalemate!");
        }

    }
}

void ChessGUI::newGame() {}


void ChessGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb")
            << QString("Hb") << QString("Rb");
        for (int i = 0; i < 8; i++) {
            out << QString("Pb");
        }
        for (int r = 3; r < 7; r++) {
            for (int c = 0; c < 8; c++) {
                out << QString(".");
            }
        }
        for (int i = 0; i < 8; i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw")
            << QString("Hw") << QString("Rw");
    }
}

void ChessGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status() != QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString &Q) {
            message(Q);
        }
    }
    update();
}


void ChessGUI::undo() {
    message("You chose to undo your move");
}

void ChessGUI::redo() {}


void ChessGUI::visualizationChange() {
    QString visstring =
            QString(displayMoves() ? "T" : "F") + (displayKills() ? "T" : "F") + (displayThreats() ? "T" : "F");
    message(QString("Visualization changed : ") + visstring);
}



void ChessGUI::update() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            setPieceThreat(r, c, false);
            setTileThreat(r, c, false);
        }
    }
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            ChessPiece *chessPiece = g.getPiece(r, c);
            if (chessPiece != nullptr) {
                setItem(r, c, chessPiece);
            }

            if (displayKills()) {
                ChessPiece *p = g.getPiece(r, c);
                if (p != nullptr && p->getColor() == white) {
                    std::vector<std::pair<int, int>> validMoves = p->getValidMoves(g);
                    for (std::pair<int, int> m: validMoves) {
                        if (g.validateMove(p, m.first, m.second)) {
                            ChessPiece *piece = g.getPiece(m.first, m.second);
                            if (piece != nullptr && piece->getColor() == black) {
                                setPieceThreat(m.first, m.second, true);
                            }
                        }
                    }
                }
            }
            if (displayThreats()) {
                ChessPiece *p = g.getPiece(r, c);
                if (p != nullptr && p->getColor() == black) {
                    std::vector<std::pair<int, int>> validMoves = p->getValidMoves(g);
                    for (std::pair<int, int> m: validMoves) {
                        if (g.validateMove(p, m.first, m.second)) {
                            ChessPiece *piece = g.getPiece(m.first, m.second);
                            if (piece != nullptr && piece->getColor() == white) {
                                setPieceThreat(m.first, m.second, true);
                            }
                        }
                    }
                }
            }
        }
    }
}


