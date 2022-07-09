#ifndef CHESS_CHESSGUI_H
#define CHESS_CHESSGUI_H

#include "guicode/ChessWindow.h"
#include "ChessPiece.h"
#include <QMessageBox>
#include <QAction>

class ChessGUI: public ChessWindow {
public:
    ChessGUI();
    void update() override;
private:
    Game g;

    void clicked(int x, int y) override;
    void newGame() override;
    void open() override;
    void save() override;
    void undo() override;
    void redo() override;
    void visualizationChange() override;
};
#endif