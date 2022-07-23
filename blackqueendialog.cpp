#include "blackqueendialog.h""
#include "ui_blackqueendialog.h""

BlackQueenDialog::BlackQueenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackQueenDialog)
{
    ui->setupUi(this);
    choice_ = "queen";
}

BlackQueenDialog::~BlackQueenDialog()
{
    delete ui;
}

const std::string &BlackQueenDialog::choice() const
{
    return choice_;
}

void BlackQueenDialog::setChoice(const std::string &newChoice)
{
    choice_ = newChoice;
}

void BlackQueenDialog::on_queen_clicked()
{
    choice_ = "queen";
}


void BlackQueenDialog::on_rook_clicked()
{
    choice_ = "rook";
}


void BlackQueenDialog::on_bishop_clicked()
{
    choice_ = "bishop";
}


void BlackQueenDialog::on_knight_clicked()
{
    choice_ = "knight";
}

