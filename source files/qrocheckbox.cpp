#include "qrocheckbox.h"

//ReadOnlyCheckBox for in the list of students assignments the score indicators.
QROCheckBox::QROCheckBox(QString string, bool tested, QWidget *parent) : QCheckBox(string, parent) {
	setText(string);
	setChecked(tested);
	QPalette my_palette = palette();
	setStyleSheet( "QCheckBox::indicator:unchecked { \
					image: url(:/new/prefix1/plaatjes/checkbox_unchecked.png); \
				} \
				\
				QCheckBox::indicator:unchecked:hover { \
					image: url(:/new/prefix1/plaatjes/checkbox_unchecked_hover.png); \
				} \
				\
				QCheckBox::indicator:unchecked:pressed { \
					image: url(:/new/prefix1/plaatjes/checkbox_unchecked_pressed.png); \
				} \
				\
				QCheckBox::indicator:checked { \
					image: url(:/new/prefix1/plaatjes/checkbox_checked.png); \
				} \
				\
				QCheckBox::indicator:checked:hover { \
					image: url(:/new/prefix1/plaatjes/checkbox_checked_hover.png); \
				} \
				\
				QCheckBox::indicator:checked:pressed { \
					image: url(:/new/prefix1/plaatjes/checkbox_checked_pressed.png); \
				} \
				\
				QCheckBox::indicator:indeterminate:hover { \
					image: url(:/new/prefix/achievement dingen/checkbox_indeterminate_hover.png); \
				} \
				\
				QCheckBox::indicator:indeterminate:pressed { \
					image: url(:/new/prefix/achievement dingen/checkbox_indeterminate_pressed.png); \
				}" );
	my_palette.setColor(my_palette.Disabled, my_palette.WindowText, QColor::fromRgb(128, 0, 128, 255));
	setPalette(my_palette);
}

void QROCheckBox::mousePressEvent(QMouseEvent *e) {

}

void QROCheckBox::mouseReleaseEvent(QMouseEvent *e) {

}
