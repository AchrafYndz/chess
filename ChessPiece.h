#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H
#include <guicode/chessboard.h>

class Game;

enum bw{black, white};


class ChessPiece {
public:
    ChessPiece(bw color) : color(color) {}

    virtual Piece piece() const = 0;

    bw getColor() const { return color; }

    virtual std::vector<std::pair<int, int>> getValidMoves(Game &g) = 0;

    int curRow = 0;
    int curCol = 0;

    virtual void setMoved(bool b) {};
    virtual bool getMoved() {return true;};

    virtual void setEnPassantable(bool b) {};
    virtual bool isEnPassantable() {return false;};

private:
    bw color;
};

class Pawn : public ChessPiece {
public:
    Pawn(bw color) : ChessPiece(color) {}

    virtual Piece piece() const override {
        return Piece(Piece::Pawn, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;

    void setMoved(bool b) override;
    bool getMoved();

    void setEnPassantable(bool b) override;
    bool isEnPassantable() override;

private:
    bool moved = false;
    bool enPassantable = false;
};

class Rook : public ChessPiece {
public:
    Rook(bw color) : ChessPiece(color) {}

    Piece piece() const override {
        return Piece(Piece::Rook, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;

    void setMoved(bool m) override;

    bool getMoved() override;;

private:
    bool moved = false;
};

class Knight : public ChessPiece {
public:
    Knight(bw color) : ChessPiece(color) {}

    Piece piece() const override {
        return Piece(Piece::Knight, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;
};

class Bishop : public ChessPiece {
public:
    Bishop(bw color) : ChessPiece(color) {}

    Piece piece() const override {
        return Piece(Piece::Bishop, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;
};

class King : public ChessPiece {
public:
    King(bw color) : ChessPiece(color) {}

    Piece piece() const override {
        return Piece(Piece::King, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;

    void setMoved(bool m) override;
    bool getMoved() override;;

private:
    bool moved;
};

class Queen : public ChessPiece {
public:
    Queen(bw color) : ChessPiece(color) {}

    Piece piece() const override {
        return Piece(Piece::Queen, getColor() == white ? Piece::White : Piece::Black);
    }

    std::vector<std::pair<int, int>> getValidMoves(Game &g) override;;
};

#endif
