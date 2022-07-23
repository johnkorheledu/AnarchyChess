#ifndef WHITEQUEENDIALOG_H
#define WHITEQUEENDIALOG_H

#include <QDialog>

namespace Ui {
class WhiteQueenDialog;
}

class WhiteQueenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WhiteQueenDialog(QWidget *parent = nullptr);
    ~WhiteQueenDialog();
    std::string choice_;

    const std::string &choice() const;
    void setChoice(const std::string &newChoice);

private slots:
    void on_queen_clicked();

    void on_rook_clicked();

    void on_bishop_clicked();

    void on_knight_clicked();

private:
    Ui::WhiteQueenDialog *ui;
};

#endif // WHITEQUEENDIALOG_H
