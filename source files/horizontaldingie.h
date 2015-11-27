#ifndef HORIZONTALDINGIE_H
#define HORIZONTALDINGIE_H

#include <QWidget>

namespace Ui {
class Horizontaldingie;
}

class Horizontaldingie : public QWidget
{
	Q_OBJECT

public:
	explicit Horizontaldingie(QWidget *parent = 0);
	~Horizontaldingie();

private:
	Ui::Horizontaldingie *ui;
};

#endif // HORIZONTALDINGIE_H
