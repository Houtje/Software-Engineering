#ifndef ASSIGNMENTLISTITEM_H
#define ASSIGNMENTLISTITEM_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include "qrocheckbox.h"

class AssignmentListItem : public QWidget
{
	Q_OBJECT
public:
	AssignmentListItem(int assignmentNumber, int score, QWidget *parent = 0);
	QSize minimumSizeHint();

signals:
	void mouseDoubleClickEvent();

public slots:
};

#endif // ASSIGNMENTLISTITEM_H
