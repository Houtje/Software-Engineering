#ifndef QROCHECKBOX_H
#define QROCHECKBOX_H

#include <QCheckBox>
#include <QPalette>

class QROCheckBox : public QCheckBox
{
public:
	QROCheckBox(QString string, bool tested = false, QWidget *parent = 0);
protected:
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // QROCHECKBOX_H
