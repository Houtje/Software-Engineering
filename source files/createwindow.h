#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QMainWindow>

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateWindow(QWidget *parent = 0);
    ~CreateWindow();

private slots:
    void on_createknop_clicked();
    void on_cancelknop_clicked();

private:
    Ui::CreateWindow *ui;
};

#endif // CREATEWINDOW_H
