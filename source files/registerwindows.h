#ifndef REGISTERWINDOWS_H
#define REGISTERWINDOWS_H

#include <QDialog>
#include "sqlhandler.h"

namespace Ui {
class RegisterWindows;
}

class RegisterWindows : public QDialog
{
	Q_OBJECT

public:
	explicit RegisterWindows(QWidget *parent = 0);
	~RegisterWindows();

private slots:
	void on_pushButton_clicked();

private:
	Ui::RegisterWindows *ui;
    SqlHandler * sqlplayer;
    QString message;
};

#endif // REGISTERWINDOWS_H
