#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "move_option.h"
#include "whitequeendialog.h"
#include "blackqueendialog.h"
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // setup board scene and view
    QGraphicsView * boardView = ui->boardView;
    boardScene = new QGraphicsScene;
    boardView->setScene(boardScene);
    boardView->setSceneRect(0,0,boardView->frameSize().width(),boardView->frameSize().height());
    boardView->setFrameStyle(0);

    QGraphicsView * whiteView = ui->whiteView;
    whiteScene = new QGraphicsScene;
    whiteView->setScene(whiteScene);
    whiteView->setSceneRect(0,0,whiteView->frameSize().width(),whiteView->frameSize().height());
    whiteView->setFrameStyle(0);

    QGraphicsView * blackView = ui->blackView;
    blackScene = new QGraphicsScene;
    blackView->setScene(blackScene);
    blackView->setSceneRect(0,0,blackView->frameSize().width(),blackView->frameSize().height());
    blackView->setFrameStyle(0);

    DrawBoard();
    AddPieces();
    white_captured_pieces_ = 0;
    black_captured_pieces_ = 0;


    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::updateTimer);
    timer_->start(1000);

    black_timer_ = 600;
    white_timer_ = 600;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawBoard(){
    int boardNo = 0;
    int colorPick = 0;
    QColor tileColor;
    for(long unsigned int i = 0; i < 8; i++){
        colorPick++;
        for(long unsigned int j = 0; j < 8; j++){
            boardNo++;
            colorPick++;
            colorPick % 2 == 0 ? tileColor = QColor::fromRgba(qRgba(255,206,158,255)) : tileColor = QColor::fromRgba(qRgba(209,139,71,255));
            Tile *t = new Tile(tileColor, boardNo, 95*j, 95*i, 95, 95);
            boardScene->addItem(t);
            tiles_.push_back(t);
        }
    }
}

