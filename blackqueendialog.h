#ifndef BLACKQUEENDIALOG_H
#define BLACKQUEENDIALOG_H

#include <QDialog>

namespace Ui {
class BlackQueenDialog;
}

class BlackQueenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlackQueenDialog(QWidget *parent = nullptr);
    ~BlackQueenDialog();
    std::string choice_;

    const std::string &choice() const;
    void setChoice(const std::string &newChoice);

private slots:
    void on_queen_clicked();

    void on_rook_clicked();

    void on_bishop_clicked();

    void on_knight_clicked();

private:
    Ui::BlackQueenDialog *ui;
};

#endif // BLACKQUEENDIALOG_H
