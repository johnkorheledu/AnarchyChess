#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "tile.h"
#include "piece.h"
#include "move_option.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawBoard();
    void AddPieces();
    Tile * GetTileByNumber(int n);
    Tile * GetTileByCoords(int x, int y);

    Piece* GetPiecesOnTile(Tile *t);
    std::vector<Tile *> GetValidMoves(Piece *p);
    Tile * GetKingTile(std::string p);

    bool in_check() const;
    void setIn_check(bool newIn_check);
    void Check();
    bool MoveIntoCheck(Tile *toMove);


private:
    QTimer * timer_;
    Ui::MainWindow *ui;
    QGraphicsScene *boardScene;
    QGraphicsScene *whiteScene;
    QGraphicsScene *blackScene;
    std::vector<Tile *> tiles_;
    std::vector<Piece *> pieces_;
    std::vector<MoveOption *> move_options_;
    Piece * selected_piece_;
    std::string turn_ = "white";
    int white_captured_pieces_;
    int black_captured_pieces_;
    bool in_check_;
    int white_timer_;
    int stop_clock_white_ = 30;
    int black_timer_;
    int stop_clock_black_ = 30;
    bool stopped_clock_ = false;
    bool white_double_move_ = false;
    bool black_double_move_ = false;
    bool double_move_ = false;

private slots:
    void PieceSelected(Piece *p);
    void MoveOptionSelected(MoveOption *mo);
    void updateTimer();
    void on_stopClock_clicked();
    void on_doubleMove_clicked();
};
#endif // MAINWINDOW_H