void MainWindow::AddPieces(){
    QString pType;
    QString pColor;
    // pawns for black
    for(long unsigned int i = 9; i < 17; i++){
        pType = "pawn";
        pColor = "black";
        Piece *p = Piece::PieceFactory(pType, pColor);
        p->setPos(GetTileByNumber(i)->x(), GetTileByNumber(i)->y());
        boardScene->addItem(p);
        connect(p, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
        pieces_.push_back(p);
    }

    // pawns for white
    for(long unsigned int i = 49; i < 57; i++){
        pType = "pawn";
        pColor = "white";
        Piece *p = Piece::PieceFactory(pType, pColor);
        p->setPos(GetTileByNumber(i)->x(), GetTileByNumber(i)->y());
        boardScene->addItem(p);
        connect(p, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
        pieces_.push_back(p);
    }

    //rooks for black
    pType = "rook";
    pColor = "black";
    Piece *rb1 = Piece::PieceFactory(pType, pColor);
    rb1->setPos(GetTileByNumber(1)->x(), GetTileByNumber(1)->y());
    boardScene->addItem(rb1);
    connect(rb1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(rb1);

    Piece *rb2 = Piece::PieceFactory(pType, pColor);
    rb2->setPos(GetTileByNumber(8)->x(), GetTileByNumber(8)->y());
    boardScene->addItem(rb2);
    connect(rb2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(rb2);

    //rooks for white
    pColor = "white";
    Piece *rw1 = Piece::PieceFactory(pType, pColor);
    rw1->setPos(GetTileByNumber(57)->x(), GetTileByNumber(57)->y());
    boardScene->addItem(rw1);
    connect(rw1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(rw1);

    Piece *rw2 = Piece::PieceFactory(pType, pColor);
    rw2->setPos(GetTileByNumber(64)->x(), GetTileByNumber(64)->y());
    boardScene->addItem(rw2);
    connect(rw2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(rw2);

    //knights for black
    pColor = "black";
    pType = "knight";
    Piece *hb1 = Piece::PieceFactory(pType, pColor);
    hb1->setPos(GetTileByNumber(7)->x(), GetTileByNumber(7)->y());
    boardScene->addItem(hb1);
    connect(hb1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(hb1);

    Piece *hb2 = Piece::PieceFactory(pType, pColor);
    hb2->setPos(GetTileByNumber(2)->x(), GetTileByNumber(2)->y());
    boardScene->addItem(hb2);
    connect(hb2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(hb2);

    //knights for white
    pColor = "white";
    Piece *hw1 = Piece::PieceFactory(pType, pColor);
    hw1->setPos(GetTileByNumber(58)->x(), GetTileByNumber(58)->y());
    boardScene->addItem(hw1);
    connect(hw1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(hw1);

    Piece *hw2 = Piece::PieceFactory(pType, pColor);
    hw2->setPos(GetTileByNumber(63)->x(), GetTileByNumber(63)->y());
    boardScene->addItem(hw2);
    connect(hw2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(hw2);

    //bishops for black
    pColor = "black";
    pType = "bishop";
    Piece *bb1 = Piece::PieceFactory(pType, pColor);
    bb1->setPos(GetTileByNumber(3)->x(), GetTileByNumber(3)->y());
    boardScene->addItem(bb1);
    connect(bb1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(bb1);

    Piece *bb2 = Piece::PieceFactory(pType, pColor);
    bb2->setPos(GetTileByNumber(6)->x(), GetTileByNumber(6)->y());
    boardScene->addItem(bb2);
    connect(bb2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(bb2);

    //bishops for white
    pColor = "white";
    Piece *bw1 = Piece::PieceFactory(pType, pColor);
    bw1->setPos(GetTileByNumber(59)->x(), GetTileByNumber(59)->y());
    boardScene->addItem(bw1);
    connect(bw1, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(bw1);

    Piece *bw2 = Piece::PieceFactory(pType, pColor);
    bw2->setPos(GetTileByNumber(62)->x(), GetTileByNumber(62)->y());
    boardScene->addItem(bw2);
    connect(bw2, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(bw2);

    //queen for black
    pColor = "black";
    pType = "queen";
    Piece *qb = Piece::PieceFactory(pType, pColor);
    qb->setPos(GetTileByNumber(4)->x(), GetTileByNumber(4)->y());
    boardScene->addItem(qb);
    connect(qb, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(qb);

    //queen for white
    pColor = "white";
    Piece *qw = Piece::PieceFactory(pType, pColor);
    qw->setPos(GetTileByNumber(60)->x(), GetTileByNumber(60)->y());
    boardScene->addItem(qw);
    connect(qw, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(qw);


    //king for black
    pColor = "black";
    pType = "king";
    Piece *kb = Piece::PieceFactory(pType, pColor);
    kb->setPos(GetTileByNumber(5)->x(), GetTileByNumber(5)->y());
    boardScene->addItem(kb);
    connect(kb, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(kb);

    //king for white
    pColor = "white";
    Piece *kw = Piece::PieceFactory(pType, pColor);
    kw->setPos(GetTileByNumber(61)->x(), GetTileByNumber(61)->y());
    boardScene->addItem(kw);
    connect(kw, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
    pieces_.push_back(kw);
}

Tile* MainWindow::GetTileByNumber(int n){
    for(long unsigned int i = 0; i < tiles_.size(); i++){
        if(tiles_.at(i)->number() == n){
            return tiles_.at(i);
        }
    }
    return nullptr;
}

Tile* MainWindow::GetTileByCoords(int x, int y){
    for (Tile * curr : tiles_) {
        if (curr->x() == x && curr->y() == y) {
            return curr;
        }
    }
    return nullptr;
}


Piece* MainWindow::GetPiecesOnTile(Tile *t) {
    for(Piece * p : pieces_) {
        if (p->pos().x() == t->x() && p->pos().y() == t->y()) {
            return p;
        }
    }
    return nullptr;
}

Tile * MainWindow::GetKingTile(std::string p){
    for(Piece * pi : pieces_) {
        if(pi->getType() == QString::fromStdString("king") && pi->getColor() == QString::fromStdString(p)){
            return GetTileByCoords(pi->x(), pi->y());
        }
    }
    return nullptr;
}

bool MainWindow::in_check() const
{
    return in_check_;
}

void MainWindow::setIn_check(bool newIn_check)
{
    in_check_ = newIn_check;
}

//Handle click of piece
void MainWindow::PieceSelected(Piece *p) {
    //qDebug() << QString::fromStdString("Selected Piece: ") <<  p->getType() << QString::fromStdString(" - ") << p->getColor();
    //Handle Logic here.
    if (p->getColor() == QString::fromStdString(turn_)) {

        //Clear move options drawn on board
        for (MoveOption *curr : move_options_) {
            boardScene->removeItem(curr);
        }
        //Clear move option storage
        move_options_.clear();

        selected_piece_ = p;

        //get valid moves and draw on board.
        for (Tile * curr : GetValidMoves(p)) {
            //            qDebug() << p->getType() << GetValidMoves(p).size();
            bool occupy = false;
            if(GetPiecesOnTile(GetTileByCoords(curr->x(), curr->y()))){
                occupy = true;
            }
            MoveOption *mo = new MoveOption(curr->x(), curr->y(), 95, 95, occupy);
            move_options_.push_back(mo);
            boardScene->addItem(mo);
            //Add connect here.
            connect(mo, &MoveOption::MoveOptionSelected, this, &MainWindow::MoveOptionSelected);
        }
    }
}

void MainWindow::MoveOptionSelected(MoveOption *mo) {
    //Clear move options drawn on board
    for (MoveOption *curr : move_options_) {
        boardScene->removeItem(curr);
    }
    //Clear move option storage
    move_options_.clear();

    //did we capture a piece?
    Piece * toRemove = GetPiecesOnTile(GetTileByCoords(mo->x(), mo->y()));
    if (toRemove != nullptr) {
        boardScene->removeItem(toRemove);
        if(turn_ == "white"){
            if(white_captured_pieces_ >= 9){
                whiteScene->addItem(toRemove);
                toRemove->setPos((white_captured_pieces_ - 9) * 30,38);
                toRemove->setScale(0.4);
                white_captured_pieces_++;
            }else{
                whiteScene->addItem(toRemove);
                toRemove->setPos(white_captured_pieces_ * 30,0);
                toRemove->setScale(0.4);
                white_captured_pieces_++;
            }
        }
        else{
            if(black_captured_pieces_ >= 9){
                blackScene->addItem(toRemove);
                toRemove->setPos((black_captured_pieces_ - 9) * 30,38);
                toRemove->setScale(0.4);
                black_captured_pieces_++;
            }else{
                blackScene->addItem(toRemove);
                toRemove->setPos(black_captured_pieces_ * 30,0);
                toRemove->setScale(0.4);
                black_captured_pieces_++;
            }
        }
        pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), toRemove), pieces_.end());
    }


    //Move Piece
    selected_piece_->setPos(mo->x(), mo->y());

    //queening?
    std::string choice;
    if (turn_ == "white" && selected_piece_->y() == 0 && selected_piece_->getType() == "pawn"){
        QString pType = "queen";
        QString pColor = "white";
        WhiteQueenDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted){
            choice = dialog.choice();
            dialog.hide();
        }
        if(choice == "queen"){
            Piece *np = Piece::PieceFactory(pType,pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "rook"){
            pType = "rook";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "bishop"){
            pType = "bishop";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "knight"){
            pType = "knight";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
    }
    else if(turn_ == "black" && selected_piece_->y() == 665 && selected_piece_->getType() == "pawn"){
        QString pColor = "black";
        QString pType = "queen";
        BlackQueenDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted){
            choice = dialog.choice();
            dialog.hide();
        }
        if(choice == "queen"){
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "rook"){
            pType = "rook";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "bishop"){
            pType = "bishop";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
        if(choice == "knight"){
            pType = "knight";
            Piece *np = Piece::PieceFactory(pType, pColor);
            np->setPos(mo->x(), mo->y());
            boardScene->addItem(np);
            connect(np, &Piece::PieceSelected, this, &MainWindow::PieceSelected);
            pieces_.push_back(np);
            boardScene->removeItem(selected_piece_);
            pieces_.erase(std::remove(pieces_.begin(), pieces_.end(), selected_piece_), pieces_.end());
        }
    }


    //Handle Pawn bs
    if (selected_piece_->getType() == "pawn") {
        ((Pawn *)selected_piece_)->setMoved();
    }

    bool blackKing = false, whiteKing = false;
    for (Piece *curr : pieces_) {
        if (curr->getType() == QString::fromStdString("king")) {
            if (curr->getColor() == QString::fromStdString("black")) {
                blackKing = true;
            } else {
                whiteKing = true;
            }
        }
    }
    if (!blackKing || !whiteKing) {
        std::string winner;
        if(blackKing){
            winner = "black";
        }
        else{
            winner = "white";
        }
        QMessageBox::StandardButton reply;
        QString won = QString("%1 won. New Game?").arg(QString::fromStdString(winner));
        reply = QMessageBox::question(this, "Game Over", won,
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        } else {
            qApp->quit();
        }
    }


    //change turn
    if (double_move_) {
        if (turn_ == "white") {
            white_double_move_ = true;
        } else if (turn_ == "black") {
            black_double_move_ = true;
        }
        double_move_ = false;
    } else {
        if (turn_ == "white") {
            turn_ = "black";
            ui->doubleMove->setDisabled(black_double_move_);
            if (stop_clock_black_ < 30) {
                ui->stopClock->setDisabled(true);
            } else {
                ui->stopClock->setDisabled(false);
            }
        } else if (turn_ == "black") {
            turn_ ="white";
            ui->doubleMove->setDisabled(white_double_move_);
            if (stop_clock_white_ < 30) {
                ui->stopClock->setDisabled(true);
            } else {
                ui->stopClock->setDisabled(false);
            }
        }
    }
    stopped_clock_ = false;

    ui->currentTurn->setText(QString::fromStdString(turn_));
}


//Handle actual logic of moves. this is going to be a LOT

//TODO: handle check stuff maybe just let player screw themselves?
std::vector<Tile *> MainWindow::GetValidMoves(Piece *p) {
    std::vector<Tile *> storage;

    QString type = p->getType();
    QString color = p->getColor();

    int direction = (color == "black") ? 1 : -1;

    if (type == "pawn") {
        //pawns
        //Handles All moves (1 pos away)
        if (!GetPiecesOnTile(GetTileByCoords(p->x(), p->y() + (direction * 95)))) {
            storage.push_back(GetTileByCoords(p->x(), p->y() + (direction * 95)));
        }
        //Handles First Move (2 Pos away)
        if (!((Pawn*)p)->getMoved() && !GetPiecesOnTile(GetTileByCoords(p->x(), p->y() + (direction * 95 * 2)))) {
            storage.push_back(GetTileByCoords(p->x(), p->y() + (direction * 95 * 2)));
        }
        //Handles Diagonal (capturing pieces)
        //3 Part if statemnt to handle cases (since cpp uses short-circuit evaluation)
        //1:checks if edge of board. 2: checks for piece there, 3: checks if piece is opposing team
        //Right diagonal
        if (p->x() != 665 && GetPiecesOnTile(GetTileByCoords(p->x() + (95), p->y() + (direction * 95))) &&GetPiecesOnTile(GetTileByCoords(p->x() + (95), p->y() + (direction * 95)))->getColor() != QString::fromStdString(turn_)) {
            storage.push_back(GetTileByCoords(p->x() + (95), p->y() + (direction * 95)));
        }
        //Left diagonal
        if (p->x() != 0 && GetPiecesOnTile(GetTileByCoords(p->x() - (95), p->y() + (direction * 95))) &&GetPiecesOnTile(GetTileByCoords(p->x() - (95), p->y() + (direction * 95)))->getColor() != QString::fromStdString(turn_)) {
            storage.push_back(GetTileByCoords(p->x() - (95), p->y() + (direction * 95)));
        }
    }
    //It's rook time bois.
    if (type == "rook" || type == "queen") {
        //4 directions for movement = 4 loops
        int x1 = p->x()-95,  x2 = p->x()+95,  y1 = p->y()-95,  y2= p->y()+95;
        //left
        while (x1 >= 0) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x1, p->y())) && GetPiecesOnTile(GetTileByCoords(x1, p->y()))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x1, p->y()));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x1, p->y()))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x1, p->y()));
            x1 -= 95;
        }
        //right
        while (x2 <= 665) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x2, p->y())) && GetPiecesOnTile(GetTileByCoords(x2, p->y()))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x2, p->y()));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x2, p->y()))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x2, p->y()));
            x2 += 95;
        }
        //up
        while (y1 >= 0) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(p->x(), y1)) && GetPiecesOnTile(GetTileByCoords(p->x(), y1))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(p->x(), y1));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(p->x(), y1))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(p->x(), y1));
            y1 -= 95;
        }
        //down
        while (y2 <= 665) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(p->x(), y2)) && GetPiecesOnTile(GetTileByCoords(p->x(), y2))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(p->x(), y2));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(p->x(), y2))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(p->x(), y2));
            y2 += 95;
        }
    }
    //bishop poggers
    if (type == "bishop" || type == "queen") {
        int x1 = p->x()-95, y1 = p->y()-95, x2 = p->x()+95, y2= p->y()-95, x3 = p->x()-95, y3= p->y()+95, x4 = p->x()+95, y4 = p->y()+95;
        //up-left
        while (x1 >= 0 && y1 >= 0) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x1, y1)) && GetPiecesOnTile(GetTileByCoords(x1, y1))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x1, y1));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x1, y1))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x1, y1));
            x1 -= 95;
            y1 -= 95;
        }
        //up-right
        while (x2 <= 665 && y2 >= 0) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x2, y2)) && GetPiecesOnTile(GetTileByCoords(x2, y2))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x2, y2));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x2, y2))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x2, y2));
            x2 += 95;
            y2 -= 95;
        }
        //down-left
        while (x3 >= 0 && y3 <= 665) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x3, y3)) && GetPiecesOnTile(GetTileByCoords(x3, y3))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x3, y3));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x3, y3))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x3, y3));
            x3 -= 95;
            y3 += 95;
        }
        //down-right
        while (x4 <= 665 && y4 <= 665) {
            //Tile with opposing piece, allow capture
            if (GetPiecesOnTile(GetTileByCoords(x4, y4)) && GetPiecesOnTile(GetTileByCoords(x4, y4))->getColor() != QString::fromStdString(turn_)) {
                storage.push_back(GetTileByCoords(x4, y4));
                break;
                //Tile with same piece, don't allow capture
            } else if (GetPiecesOnTile(GetTileByCoords(x4, y4))) {
                break;
            }
            //Blank tile
            storage.push_back(GetTileByCoords(x4, y4));
            x4 += 95;
            y4 += 95;
        }
    }
    //we are the knights who say "ni"
    if (type == "knight") {
        std::pair<int,int> toCheck[] = {std::make_pair(-190,-95),std::make_pair(-95,-190),std::make_pair(95,-190),std::make_pair(190,-95),std::make_pair(-190,95),std::make_pair(-95,190),std::make_pair(95,190),std::make_pair(190,95)};
        for (std::pair<int,int> curr : toCheck) {
            if (p->x() + curr.first >= 0 && p->x() + curr.first <= 665 && p->y() + curr.second >= 0 && p->y() + curr.second <= 665 ) {
                //Tile with opposing piece, allow capture, or blank piece
                if ((GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second)) && GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second))->getColor() != QString::fromStdString(turn_)) || !(GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second)))) {
                    storage.push_back(GetTileByCoords(p->x() + curr.first, p->y() + curr.second));
                }
            }
        }
    }
    //YASSS KING
    if (type == "king") {
        std::pair<int,int> toCheck[] = {std::make_pair(-95,-95),std::make_pair(0,-95),std::make_pair(95,-95),std::make_pair(-95,0),std::make_pair(95,0),std::make_pair(-95,95),std::make_pair(0,95),std::make_pair(95,95)};
        for (std::pair<int,int> curr : toCheck) {
            if (p->x() + curr.first >= 0 && p->x() + curr.first <= 665 && p->y() + curr.second >= 0 && p->y() + curr.second <= 665 ) {
                //Tile with opposing piece, allow capture, or blank piece
                if ((GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second)) && GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second))->getColor() != QString::fromStdString(turn_)) || !(GetPiecesOnTile(GetTileByCoords(p->x() + curr.first, p->y() + curr.second)))) {
                    storage.push_back(GetTileByCoords(p->x() + curr.first, p->y() + curr.second));
                }
            }
        }
    }

    return storage;
}

