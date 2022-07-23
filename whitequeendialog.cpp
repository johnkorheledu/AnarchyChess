#include "whitequeendialog.h"
#include "ui_whitequeendialog.h"

WhiteQueenDialog::WhiteQueenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WhiteQueenDialog)
{
    ui->setupUi(this);
    choice_ = "queen";
}

WhiteQueenDialog::~WhiteQueenDialog()
{
    delete ui;
}

const std::string &WhiteQueenDialog::choice() const
{
    return choice_;
}

void WhiteQueenDialog::setChoice(const std::string &newChoice)
{
    choice_ = newChoice;
}

void WhiteQueenDialog::on_queen_clicked()
{
    choice_ = "queen";
}


void WhiteQueenDialog::on_rook_clicked()
{
    choice_ = "rook";
}


void WhiteQueenDialog::on_bishop_clicked()
{
    choice_ = "bishop";
}


void WhiteQueenDialog::on_knight_clicked()
{
    choice_ = "knight";
}

