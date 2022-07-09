#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <vector>
#include "ChessPiece.h"

class ChessPiece;

class Game {
public:
    Game();
    ~Game();

    ChessPiece* getPiece(int r, int c);
    void setPiece(int r, int c, ChessPiece* p);

    bool move(ChessPiece* p, int r, int c);
    bool move_wo_delete(ChessPiece *p, int r, int c);

    bool validateMove(ChessPiece* p, int r, int c);

    bool check(bw color);
    bool checkmate(bw color);

    void setStartingBoard();

    void setBoard(std::vector<std::vector<ChessPiece*>> p);
    std::vector<std::vector<ChessPiece*>> getBoard();

    bool stalemate(bw color);

private:
    std::vector<std::vector<ChessPiece*>> board = {{}};
};


#endif
