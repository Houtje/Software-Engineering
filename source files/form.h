#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
	Q_OBJECT

public:
	explicit Form(QPixmap image, QString name, QString tooltip, QWidget *parent = 0);
	~Form();

private:
	Ui::Form *ui;
};

#endif // FORM_H
