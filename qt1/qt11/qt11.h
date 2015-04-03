#ifndef QT11_H
#define QT11_H

#include <QtWidgets/QDialog>
#include "ui_qt11.h"

class qt11 : public QDialog
{
	Q_OBJECT

public:
	qt11(QWidget *parent = 0);
	~qt11();

private:
	Ui::qt11Class ui;
};

#endif // QT11_H
