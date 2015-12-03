#ifndef ACHIEVEMENTLIST_H
#define ACHIEVEMENTLIST_H

#include <QListWidget>

namespace Ui {
class AchievementList;
}

class AchievementList : public QListWidget
{
	Q_OBJECT

public:
	explicit AchievementList(QWidget *parent = 0);
	~AchievementList();
	void mousePressEvent(QMouseEvent *e);

public: signals:
	void clicked();

private:
	Ui::AchievementList *ui;
};

#endif // ACHIEVEMENTLIST_H