std::string secToString(int time_remaining) {
    int mins = time_remaining/60;
    int secs = time_remaining%60;

    std::string secsTemp = std::to_string(secs);

    if (secsTemp.length() < 2) {
        secsTemp = "0" + secsTemp;
    }

    return (std::to_string(mins) + ":" + secsTemp);
}

void MainWindow::updateTimer()
{
    if (!stopped_clock_) {
        if (turn_ == "white") {
            white_timer_--;
        } else if (turn_ == "black") {
            black_timer_--;
        }
        ui->stopTheClockLabel->setText(QString::fromStdString(""));
    } else {
        if (turn_ == "white") {
            stop_clock_white_--;

            ui->stopTheClockLabel->setText(QString::fromStdString("Clock Paused for: " + std::to_string(stop_clock_white_)));
            if (stop_clock_white_ == 0) {
                stopped_clock_ = false;
            }
        } else if (turn_ == "black") {
            stop_clock_black_--;
            ui->stopTheClockLabel->setText(QString::fromStdString("Clock Paused for: " + std::to_string(stop_clock_black_)));
            if (stop_clock_black_ == 0) {
                stopped_clock_ = false;
            }
        }

    }
    ui->timeRemainingBlack->setText(QString::fromStdString("Time Remaining " + secToString(black_timer_)));
    ui->timeRemainingWhite->setText(QString::fromStdString("Time Remaining " + secToString(white_timer_)));
    if (black_timer_ == 0 || white_timer_ ==0 ) {
        qDebug() << "Game over";
    }

}

void MainWindow::on_stopClock_clicked()
{
    stopped_clock_ = true;
    ui->stopClock->setDisabled(true);
}


void MainWindow::on_doubleMove_clicked()
{
    double_move_ = true;
    ui->doubleMove->setDisabled(true);
}

